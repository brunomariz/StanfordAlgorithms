#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 10000

typedef enum {
    PIVOT_CHOICE_MODE_FIRST,
    PIVOT_CHOICE_MODE_LAST,
    PIVOT_CHOICE_MODE_MEDIAN
} PivotChoiceMode;

typedef enum {
    VERBOSE_ON,
    VERBOSE_OFF,
} VerboseMode;

void quicksort(int **array, int l, int r, int *pivot_comparison_count,
               PivotChoiceMode pivot_choice_mode, VerboseMode verbose_mode);
int choose_pivot(int *array, int l, int r, PivotChoiceMode mode);
void swap_elements(int **array, int i, int j);
void partition_around_pivot(int **array, int l, int r, int *pivot);
int *generate_array();
void print_int_array(int *input, int length);

int main() {
    VerboseMode verbose_mode = VERBOSE_OFF;

    int pivot_comparison_count = 0;

    printf("================================================\n");
    printf("Pivot choice strategy: first element of subarray\n");

    int *array = generate_array();
    // printf("Input array:\n");
    // print_int_array(array, MAX_INPUT_LEN);
    quicksort(&array, 0, MAX_INPUT_LEN - 1, &pivot_comparison_count,
              PIVOT_CHOICE_MODE_FIRST, verbose_mode);

    // printf("\nSorted array:\n");
    // print_int_array(array, MAX_INPUT_LEN);
    printf(
        "Total pivot comparisons: "
        "%d\n",
        pivot_comparison_count);

    printf("================================================\n");
    printf("Pivot choice strategy: last element of subarray\n");
    pivot_comparison_count = 0;

    array = generate_array();

    // printf("Input array:\n");
    // print_int_array(array, MAX_INPUT_LEN);
    quicksort(&array, 0, MAX_INPUT_LEN - 1, &pivot_comparison_count,
              PIVOT_CHOICE_MODE_LAST, verbose_mode);

    // printf("\nSorted array:\n");
    // print_int_array(array, MAX_INPUT_LEN);
    printf(
        "Total pivot comparisons: "
        "%d\n",
        pivot_comparison_count);

    printf("================================================\n");
    printf(
        "Pivot choice strategy: median element between first, middle, and last "
        "elements of subarray\n");
    pivot_comparison_count = 0;

    array = generate_array();

    // printf("Input array:\n");
    // print_int_array(array, MAX_INPUT_LEN);
    quicksort(&array, 0, MAX_INPUT_LEN - 1, &pivot_comparison_count,
              PIVOT_CHOICE_MODE_MEDIAN, verbose_mode);

    // printf("\nSorted array:\n");
    // print_int_array(array, MAX_INPUT_LEN);
    printf(
        "Total pivot comparisons: "
        "%d\n",
        pivot_comparison_count);

    return 0;
}

void quicksort(int **array, int l, int r, int *pivot_comparison_count,
               PivotChoiceMode pivot_coice_mode, VerboseMode verbose_mode) {
    // Run quicksort on array from indexes l to r       [1  ,2  ,3  ,4  ,5  ]
    //                                                    l       p       r
    //                                                    0   1   2   3   4
    // Counts number of comparisons between pivots and array elements

    if (verbose_mode == VERBOSE_ON) printf("Running on subarray:\n");
    if (verbose_mode == VERBOSE_ON) print_int_array(&((*array)[l]), r - l + 1);

    if (r - l <= 0) {
        return;
    }

    int pivot_index = choose_pivot(*array, l, r, pivot_coice_mode);
    partition_around_pivot(array, l, r, &pivot_index);

    if (verbose_mode == VERBOSE_ON) printf("Partitioned\n");
    if (verbose_mode == VERBOSE_ON) print_int_array(&((*array)[l]), r - l + 1);
    if (verbose_mode == VERBOSE_ON) printf("Left\n");
    if (verbose_mode == VERBOSE_ON)
        print_int_array(&((*array)[l]), pivot_index - l);
    if (verbose_mode == VERBOSE_ON) printf("Right\n");
    if (verbose_mode == VERBOSE_ON)
        print_int_array(&((*array)[pivot_index + 1]), r - pivot_index);
    if (verbose_mode == VERBOSE_ON) printf("Pivot\n");
    if (verbose_mode == VERBOSE_ON) printf("%d\n", (*array)[pivot_index]);

    *pivot_comparison_count += pivot_index - l;
    *pivot_comparison_count += r - pivot_index;
    if (verbose_mode == VERBOSE_ON)
        printf("Pivot comparisons: %d\n", *pivot_comparison_count);
    if (verbose_mode == VERBOSE_ON) printf("\n");

    quicksort(array, l, pivot_index - 1, pivot_comparison_count,
              pivot_coice_mode, verbose_mode);
    quicksort(array, pivot_index + 1, r, pivot_comparison_count,
              pivot_coice_mode, verbose_mode);
}

int choose_pivot(int *array, int l, int r, PivotChoiceMode mode) {
    // returns index of pivot element
    if (mode == PIVOT_CHOICE_MODE_FIRST) {
        return l;
    }
    if (mode == PIVOT_CHOICE_MODE_LAST) {
        return r;
    }
    if (mode == PIVOT_CHOICE_MODE_MEDIAN) {
        int first = array[l];
        int middle_index;
        if ((r - l + 1) % 2 == 0) {
            middle_index = (r - l + 1) / 2 + l - 1;
            /* code */
        } else {
            middle_index = (r - l + 1) / 2 + l;
        }

        int middle = array[middle_index];
        int last = array[r];
        // First element is median
        if ((last < first && first < middle) ||
            (middle < first && first < last)) {
            return l;
        }
        // Last element is median
        if ((first < last && last < middle) ||
            (middle < last && last < first)) {
            return r;
        }
        // Middle element is median
        return middle_index;
    }
    return -1;
}

void swap_elements(int **array, int i, int j) {
    int aux = (*array)[i];
    (*array)[i] = (*array)[j];
    (*array)[j] = aux;
}

void partition_around_pivot(int **array, int l, int r, int *pivot) {
    // Partition elements of array around pivot (first element of array)
    // returns new pivot index
    int pivot_value = (*array)[*pivot];
    swap_elements(array, l, *pivot);
    *pivot = l;
    int i = l + 1;
    for (size_t j = l + 1; j <= r; j++) {
        if ((*array)[j] < pivot_value) {
            swap_elements(array, i, j);
            i++;
        }
    }
    swap_elements(array, *pivot, i - 1);
    *pivot = i - 1;
}

int *generate_array() {
    // int *array = malloc(sizeof(int) * MAX_INPUT_LEN);

    // array[0] = 3;
    // array[1] = 8;
    // array[2] = 2;
    // array[3] = 5;
    // array[4] = 1;
    // array[5] = 4;
    // array[6] = 7;
    // array[7] = 6;
    // return array;
    int *input = malloc(sizeof(int) * MAX_INPUT_LEN);

    // Read input file
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen("Course1/Week3/quicksort/input.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    int i = 0;
    while (((read = getline(&line, &len, fp)) != -1) && i < MAX_INPUT_LEN) {
        input[i] = atoi(line);
        i++;
    }

    fclose(fp);
    if (line) free(line);
    return input;
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
