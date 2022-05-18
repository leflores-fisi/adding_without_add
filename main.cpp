#include <iostream>
#include <bitset>
#include <string>
#include <stdlib.h> // atoi
#include <conio.h>
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
	const int BIT_SIZE = 32;
	std::string aBinary = std::bitset<BIT_SIZE>(a).to_string();
	std::string bBinary = std::bitset<BIT_SIZE>(b).to_string();

	int previousCarry = 0;
	std::string sumToReturn = "";

	for (int i = BIT_SIZE-1; i >= 0; i--) {
		int aBit, bBit, sum, carry;

	    aBit = static_cast<int>aBinary[i] - 48;
		bBit = static_cast<int>bBinary[i] - 48;

		carry = CARRY_OF_SUM(aBit, bBit, previousCarry);
		sum   = SUM(aBit, bBit, previousCarry);

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
	return ~num + 1;
}
int AND(int a, int b) {
	return a & b;
}
int OR(int a, int b) {
	return a | b;
}
// Stands for "Exclusive or" (1 if both are different, otherwise return 0)
int XOR(int a, int b) {
	return a ^ b;
}
