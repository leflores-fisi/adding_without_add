#include <iostream>
#include <bitset>
#include <string>
#include <stdlib.h> // atoi
#include <conio.h>
#define BIT_SIZE 64;
// TODO: Pass read-only argument by const reference

unsigned long recursiveSum(int a, int b);
int SUM(int bit1, int bit2, int carry = 0);
int CARRY_OF_SUM(int bit1, int bit2, int prevCarry = 0);
int AND(int a, int b);
int OR(int a, int b);
int XOR(int a, int b);
int NEGATE(int num);

int main() {
	int first, second;
	std::cout << "Write a sum like \"a + b\": ";
	scanf("%d + %d", &first, &second);

	std::cout << "BROOOOOO: " << recursiveSum(first, second) << std::endl << std::endl;
    getch();
    return 0;
}

unsigned long recursiveSum(int a, int b) {
	std::string aBinary = std::bitset<32>(a).to_string();
	std::string bBinary = std::bitset<32>(b).to_string();

	int previousCarry = 0;
	std::string sumToReturn = "";

	for (int i = 31; i >= 0; i--) {
		int aBit, bBit, sum, carry;

	    aBit = (int)aBinary[i] - 48;
		bBit = (int)bBinary[i] - 48;

		carry = CARRY_OF_SUM(aBit, bBit, previousCarry);
		sum   = SUM(aBit, bBit, previousCarry);
		//std::cout << previousCarry << " | " << aBit << " + " << bBit << " = " << sum << " carrying " << carry << std::endl;
		previousCarry = carry;
		sumToReturn = std::to_string(sum) + sumToReturn;
	}
	return std::bitset<32>(sumToReturn).to_ulong();
}
// Only exist carry if both are 1
int CARRY_OF_SUM(int bit1, int bit2, int prevCarry) {
	int logicSum = XOR(bit1, bit2);

	int willOverflowWithCarry = AND(logicSum,  prevCarry); // 1 + 0 or 0 + 1
	int alreadyOverflowed = AND(bit1, bit2); // 1 + 1

	int carry = OR(willOverflowWithCarry, alreadyOverflowed);
	return carry;
}
int SUM(int bit1, int bit2, int carry) {
	int logicSum = XOR(bit1, bit2);
	// XOR will invert the logicSum result if exist carry
	// that's because carry causes bit overflow in this case
	return XOR(logicSum, carry);
}

int NEGATE(int num) {
	return ~num + 1; // FIX SUM
}
int AND(int a, int b) {
	return a & b;
}
int OR(int a, int b) {
	return a | b;
}
// Exclusive or (1 if both are different, 0 otherwise)
int XOR(int a, int b) {
	return a ^ b;
}
