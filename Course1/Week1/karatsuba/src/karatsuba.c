#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/str_math.h"

char *karatsuba(char *x, char *y);

int main()
{
    char *x = "3141592653589793238462643383279502884197169399375105820974944592";
    char *y = "2718281828459045235360287471352662497757247093699959574966967627";
    printf("--> Karatsuba(%s, %s)\n", x, y);
    char *z = karatsuba(x, y);
    printf("--> Result: %s\n", z);

    return 0;
}

char *karatsuba(char *x, char *y)
{

    x = trim_zeros_to_left(x);
    y = trim_zeros_to_left(y);
    // printf("--> Karatsuba(%s, %s)\n", x, y);

    //  When one input is a single digit, return the multiplication result
    if (strlen(x) == 1 || strlen(y) == 1)
    {
        int r = atoi(x) * atoi(y);
        const int max_r_len = 4;
        char *r_str = malloc(max_r_len * sizeof(char));
        r_str[3] = '\0';

        for (size_t i = 0; i < max_r_len - 1; i++)
        {
            r_str[max_r_len - 2 - i] = r % 10 + '0';
            r /= 10;
        }
        r_str = trim_zeros_to_left(r_str);
        // printf("--> Result: %s\n", r_str);
        return r_str;
    }

    int len_x = strlen(x);
    int len_y = strlen(y);
    int m = len_x > len_y ? len_x : len_y;
    int m2 = floor((double)(m) / 2.0);
    // printf("     K(%s, %s)  m %d m2 %d\n", x, y, m, m2);
    char *x0;
    char *x1;
    char *y0;
    char *y1;
    split_str(x, m2, &x1, &x0);
    split_str(y, m2, &y1, &y0);

    // printf("     K(%s, %s)  x %s %s\n", x, y, x1, x0);
    // printf("     K(%s, %s)  y %s %s\n", x, y, y1, y0);

    // printf("     K(%s, %s)  Calculating Z0 = %s * %s (x0 * y0)\n", x, y, x0, y0);
    char *z0 = karatsuba(x0, y0);
    // printf("     K(%s, %s)  z0 %s\n", x, y, z0);

    // printf("     K(%s, %s)  Calculating Z2 = %s * %s (x1 * y1)\n", x, y, x1, y1);
    char *z2 = karatsuba(x1, y1);
    // printf("     K(%s, %s)  z2 %s\n", x, y, z2);

    char *s1 = add_str(x0, x1);
    char *s2 = add_str(y0, y1);
    // printf("     K(%s, %s)  s1 %s\n", x, y, s1);
    // printf("     K(%s, %s)  s2 %s\n", x, y, s2);

    // printf("     K(%s, %s)  Calculating Z1 = %s * %s (s1 * s2)\n", x, y, s1, s2);
    char *z1 = karatsuba(s1, s2);
    // printf("     K(%s, %s)  z1 %s\n", x, y, z1);
    z1 = subtract_str(z1, z2);
    // printf("     K(%s, %s)  z1 - %s = %s\n", x, y, z2, z1);
    z1 = subtract_str(z1, z0);
    // printf("     K(%s, %s)  z1 - %s = %s\n", x, y, z0, z1);

    // printf("\n     K(%s, %s)  z2* 10^(2 m2) + z1 * 10^m2 + z0\n", x, y);
    // printf("     K(%s, %s)  %s* 10^(2 %d) + %s * 10^%d + %s\n", x, y, z2, m2, z1, m2, z0);
    z2 = append_zeros_to_right(z2, 2 * m2);
    z1 = append_zeros_to_right(z1, m2);
    // printf("     K(%s, %s)  %s + %s + %s\n\n", x, y, z2, z1, z0);

    return add_str(add_str(z2, z1), z0);
}
