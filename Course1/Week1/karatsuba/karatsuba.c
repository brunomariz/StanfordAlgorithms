#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *karatsuba(char *x, char *y);
char *add_str(char *x, char *y);
void split_str(char *x, int n, char **dest1, char **dest2);
void trim_zeros_to_left(char *x);
void append_zeros_to_right(char *x, int n);

int main()
{
    char *x = "123456789";
    char *a;
    char *b;
    int n;
    n = 8;
    split_str(x, n, &a, &b);
    printf("x: %s\nn %d\na %s\nb %s\n", x, n, a, b);
    n = 9;
    split_str(x, n, &a, &b);
    printf("x: %s\nn %d\na %s\nb %s\n", x, n, a, b);
    n = 10;
    split_str(x, n, &a, &b);
    printf("x: %s\nn %d\na %s\nb %s\n", x, n, a, b);

    return 0;
}

char *karatsuba(char *x, char *y)
{
    if (strlen(x) == 1 || strlen(y) == 1)
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

void split_str(char *x, int n, char **dest1, char **dest2)
{
    // Splits x string between dest1 and dest2 at position n
    // where n = length of dest1

    int len_x = strlen(x);

    int len_dest1 = n;
    int len_dest2 = len_x - n;
    (*dest1) = (char *)malloc(sizeof(char) * (len_dest1 + 1));
    (*dest1)[len_dest1] = '\0';
    (*dest2) = (char *)malloc(sizeof(char) * (len_dest2 + 1));
    (*dest2)[len_dest2] = '\0';

    for (size_t i = 0; i < len_dest1; i++)
    {
        (*dest1)[i] = x[i];
    }
    for (size_t i = len_dest1; i < len_x; i++)
    {
        (*dest2)[i - len_dest1] = x[i];
    }
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