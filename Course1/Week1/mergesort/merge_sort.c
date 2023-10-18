#include <stdio.h>
#include <stdlib.h>

#define INPUT_LEN 16

void print_int_array(int *input, int length);
int *merge(int *a, int len_a, int *b, int len_b);
int *merge_sort(int *input, int len);

int main()
{
    int input[INPUT_LEN] = {7, 1, 6, 2, 8, 3, 4, 5, 9, 56, 2, 34, 23, 64, 24, 15};

    printf("Input:\n");
    print_int_array(input, INPUT_LEN);

    int *output = merge_sort(input, INPUT_LEN);

    printf("Output:\n");
    print_int_array(output, INPUT_LEN);

    return 0;
}

int *merge(int *a, int len_a, int *b, int len_b)
{
    int *c = malloc((len_a + len_b) * sizeof(int));
    int i = 0;
    int j = 0;
    for (size_t k = 0; k < len_a + len_b; k++)
    {
        if (((a[i] <= b[j]) && i < len_a) || j >= len_b)
        {
            c[k] = a[i];
            i++;
        }
        else
        {
            c[k] = b[j];
            j++;
        }
    }
    return c;
}

int *merge_sort(int *input, int len)
{
    int len_a = len / 2;
    int *a = malloc(len_a * sizeof(int));

    for (size_t i = 0; i < len_a; i++)
    {
        a[i] = input[i];
    }

    if (len_a > 1)
    {
        a = merge_sort(a, len_a);
    }

    int len_b = len / 2 + len % 2;
    int *b = malloc(len_b * sizeof(int));

    for (size_t i = 0; i < len_b; i++)
    {
        b[i] = input[len - len_b + i];
    }

    if (len_b > 1)
    {
        b = merge_sort(b, len_b);
    }

    return merge(a, len_a, b, len_b);
}

void print_int_array(int *input, int length)
{
    printf("[");
    for (unsigned short i = 0; i < length; i++)
    {
        printf("%d", input[i]);
        if (i < length - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}
