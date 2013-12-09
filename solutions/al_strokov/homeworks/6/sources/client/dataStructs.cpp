#include "dataStructs.h"

#include <iostream>
#include <string>
#include <sstream>

std::string renderArr(const char * arr, size_t size){
	std::stringstream ss;
	for( size_t i = 0; i < size; i++){
		ss << std::hex << (uint)arr[i] << " ";
	}
	return ss.str();

}


bool tqHeader_t::isShortQuote() {
	return (this->messageCategory == 'E'
			|| this->messageCategory == 'L')
			&& this->messageType == 'D';
}

bool tqHeader_t::isLongQuote() {
	return (this->messageCategory == 'B'
			|| this->messageCategory == 'E'
			|| this->messageCategory == 'L')
			&& this->messageType == 'B';
}

bool tqHeader_t::isShortTrade() {
	return (this->messageCategory == 'E'
			|| this->messageCategory == 'L')
			&& this->messageType == 'I';
}

bool tqHeader_t::isLongTrade() {
	return (this->messageCategory == 'B'
			|| this->messageCategory == 'E'
			|| this->messageCategory == 'L')
			&& this->messageType == 'B';
}
