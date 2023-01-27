#ifndef _BITREPR_H
#define _BITREPR_H

#include <string>
#include <vector>

template <class T> 
class BitRepresentation {
private:
	T data;
public:
	BitRepresentation(T number);
	BitRepresentation(const std::vector<bool>&) ;
	std::string getBinary() const;
	std::string getHexadecimal() const;
	void setBit(unsigned int location);
	void unsetBit(unsigned int location);
	bool isBitSet(unsigned int location);
	std::string decimal_to_binary(T) const;
	T getNumber();
};

#include "BitRepresentation.cpp"

#endif // !_BITREPR_H