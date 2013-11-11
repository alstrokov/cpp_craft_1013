#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <stdexcept>

namespace task5_5
{
	template< typename T >
	class vector
	{
	private:
		T* mem;
		size_t len;
		size_t cap;
	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this
	explicit vector();
		vector( const vector& copy );
		vector& operator=( const vector& copy_from );
		~vector();

		void push_back( const T& value );
		void insert( const size_t index, const T& value );

		T& operator[]( const size_t index );
		const T& operator[]( const size_t index ) const;

		void resize( const size_t amount );
		void reserve( const size_t amount );

		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;
	};

	//  please realise the rest methods according to the tests

	template< typename T >
	vector< T >::vector()
	{
		len = 0;
		cap = 4;
		mem = new T[cap];
	}
	template< typename T >
	vector< T >::vector( const vector< T >& copy )
	{
		operator=(copy);
	}
	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& copy_from )
	{
		len = copy_from.size();
		cap = copy_from.capacity();
		mem = new T[cap];
		int i = 0;
		for( vector<T>::const_iterator it = copy_from.begin(); it != copy_from.end(); ++it, ++i)
		{
			mem[i] = *it;
		}
		return *this;
	}
	template< typename T >
	vector<T>::~vector()
	{

	}

	template< typename T >
	void vector< T >::push_back( const T& t)
	{
		if(len < cap)
		{
			mem[len] = t;
			len++;
		}
		else
		{
			cap *= 4;
			T* newMem = new T[cap];
			for(size_t i = 0; i < len; ++i)
			{
				newMem[i] = mem[i];
			}
			delete[] mem;
			newMem[len] = t;
			mem = newMem;
			len++;
		}
	}

	template< typename T >
	void vector< T >::insert( const size_t index, const T& value )
	{
		if(index > len)
		{
			throw std::out_of_range("error in []");
		}
		if(cap == len )
		{
			reserve(cap*4);
		}
		for(size_t i = index; i < len; ++i)
		{
			mem[i+1] = mem[i];
		}
		mem[index] = value;		
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t index )
	{
		if(index >= len)
		{
			throw std::out_of_range("error in []");
		}
		return mem[index];
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t index ) const
	{
		if(index >= len)
		{
			throw std::out_of_range("error in cosnt []");
		}
		return mem[index];
	}

	template< typename T >
	void vector< T >::resize( const size_t amount )
	{
		cap = amount;
		T* newMem = new T[cap];
		for(size_t i = 0; i < len; ++i)
		{
			newMem[i] = mem[i];
		}
		for(size_t i = len; i < cap; ++i)
		{
			newMem[i] = T();
		}
		len = cap;
		delete[] mem;
		mem = newMem;
	}
	template< typename T >
	void vector< T >::reserve( const size_t amount)
	{
		cap = amount;
		T* newMem = new T[cap];
		for(size_t i = 0; i < len; ++i)
		{
			newMem[i] = mem[i];
		}
		delete[] mem;
		mem = newMem;
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return len;
	}
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return cap;
	}
	template< typename T >
	bool vector< T >::empty() const
	{
		return (len == 0);
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return &mem[0];
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return &mem[len];
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return &mem[0];
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return &mem[len];
	}
}

#endif // _TASK5_5_VECTOR_H_

