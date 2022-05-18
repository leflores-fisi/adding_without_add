## Adding without add
Based on bitwise operators.

Applied using the concepts covered by ![Ben Eater](https://www.youtube.com/watch?v=wvJc9CZcvBc) <3

See the main.cpp for a warm the code explanation.
"How a computer add numbers? How we can sum without arithmetic operators? 😱"

```cpp
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
```
See the file for full explanation, now I need to sleep.
