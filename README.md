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

### Procedure toInteger
Input: 
- inputNumber - string form of MPI number in system base1.

Output:
- num - MPI form of inputNumber.

Variables:
- digits - vector of chars 0,..,9,a,..,z, where item index from beginning denotes numeral value of this symbolic digit. Indicies are 0-based.

```
1. Put MPIs num := 0, num2 := 1.
2. For every char c in inputNumber from end to begin do:
2.1. Put num3 := index of c in vector digits.
2.2. Assign num += num2 * num3.
2.3. Assign num2 *= base1.
3. Return num.
```

### Procedure pow
Input: 
- a - MPI;
- n - integer number.

Output:
- a, raised to power n.

Use binary exponentiation. Pseudocode is not interesting.

### Procedure toString
Input: 
- inputNumber - MPI.

Output:
- outStr - string form inputNumber in system base2.

Variables:
- digits - vector of chars 0,..,9,a,..,z, as above.

```
1. Put outStr := "".
2. If inputNumber = 0:
2.1. Return "0".
2. While inputNumber > 0, do:
2.1. Divide inputNumber by base2 and get numbers:
     remainder r - integer;
     quotient q - MPI.
2.2. Assign outStr += digits[r]
2.3. Assign inputNumber := q.
3. Reverse chars in outStr.
4. Return outStr.
```

### Procedure fractionPartToString
Input: 
- num - rational number in range [0, 1), that is pair of MPIs.

Output:
- outStr - string form num in system base2.

Variables:
- digits - vector of chars 0,..,9,a,..,z, as above.

```
