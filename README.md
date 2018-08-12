# NumberConverter
Convert integers and fixed point real numbers between numeral systems. Suppose numeral systems form 2 to 36. Alphabet is '0-9a-z\.'. Input strings are case insensitive. Length of numbers is limited olny by your available memory, since the program depends on Boost multiprecision integers (MPI).

The program depends on Boost for MPIs and Qt for interface.

# Algorithm:
Input: 
- inputNumber - string, representing a number in system base1. inputNumber can contain one point, delimiting integer and fraction parts.

Output:
- outString, representing inputNumber in system base2. If inputNumber contains fraction part, outString can also contains one. Number of digits in fraction part can be set by user, since some number in system base1 can haven't precise representaion in system base2.
