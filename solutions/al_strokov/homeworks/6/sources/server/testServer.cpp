#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>
#include <fstream>

const static std::string filePath(SOURCE_DIR "/sources/datafiles/");

static const char SOH = 0x01;
static const char ETX = 0x03;

void peekChar(const char key, std::ifstream& ifs) {
	char x;
	while (!ifs.eof() && ifs.read(&x, sizeof x) && x != key)
		;
}

void asendHandler(char *, const boost::system::error_code&,
		std::size_t) {}

void sendUdpFile(const char * fileName, boost::asio::io_service&ios,
		const char * address, const int port) {

	boost::asio::ip::udp::endpoint endpoint(
			boost::asio::ip::address::from_string(address), port);
	boost::asio::ip::udp::socket socket(ios, endpoint.protocol());

	std::ifstream ifs;
	ifs.open(fileName, std::ios::binary | std::ios::in);
	std::cout << fileName << " to " << address << ":" << port << "...";
	if (!ifs.is_open()) {
		std::cout << " - file bad" << std::endl;
		return;
	}

	char* buffMsg;
	size_t buffSize;
	std::streampos spCurr;
	std::streampos spKey;

	while (!ifs.eof()) {
		peekChar(SOH, ifs);
		spCurr = ifs.tellg() - (std::streampos) (1);
		peekChar(ETX, ifs);
		spKey = ifs.tellg();
		if (ifs.eof()) {
			std::cout << "...file send." << std::endl;
			break;
		}

		buffSize = spKey - spCurr;

		ifs.seekg(spCurr);
		buffMsg = new char[buffSize];
		ifs.read(buffMsg, buffSize);

		boost::this_thread::sleep(boost::posix_time::millisec(1));

		socket.async_send_to(boost::asio::buffer(buffMsg, buffSize),
				endpoint,
				boost::bind(&asendHandler, buffMsg,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
		delete[] buffMsg;
	}

	ifs.close();
}

int main() {
	std::cout << "udp server 03" << std::endl;
	std::cout.flush();

	boost::asio::io_service service;

	sendUdpFile( (filePath + "233.200.79.0.udp").c_str(), service, "233.200.79.0", 61000 );
	sendUdpFile( (filePath + "233.200.79.1.udp").c_str(), service, "233.200.79.1", 61001 );
	sendUdpFile( (filePath + "233.200.79.2.udp").c_str(), service, "233.200.79.2", 61002 );
	sendUdpFile( (filePath + "233.200.79.3.udp").c_str(), service, "233.200.79.3", 61003 );
	sendUdpFile( (filePath + "233.200.79.4.udp").c_str(), service, "233.200.79.4", 61004 );
	sendUdpFile( (filePath + "233.200.79.5.udp").c_str(), service, "233.200.79.5", 61005 );
	sendUdpFile( (filePath + "233.200.79.6.udp").c_str(), service, "233.200.79.6", 61006 );
	sendUdpFile( (filePath + "233.200.79.7.udp").c_str(), service, "233.200.79.7", 61007 );

	sendUdpFile( (filePath + "233.200.79.128.udp").c_str(), service, "233.200.79.128", 62128 );
	sendUdpFile( (filePath + "233.200.79.129.udp").c_str(), service, "233.200.79.129", 62129 );
	sendUdpFile( (filePath + "233.200.79.130.udp").c_str(), service, "233.200.79.130", 62130 );
	sendUdpFile( (filePath + "233.200.79.131.udp").c_str(), service, "233.200.79.131", 62131 );
	sendUdpFile( (filePath + "233.200.79.132.udp").c_str(), service, "233.200.79.132", 62132 );
	sendUdpFile( (filePath + "233.200.79.133.udp").c_str(), service, "233.200.79.133", 62133 );
	sendUdpFile( (filePath + "233.200.79.134.udp").c_str(), service, "233.200.79.134", 62134 );
	sendUdpFile( (filePath + "233.200.79.135.udp").c_str(), service, "233.200.79.135", 62135 );

	service.run();
	std::cout << std::endl;
	service.stop();

	std::cout << "\nfiles transmitted" << std::endl;
	return 0;
}
