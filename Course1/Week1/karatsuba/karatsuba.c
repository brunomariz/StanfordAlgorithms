#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *karatsuba(char *x, char *y);
void trim_zeros_to_left(char *x);
void append_zeros_to_right(char *x, int n);
char *add_str(char *x, char *y);

int main()
{
    char x[] = "123";

    char y[] = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

    char *z = add_str(x, y);
    printf("%s\n", z);

    return 0;
}

char *karatsuba(char *x, char *y)
{
    if (strlen(x) == 1 && strlen(y) == 1)
    {
        // int r = atoi(x) * atoi(y);
        // char *c = {r + '0', '\0'};
        // return c;
    }
}

char *add_str(char *x, char *y)
{
    int len_x = strlen(x);
    int len_y = strlen(y);

    int max_len = len_x > len_y ? len_x : len_y;
    int min_len = len_x < len_y ? len_x : len_y;

    int sum_len = max_len + 1;
    char *sum = malloc(sizeof(char) * (sum_len + 1));
    sum[sum_len] = '\0';
    for (size_t i = 0; i < sum_len; i++)
    {
        sum[i] = '0';
    }

    int carry = 0;
    for (size_t i = 0; i < min_len; i++)
    {
        int current_x = x[len_x - i - 1] - '0';
        int current_y = y[len_y - i - 1] - '0';
        int partial_sum = current_x + current_y + carry;
        carry = partial_sum / 10;
        sum[max_len - i] = partial_sum % 10 + '0';
    }
    for (size_t i = min_len; i < max_len; i++)
    {
        int current = len_x > len_y ? x[len_x - i - 1] - '0' : y[len_y - i - 1] - '0';
        int partial_sum = current + carry;
        carry = partial_sum / 10;
        sum[max_len - i] = partial_sum % 10 + '0';
    }
    sum[0] = carry + '0';
    trim_zeros_to_left(sum);
    return sum;
}

void trim_zeros_to_left(char *x)
{
    int count = 0;
    while (x[count] == '0')
    {
        count++;
    }

    int len_x = strlen(x);
    char *trimmed = malloc(sizeof(char) * (len_x - count + 1));
    trimmed = &x[count];
    strcpy(x, trimmed);
}