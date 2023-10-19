# Karatsuba algorithm

For this assignment, an implementation of the Karatsuba algorithm for the multiplication of two 64 digit numbers was developed in C. This required creating functions for preforming math on strings, since the largest integer variable in C is 64 bits long.

The library str_math.h contains these functions. They are:

```c
char *add_str(char *x, char *y);
```
Performs addition of positive integer string variables.

---

```c
char *subtract_str(char *x, char *y);
```
Performs subtraction of positive integer string variables. Can return negative numbers (Ex `"1" - "3" = "-2"``)

---


```c
void split_str(char *x, int n, char **dest1, char **dest2);
```
Splits a string in two, being the second one (dest2) of length n

---


```c
char *trim_zeros_to_left(char *x);
```
Removes leading zeros. Supports negative numbers.

---


```c
char *append_zeros_to_right(char *x, int n);
```
Appends zeros to right of string integers, multiplying them by $10^n$

---

## Program

```c
int main()
{
    char *x = "3141592653589793238462643383279502884197169399375105820974944592";
    char *y = "2718281828459045235360287471352662497757247093699959574966967627";
    printf("--> Karatsuba(%s, %s)\n", x, y);
    char *z = karatsuba(x, y);
    printf("--> Result: %s\n", z);

    return 0;
}
```

<!-- gh-action-output -->
## Program output
```bash
$ make
$ ./Course1/Week1/karatsuba/a.out 
--> Karatsuba(3141592653589793238462643383279502884197169399375105820974944592, 2718281828459045235360287471352662497757247093699959574966967627)
--> Result: 8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184
```
<!-- gh-action-output end -->


