/*

base^cardinality

The total number of values possible within a given range in base N within a set
with a cardinality of C would be N^C.

N=2
C=4
2^4 = 16 = 0000 1000
           0001 1001
           0010 1010
           0011 1011
           0100 1100
           0101 1101
           0110 1110
           0111 1111

Using binary counting it is easy to prove this formula by iterating through all
possible values. In decimal (greater N) or with a greater cardinality (greater 
C) the table of values would be much larger --however the formula for computing
the total amount of uniqe values the number can hold is the same.

This formula (N^C) allows for fast and logical computation of probablities in
a non-deterministic setting such as a dice game throwing "random" dice throws.

Here is an explanation of the probablity of obtaining the sequence
 4, 6, 2, 5, 7, 9, 8 out of a random throwing of 7 dice: 

6 sided dice use a base 5 counting system consisting of the character values 1-6
(1,2,3,4,5 and 6). Therefore computing the maximum number of possible dice
combinations in base 5 using 7 dice is simple and can be expressed as the value 
5555555 (or 6666666). Therefore the entire range of this number system sits
between 0000000 and 5555555 possibilities in base 5.

*/
