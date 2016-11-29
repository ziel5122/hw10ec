#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int bSearch(int nums[], int size, int find);
int sSearch(int nums[], int size, int find);

void merge(int nums[], int left[], int right[], int size_left, int size_right);
void mergeSort(int nums[], int size);
void printDoubleArray(double arr[], int size);
void printIntArray(int arr[], int size);

int main() {
    srand(time(NULL));

    int num_values = 100;
    int value_increment = 10;
    int num_size = 10;

    int b_ops[num_values];
    int s_ops[num_values];
    double b_times[num_values];
    double s_times[num_values];
    int size = sizeof(b_ops) / sizeof(b_ops[0]);

    int ops_index = 0;

    while (ops_index < size) {
        b_ops[ops_index] = 0;
        s_ops[ops_index] = 0;
        b_times[ops_index] = 0;
        s_times[ops_index] = 0;
        int trials = 0;

        while (trials < 1000) {
            int nums_rand[num_size];
            int nums_sort[num_size];

            int x = 0;
            while (x < num_size) {
                int r = rand() % num_size;
                nums_rand[x] = r;
                nums_sort[x] = r;
                ++x;
            }

            mergeSort(nums_sort, num_size);

            int find = rand() % num_size;
            clock_t begin = clock();
            b_ops[ops_index] += bSearch(nums_sort, num_size, find);
            clock_t end = clock();
            b_times[ops_index] += (double)(end - begin) / CLOCKS_PER_SEC * 1000;

            begin = clock();
            s_ops[ops_index] += sSearch(nums_rand, num_size, find);
            end = clock();
            s_times[ops_index] += (double)(end - begin) / CLOCKS_PER_SEC * 1000;
            ++trials;
        }

        num_size += value_increment;
        ++ops_index;
    }

    printIntArray(b_ops, size);
    printIntArray(s_ops, size);

    printDoubleArray(b_times, size);
    printDoubleArray(s_times, size);
}

int bSearch(int nums[], int size, int find) {
    int min = 0, max = size-1, mid, i = 0;

    do {
        mid = (min + max) / 2;

        i++;
        if (nums[mid] == find)
            return i;

        if (nums[mid] > find)
            max = mid - 1;
        else
            min = mid + 1;
    } while (max > min);

    return i;
}

void merge(int nums[], int left[], int right[], int size_left, int size_right) {
    int i = 0, j = 0, k = 0;

    while (i < size_left && j < size_right) {
        if (left[i] < right[j])
            nums[k++] = left[i++];
        else
            nums[k++] = right[j++];
    }

    while (i < size_left)
        nums[k++] = left[i++];

    while (j < size_right)
        nums[k++] = right[j++];
}

void mergeSort(int nums[], int size) {
    if (size < 2) return;

    int mid = size >> 1;

    int* left = malloc(mid * sizeof(int));
    int* right = malloc((size-mid) * sizeof(int));

    int i = 0;
    while (i < mid) {
        left[i] = nums[i];
        i++;
    }

    int j = 0;
    while (i < size) {
        right[j] = nums[i];
        i++; j++;
    }

    mergeSort(left, mid);
    mergeSort(right, size-mid);
    merge(nums, left, right, mid, size-mid);

    free(left);
    free(right);
}

void printDoubleArray(double arr[], int size) {
    int i = 0;
    while (i < size)
        printf("%f,", arr[i++]);
    printf("\n\n");
}

void printIntArray(int arr[], int size) {
    int i = 0;
    while (i < size)
        printf("%d,", arr[i++]);
    printf("\n\n");
}

int sSearch(int nums[], int size, int find) {
    int i = 0;
    while (i < size) {
        if (nums[i] == find)
            return i+1;
        ++i;
    }

    return i;
}
