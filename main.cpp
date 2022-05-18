#include <iostream>
#include <bitset>
#include <string>
#include <stdlib.h> // atoi
#include <conio.h>
// TODO: Pass read-only argument by const reference

/*
  Algorithm for adding without the sum operator.
  Content learned from Ben Eater <3, see https://www.youtube.com/watch?v=wvJc9CZcvBc
  Applied to code and explained by https://github.com/leflores-fisi

  How we add binary numbers? Just like we add decimals.

     (1)(1)(0)
      1  1  1  0 +
      0  1  1  1
    ------------
   1  0  1  0  1

  This is how we are going to add here. :D
  But... without the sum operator? Yes.
  I highly recommend first watching the video above for a better concept.

  Did you remember logical operators?
  V and F === F
  F or  V === V
  V and V === V

  That is what bitwise operators are, but for bits:
  &   AND
  |   OR
  ^   XOR
  ~   NOT
  <<  LEFT SHIFT
  >>  RIGHT SHIFT

  Are the same? NO.
  Bitwise operators works with binary values.
  Logical operators works with boolean values.
  And are extremely related.

  That is,
  ~F === V
  ~11001 === 00110
  100 & 110 === ???

  See them like this, operating each column with the operator logical-definition:
  1 0 0  &
  1 1 0
  -----
  1 0 0

  Wow... this looks familiar.
  Yes :D, thats why we are going to use them for this algorithm.
  Also is the algorithm that your processor uses!!
  Now our problem is how we are going to handle the sum carries.
  And clearly the AND bitwise operator does not work as a binary sum.
  But XOR operator does. :D

  1 0 0  ^
  0 1 0
  -----
  1 1 0

  Wow! It add them perfectly. (4 + 2 = 6)
  But as mentioned before, is not enough yet.
  Here starts the code...

  It's awesome how we can define the math using the logic. <3
*/

// Our final algorithm :D
unsigned long bitwiseSUM(int a, int b);


// All the following functions returns binary values (0 or 1).
// but are typed as int for convenience (type suggestions are welcome).


int BIT_SUM(int bit1, int bit2, int carry = 0);
int GET_SUM_CARRY(int bit1, int bit2, int prevCarry = 0);
// Bitwise operators (already defined by C++ but here for readability).
int AND    (int a, int b);
int OR     (int a, int b);
int XOR    (int a, int b);
// This function negates an integer (but is not used by the algorithm).
int NEGATE (int num);
int charToInt(char c);


int main() {
	int first, second;

	std::cout << "Write a sum like \"a + b\": ";
	scanf("%d + %d", &first, &second);

	std::cout << "BROOOOOO: " << bitwiseSUM(first, second) << std::endl;
    getch();
    return 0;
}

/*
  This function add two bits and returns only one bit, its sum (the carry is later handled)
  All possible inputs and outputs:
    0 + 0 (carrying: 0) -> returns 0
    1 + 0 (carrying: 0) -> returns 1
    0 + 1 (carrying: 0) -> returns 1
    1 + 1 (carrying: 0) -> returns 0

    0 + 0 (carrying: 1) -> returns 1
    1 + 0 (carrying: 1) -> returns 0
    0 + 1 (carrying: 1) -> returns 0
    1 + 1 (carrying: 1) -> returns 1
  Note how the outputs are reversed depend of the existence of carry
  this is exploited later (in GET_SUM_CARRY) by the algorithm
*/
int BIT_SUM(int bit1, int bit2, int carry) {
	int logicSum = XOR(bit1, bit2);
	// XOR will invert the logicSum result if exist carry
	// that's because the carry causes the bits either to overflow or go from 0 to 1, one of that two
	return XOR(logicSum, carry);
	// Now we need to handle the carry
}

/*
  Here we are going to determine the sum carry
  For that we need to considerate if a previous carry exist, because we are going to sum in chain.
*/
// Note that in the BIT_SUM() examples only exist carry if both bits are 1 or previous carry overflowed the sum
// This function returns that carry (0 or 1)
int GET_SUM_CARRY(int bit1, int bit2, int prevCarry) {
	// First, we need to check if the bits sum will overflow
	// As mentioned before, only two ways exist:
	// - with carry and adding 0+0 or 1+1
	// - without carry and adding 1+1
	// People found smart ways to check this with bitwise operators :D

	int logicSum = XOR(bit1, bit2); // here XOR helps to check if bits are 1+0 or 0+1

	// First way
	// -> 1: only if (exist prevCarry) AND (bits are 1+0 or 0+1)
	int willOverflowWithCarry = AND(logicSum, prevCarry);
	// -> 1: only overflowed on 1+1 (thats why we use AND bitwise operator)
	int alreadyOverflowed = AND(bit1, bit2);

	// So.. we are going to have a carry if at least one of these conditions are "true"
	// Note that is impossible to have both as true
	int carry = OR(willOverflowWithCarry, alreadyOverflowed);
	return carry;
}

/* Bitwise operators */
int NEGATE(int num) {
	return ~num + 1;
}
int AND(int a, int b) {
	return a & b;
}
int OR(int a, int b) {
	return a | b;
}
// Stands for "Exclusive or" (1 if both bits are different, otherwise return 0)
int XOR(int a, int b) {
	return a ^ b;
}

/* Just a helper :D */
int charToInt(char c) {
	return static_cast<int>(c) - 48;
}

/*
  Now we can create our main algorithm, how exciting!
  The basic idea is transform our two integers to binary numbers,
  then iterate them adding each column with the BIT_SUM() function
  and saving each carry returned by GET_SUM_CARRY() for adding it to the next iteration.

  I made the code as self readable as possible, so enjoy <3
*/
unsigned long bitwiseSUM(int a, int b) {
	const int BIT_SIZE = 32;
	// Converting integers to string bits
	std::string aBinary = std::bitset<BIT_SIZE>(a).to_string();
	std::string bBinary = std::bitset<BIT_SIZE>(b).to_string();

	int previousCarry = 0;
	std::string sumToReturn = "";

	// reverse iteration
	for (int i = BIT_SIZE-1; i >= 0; i--) {
		int aBit, bBit, bit_result, carry_result;

		// There is, our two bits
	    aBit = charToInt(aBinary[i]);
		bBit = charToInt(bBinary[i]);

		carry_result = GET_SUM_CARRY(aBit, bBit, previousCarry);
		bit_result   = BIT_SUM(aBit, bBit, previousCarry);

		previousCarry = carry_result;
		// appending the bit to the left
		sumToReturn = std::to_string(bit_result) + sumToReturn;
	}
	// And...
	return std::bitset<BIT_SIZE>(sumToReturn).to_ulong();
	// Its all done, you can test the code an suggest changes
	// Thanks for coming here, you brave one, have a good night
}
