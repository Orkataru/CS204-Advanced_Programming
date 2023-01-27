#pragma once
#include "BitRepresentation.h"
#include <iostream>
#include <sstream>

using namespace std;

// operator i64 and the keyword _int64 are apparently Microsoft-specific, so to make this code cross-platform we need to define them
#define _int64 int64_t
inline int64_t operator"" i64(unsigned long long i) { return (int64_t) i; }


template<class T> 
BitRepresentation<T>::BitRepresentation(T number) {
	data = number;
}


template<class T>
BitRepresentation<T>::BitRepresentation(const vector<bool> &v)  {

	data = 0;

	int num_bits = v.size();
	int size_T = sizeof(T) * 8;

	int size = num_bits > size_T ? size_T : num_bits;

	// Iterate through the vector and set the corresponding bits in data
	for (int i = size - 1; i >= 0; i--) {
		// Set the i-th least significant bit in data to 1 
		if (v[v.size() - (size - i)])
		{
			data |= (1i64 << (size - 1 - i));
		}
	}

}

// Helper function that takes a decimal value as parameter and returns its binary representation as a string
template <class T>
string BitRepresentation<T>::decimal_to_binary(T n) const {
	string binary = "";
	unsigned size = sizeof(T) * 8;
	T x = 0;

	for (unsigned i = 0; i < size; i++)
	{
		_int64 one = 1;			// since the shift could be greater than 32 bits, we need to define 1 as _int64
		x = n & (one << i);		// another possible implementation would be x = n & (1i64 << i)
		if (x)
		{
			binary = "1" + binary;
		}
		else
		{
			binary = "0" + binary;
		}
	}

	if (binary.length() < size)
	{
		string s(size - binary.length(), '0');
		binary = s + binary;
	}
	return binary;
}

template<class T>
string BitRepresentation<T>::getBinary()  const
{
	return decimal_to_binary(data);
}

template<class T>
string BitRepresentation<T>::getHexadecimal() const
{
	string str("");
	size_t size = sizeof(T) * 2;
	stringstream s;
	s << hex << (_int64)data;
	str = s.str();

	if (str.length() < size)
	{
		string s(size - str.length(), '0');
		str = s + str;
	}
	else if (size < str.length())
	{
		str = str.substr(str.length() - size);
	}

	// Capitalize
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < 123 && str[i] > 96)
		{	
			str[i] = (char)str[i] - 32;
		}
	}
	return str;
}


template<class T>
void BitRepresentation<T>::setBit(unsigned int location){
	if (location < sizeof(T) * 8) data = data | (1i64 << location);
}

template<class T>
void BitRepresentation<T>::unsetBit(unsigned int location){
	if (location < sizeof(T) * 8) data = data & ~(1i64 << location);
}

template<class T>
bool BitRepresentation<T>::isBitSet(unsigned int location) { 
	if (location < sizeof(T) * 8) return data & (1i64 << location);
	return 0;
}

template<class T>
T BitRepresentation<T>::getNumber() {
	return data;
}