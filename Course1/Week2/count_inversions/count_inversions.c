#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 100000

void print_int_array(int *input, int length);
int floor(double x);
int ceil(double x);
int *merge(int *a, int len_a, int *b, int len_b);
int *merge_sort(int *input, int len);
long long unsigned int count_inversions(int **array, int length);
long long unsigned int count_split_inversions(int **array, int length);

int main() {
    int *input = malloc(sizeof(int) * MAX_INPUT_LEN);

    // Read input file
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen("Course1/Week2/count_inversions/input.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    int i = 0;
    while (((read = getline(&line, &len, fp)) != -1) && i < MAX_INPUT_LEN) {
        input[i] = atoi(line);
        i++;
    }

    fclose(fp);
    if (line) free(line);

    // printf("Input:\n");
    // print_int_array(input, MAX_INPUT_LEN);

    long long unsigned int count = count_inversions(&input, MAX_INPUT_LEN);

    // printf("Input after running count_inversions:\n");
    // print_int_array(input, MAX_INPUT_LEN);

    printf("Number of inversions: %llu\n", count);

    return 0;
}

long long unsigned int count_inversions(int **array, int length) {
    if (length == 1) {
        return 0;
    }

    // Divide array in two halves
    int len_first_half = floor((double)length / 2.0);
    int len_second_half = ceil((double)length / 2.0);

    int *first_half = *array;

    int *second_half = &((*array)[len_first_half]);

    // Recursevely count inversions in each half
    long long unsigned int x = count_inversions(&first_half, len_first_half);
    long long unsigned int y = count_inversions(&second_half, len_second_half);
    // Count inversions that happen between each half
    long long unsigned int z = count_split_inversions(array, length);

    return x + y + z;
}

long long unsigned int count_split_inversions(int **array, int length) {
    int *sorted = malloc((length) * sizeof(int));
    long long unsigned int split_inversions_count = 0;

    // Divide array in two halves
    int len_first_half = floor((double)length / 2.0);
    int len_second_half = ceil((double)length / 2.0);

    int *first_half = malloc(sizeof(int) * len_first_half);
    for (size_t i = 0; i < len_first_half; i++) {
        first_half[i] = (*array)[i];
    }

    int *second_half = malloc(sizeof(int) * len_second_half);
    for (size_t i = 0; i < len_second_half; i++) {
        second_half[i] = (*array)[len_first_half + i];
    }

    int i = 0;
    int j = 0;
    for (size_t k = 0; k < len_first_half + len_second_half; k++) {
        if (((first_half[i] <= second_half[j]) && i < len_first_half) ||
            j >= len_second_half) {
            sorted[k] = first_half[i];
            i++;
        } else {
            sorted[k] = second_half[j];
            j++;
            split_inversions_count += len_first_half - i;
        }
    }

    for (size_t i = 0; i < length; i++) {
        (*array)[i] = (sorted)[i];
    }

    return split_inversions_count;
}

int *merge(int *a, int len_a, int *b, int len_b) {
    int *c = malloc((len_a + len_b) * sizeof(int));
    int i = 0;
    int j = 0;
    for (size_t k = 0; k < len_a + len_b; k++) {
        if (((a[i] <= b[j]) && i < len_a) || j >= len_b) {
            c[k] = a[i];
            i++;
        } else {
            c[k] = b[j];
            j++;
        }
    }
    return c;
}

int *merge_sort(int *input, int len) {
    int len_a = len / 2;
    int *a = malloc(len_a * sizeof(int));

    for (size_t i = 0; i < len_a; i++) {
        a[i] = input[i];
    }

    if (len_a > 1) {
        a = merge_sort(a, len_a);
    }

    int len_b = len / 2 + len % 2;
    int *b = malloc(len_b * sizeof(int));

    for (size_t i = 0; i < len_b; i++) {
        b[i] = input[len - len_b + i];
    }

    if (len_b > 1) {
        b = merge_sort(b, len_b);
    }

    return merge(a, len_a, b, len_b);
}

void print_int_array(int *input, int length) {
    printf("[");
    for (unsigned short i = 0; i < length; i++) {
        printf("%d", input[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int floor(double x) {
    int x_round = (int)x;
    if (x_round - x <= 0) {
        return x_round;
    }
    return x_round - 1;
}

int ceil(double x) {
    int x_round = (int)x;
    if (x_round - x >= 0) {
        return x_round;
    }
    return x_round + 1;
}
