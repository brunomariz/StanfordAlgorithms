#ifndef STR_MATH_H
#define STR_MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *add_str(char *x, char *y);
char *subtract_str(char *x, char *y);
void split_str(char *x, int n, char **dest1, char **dest2);
char *trim_zeros_to_left(char *x);
char *append_zeros_to_right(char *x, int n);

#endif