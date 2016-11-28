#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int bSearch(int nums[], int size, int find);
int sSearch(int nums[], int size, int find);

void merge(int nums[], int left[], int right[], int size_left, int size_right);
void mergeSort(int nums[], int size);

int main(int argc, char** argv) {
    srand(time(NULL));

    int nums[] = {1, 2, 3, 4, 5};
    int size = sizeof(nums) / sizeof(int);
    int b = bSearch(nums, size, 4);
    int s = sSearch(nums, size, 4);

    printf("%d\n", b);
    printf("%d\n", s);

    //mergeSort(nums, size);
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
    } while (max > mid);

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

    int left[mid];
    int right[size-mid];

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
        i = 0;
        while (i < mid+1) {
            printf("%d ", left[i]);
            printf("%d ", right[i++]);
        }
        printf("\n");

    mergeSort(left, mid);
    mergeSort(right, size-mid);
    merge(nums, left, right, mid, size-mid);

    i = 0;
    while (i < size) {
        printf("%d ", nums[i++]);
    }
    printf("\n");

    free(left);
    free(right);
}


int sSearch(int nums[], int size, int find) {
    int i = 0;
    while (i < size) {
        if (nums[i] == find)
            return i+1;
        ++i;
    }
}
