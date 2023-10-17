#include "../inc/str_math.h"

int ctoi(char c)
{
    return (int)(c - '0');
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
    sum = trim_zeros_to_left(sum);
    return sum;
}

char *subtract_str(char *x, char *y)
{
    // Returns x - y

    x = trim_zeros_to_left(x);
    y = trim_zeros_to_left(y);

    // Compare numbers
    int len_x = strlen(x);
    int len_y = strlen(y);

    char x_gt_y = 0;
    char x_eq_y = 1;

    if (len_x > len_y)
    {
        x_gt_y = 1;
        x_eq_y = 0;
    }
    else if (len_y > len_x)
    {
        x_gt_y = 0;
        x_eq_y = 0;
    }
    else // if (len_x == len_y)
    {
        for (size_t i = 0; i < len_x; i++)
        {
            int diff = ctoi(x[i]) - ctoi(y[i]);
            if (diff < 0)
            {
                x_gt_y = 0;
                x_eq_y = 0;
                break;
            }
            else if (diff > 0)
            {
                x_gt_y = 1;
                x_eq_y = 0;
                break;
            }
        }
    }

    if (x_eq_y == 1)
    {
        return "0";
    }

    char *l;
    int len_l;
    char *s;
    int len_s;
    char *r;
    int len_r;

    if (x_gt_y == 1)
    {
        l = x;
        len_l = len_x;

        s = y;
        len_s = len_y;

        len_r = len_l + 1;
        r = malloc(sizeof(char) * (len_r + 1));
        r[len_r] = '\0';
        r[0] = '0';
    }
    else
    {
        l = y;
        len_l = len_y;

        s = x;
        len_s = len_x;

        len_r = len_l + 1;
        r = malloc(sizeof(char) * (len_r + 1));
        r[len_r] = '\0';
        r[0] = '-';
    }

    // Perform subtraction of largest - smallest
    // 35
    // 16
    //

    char carry = 0;
    for (size_t i = 0; i < len_l; i++)
    {
        int current_l = ctoi(l[len_l - i - 1]);
        int current_s = i < len_s ? ctoi(s[len_s - i - 1]) : 0;
        int partial = current_l - current_s - carry;
        if (partial < 0)
        {
            partial = current_l + 10 - current_s - carry;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        r[len_r - i - 1] = partial + '0';
    }

    r = trim_zeros_to_left(r);
    return r;
}

void split_str(char *x, int n, char **dest1, char **dest2)
{
    // Splits x string between dest1 and dest2 at position n
    // where n = length of dest1

    int len_x = strlen(x);

    int len_dest2 = n;
    int len_dest1 = len_x - n;
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

char *append_zeros_to_right(char *x, int n)
{
    int len_x = strlen(x);
    char *extended = malloc(sizeof(char) * (len_x + n + 1));
    strcpy(extended, x);
    for (size_t i = 0; i < n; i++)
    {
        extended[len_x + i] = '0';
    }
    extended[len_x + n] = '\0';
    return extended;
}

char *trim_zeros_to_left(char *x)
{
    int len_x = strlen(x);

    int zero_count = 0;
    int negative_count = 0;
    for (size_t i = 0; i < len_x; i++)
    {
        if (x[i] == '0')
        {
            zero_count++;
        }
        else if (x[i] == '-')
        {
            negative_count++;
        }
        else
        {
            break;
        }
    }

    // If only zeros, return "0"
    if (zero_count == len_x)
    {
        return "0";
    }

    // 0134 -> 134    zc = 1 nc = 0
    int len_trimmed = len_x - zero_count;
    char *trimmed = malloc(sizeof(char) * (len_trimmed + 1));
    strcpy(trimmed, &x[len_x - len_trimmed]);
    if (negative_count > 0)
    {
        trimmed[0] = '-';
    }

    return trimmed;
}