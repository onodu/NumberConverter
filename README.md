# NumberConverter
Convert integers and fixed point real numbers between numeral systems. Suppose numeral systems form 2 to 36. Alphabet is '0-9a-z\.'. Input strings are case insensitive. Length of numbers is limited olny by your available memory, since the program depends on Boost multiprecision integers (MPI).

The program depends on Boost for MPIs and Qt for interface.

## Pseudocode
### Core procedure
Input: 
- inputNumber - string, representing a number in system base1. inputNumber can contain one point, delimiting integer and fraction parts;
- base1 - integer number, denoting system of input number;
- base2 - integer number, denoting system of output number;
- digitsAfterPoint - number, limiting length of faction part in output number.

Output:
- outString - string, representing inputNumber in system base2. If inputNumber contains fraction part, outString can also contains one.  Some number in system base1 can haven't precise representation in system base2.

```
1. Split inputNumber into intPartStr - part to left of the point, 
   and fractPartStr - part to right of the point.
2. Put intPart := toInteger(intPartStr) - MPI, representing intPartStr as number.
3. Put fractPart := {toInteger(fractPartStr), pow(base1, fractPartStr.size)} - 
   rational number, consisting of MPIs {numerator, denominator}, 
   representing fractPartStr as number from [0, 1).
4. Put outString := toString(intPart).
5. If fractPart > 0 and digitsAfterPoint > 0:
5.1. Assign outString += "." + fractionPartToString(fractPart).
6. Return outString.
```

### Procedure pow
Input: 
- a - MPI;
- n - integer number.
Output:
- a raised to power n.

