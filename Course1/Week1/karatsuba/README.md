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
