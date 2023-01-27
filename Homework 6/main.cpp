#include <iostream>
#include "BitRepresentation.h"

int main() {
	BitRepresentation<char> br1(111111);

	std::cout << "br1: " << br1.getBinary() << " " << br1.getHexadecimal() << std::endl;

	std::vector<bool> bits = {1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1};
	BitRepresentation<char> br2(bits);
	std::cout << "br2: " << br2.getBinary() << " " << br2.getHexadecimal() << std::endl;

	br2.setBit(0);
	std::cout << "br2: " << br2.getBinary() << " " << br2.getHexadecimal() << std::endl;

	br2.unsetBit(0);
	std::cout << "br2: " << br2.getBinary() << " " << br2.getHexadecimal() << std::endl;

	std::cout << "Bit 0 is set: " << br2.isBitSet(0) << std::endl;
	std::cout << "Bit 1 is set: " << br2.isBitSet(1) << std::endl;
	std::cout << "Bit 2 is set: " << br2.isBitSet(2) << std::endl;
	std::cout << "Bit 3 is set: " << br2.isBitSet(3) << std::endl;
	std::cout << "Bit 4 is set: " << br2.isBitSet(4) << std::endl;
	std::cout << "Bit 5 is set: " << br2.isBitSet(5) << std::endl;
	std::cout << "Bit 6 is set: " << br2.isBitSet(6) << std::endl;
	std::cout << "Bit 7 is set: " << br2.isBitSet(7) << std::endl;

	std::cout << "Number: " << br2.getNumber() << std::endl;

	return 0;
}


//
//
//#include <iostream>
//#include <cassert>
//#include <vector>
//#include "BitRepresentation.h"
//
//void testConstructorWithNumber() {
//    // Test the constructor that takes a templated type T as input
//    short num = 5;
//    BitRepresentation<short> bp(num);
//    assert(bp.getNumber() == 5);
//}
//
//void testConstructorWithVector() {
//    // Test the constructor that takes a vector of booleans as input
//    std::vector<bool> v1 = { 1, 0, 1, 0 };
//    BitRepresentation<short> bp1(v1);
//    assert(bp1.getBinary() == "0000000000001010");
//
//    std::vector<bool> v2 = { 1, 0, 1 };
//    BitRepresentation<short> bp2(v2);
//    assert(bp2.getBinary() == "0000000000000101");
//
//    std::vector<bool> v3 = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
//    BitRepresentation<short> bp3(v3);
//    assert(bp3.getBinary() == "0000001010101010");
//}
//
//void testGetBinary() {
//    // Test the getBinary() function
//    short num = 5;
//    BitRepresentation<short> bp(num);
//    assert(bp.getBinary() == "0000000000000101");
//}
//
//void testGetHexadecimal() {
//    // Test the getHexadecimal() function
//    short num = 5;
//    BitRepresentation<short> bp(num);
//    assert(bp.getHexadecimal() == "0005");
//}
//
//void testSetBit() {
//    // Test the setBit() function
//    short num = 5;
//    BitRepresentation<short> bp(num);
//    bp.setBit(3);
//    assert(bp.getBinary() == "0000000000001101");
//}
//
//void testUnsetBit() {
//    // Test the unsetBit() function
//    short num = 5;
//    BitRepresentation<short> bp(num);
//    bp.unsetBit(2);
//    assert(bp.getBinary() == "0000000000000001");
//}
//
//void testIsBitSet() {
//    // Test the isBitSet() function
//    short num = 5;
//    BitRepresentation<short> bp(num);
//    bp.setBit(3);
//    assert(bp.isBitSet(3) == true);
//    bp.unsetBit(3);
//    assert(bp.isBitSet(3) == false);
//}
//
//void testGetNumber() {
//    // Test the getNumber() function
//    short num = 5;
//    BitRepresentation<short> bp(num);
//    assert(bp.getNumber() == 5);
//}
//
//void testCharTemplate() {
//    // Test the BitRepresentation class with a char as the templated type
//    char num = 'A';
//    BitRepresentation<char> bp(num);
//    assert(bp.getBinary() == "01000001");
//    assert(bp.getHexadecimal() == "41");
//    bp.setBit(3);
//    assert(bp.getBinary() == "01001001");
//    bp.unsetBit(3);
//    assert(bp.getBinary() == "01000001");
//    assert(bp.isBitSet(3) == false);
//    assert(bp.getNumber() == 'A');
//}
//
//void testLongLongTemplate() {
//    // Test the BitRepresentation class with a long long as the templated type
//    long long num = 1234567890;
//    BitRepresentation<long long> bp(num);
//    assert(bp.getBinary() == "0000000000000000000000000000000001001001100101100000001011010010");
//    assert(bp.getHexadecimal() == "00000000499602D2");
//    bp.setBit(3);
//    assert(bp.getBinary() == "0000000000000000000000000000000001001001100101100000001011011010");
//    bp.unsetBit(3);
//    assert(bp.getBinary() == "0000000000000000000000000000000001001001100101100000001011010010");
//    assert(bp.isBitSet(3) == false);
//    assert(bp.getNumber() == 1234567890);
//}
//
//int main() {
//    testConstructorWithNumber();
//    testConstructorWithVector();
//    testGetBinary();
//    testGetHexadecimal();
//    testSetBit();
//    testUnsetBit();
//    testIsBitSet();
//    testGetNumber();
//    testCharTemplate();
//    testLongLongTemplate();
//
//    std::cout << "All test cases passed!" << std::endl;
//    return 0;
//}
//
//
//
