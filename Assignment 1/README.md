## Assignment 1
<br>

### Description
This assignment's problem statement was based on the linked list (doubly linked list with a sentinel node, to be precise) implementation of polynomials. For each part of the problem, we had to write pseudo-code and code in a programming language. The resulting polynomial ought to satisfy the constraints put on the respresentation of polynomials, namely, increasing order of exponents, and non-zero co-efficients of each term.

+ Adding two polynomials: The constraints for this problem was given in the form of the sizes of the polynomials, i.e., _(1&le; n, m&le; 10<sup>5</sup>)_. Each co-efficient would fit in a 32-bit integer and the resulting time complexity was required to be _O(m+n)_.
+ Multiplying two polynomials: The constraints were again given in the form of the sizes of the polynomials, i.e., (1&le; n, m&le; 10<sup>3</sup>) and the integers would fit in a 32-bit integer. We were able to achieve a time complexity of _O(mn&sdot;min(m, n))_ which was good enough to pass all the test cases.

<br>

### Files
The directory contains 4 files other than this README-
+ [Assignment](./Problem%20Statement.pdf)- Contains the problem statements and the instructions for the assignment.
+ [Addition](./add.cpp)- This file contains the final submission made to the problem for adding two polynomials.
+ [Multiplication](./multiply.cpp)- This file contains the final submission made to the problem for multiplying two polynomials. The code is identically similar to [add.cpp](./add.cpp), except for the code in `main` which was modified accordingly.
+ [Pseudo-code](./Analysis.pdf)- Contains the pseudo-code for both addition and multiplication of two polynomials, and the complexity analysis for the pseudo-code of multiplication. It was the final submission for the theoretical part.