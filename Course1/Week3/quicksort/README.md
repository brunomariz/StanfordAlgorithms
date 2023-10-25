# Quick Sort Algorithm

For this assignment, the quick sort algorithm was implemented in C. According to the lesson instructions, the algorithm has the following pseudocode structure:

## Main algorithm

```c
quicksort(A, l, r)
    n = r - l + 1;
    if n == 0
        return;
    p = choose_pivot(A, l, r); // Chooses pivot (index) with some defined strategy
    partition_around_pivot(A, l, r, p); // Partitions A around P (and updates p)
    quicksort(A, l, p-1); // Recursevely call quicksort on partition to the left of the pivot
    quicksort(A, p+1, r); // Recursevely call quicksort on partition to the right of the pivot 
```

## Choose pivot

The function for choosing a pivot can use 3 different strategies defined in the assignment:

- Choosing the first element of the array as the pivot
- Choosing the last element of the array as the pivot
- Choosign the median between the first, last and middle elements as pivot. In cases when the array has $2\cdot k$ elements, the middle element should be the $k^{th}$.

```c
choose_pivot(A, l, r, mode)
    if mode == first {
        return l;
    }
    else if mode == median{
        first = A[l];
        middle = A[(r - l + 1) / 2 - (r - l + 1) % 2]; // Middle index calculation equivalent to floor((r-l+1)/2)
        last = A[r];

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
    else if mode == last
        return r;
    return 0;
```

## Partition array

void partition_around_pivot(A, l, r, pivot_index) {
    // Partition elements of array around pivot (first element of array)
    pivot_value = A[*pivot_index];
    swap_elements(A, l, pivot_index);
    pivot_index = l;
    int i = l + 1;
    for (size_t j = l + 1; j <= r; j++) {
        if (A[j] < pivot_value) {
            swap_elements(array, i, j);
            i++;
        }
    }
    swap_elements(array, pivot_index, i - 1);
    pivot_index = i - 1;
}



<!-- gh-action-output -->
## Program output
```bash
$ make
$ ./Course1/Week3/quicksort/a.out 
================================================
Pivot choice strategy: first element of subarray
Total pivot comparisons: 162085
================================================
Pivot choice strategy: last element of subarray
Total pivot comparisons: 164123
================================================
Pivot choice strategy: median element between first, middle, and last elements of subarray
Total pivot comparisons: 138382
```
<!-- gh-action-output end -->
