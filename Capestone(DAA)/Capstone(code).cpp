#include <stdio.h>
#include <stdlib.h>

void merge(int* nums, int* indices, int* counts, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int* leftIndices = (int*)malloc(leftSize * sizeof(int));
    int* rightIndices = (int*)malloc(rightSize * sizeof(int));
    
    for (int i = 0; i < leftSize; ++i)
        leftIndices[i] = indices[left + i];
    for (int i = 0; i < rightSize; ++i)
        rightIndices[i] = indices[mid + 1 + i];
    
    int i = 0, j = 0, k = left, rightCounter = 0;
    
    while (i < leftSize && j < rightSize) {
        if (nums[leftIndices[i]] <= nums[rightIndices[j]]) {
            counts[leftIndices[i]] += rightCounter;
            indices[k++] = leftIndices[i++];
        } else {
            rightCounter++;
            indices[k++] = rightIndices[j++];
        }
    }
    
    while (i < leftSize) {
        counts[leftIndices[i]] += rightCounter;
        indices[k++] = leftIndices[i++];
    }
    
    while (j < rightSize) {
        indices[k++] = rightIndices[j++];
    }
    
    free(leftIndices);
    free(rightIndices);
}

void mergeSort(int* nums, int* indices, int* counts, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(nums, indices, counts, left, mid);
        mergeSort(nums, indices, counts, mid + 1, right);
        merge(nums, indices, counts, left, mid, right);
    }
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* counts = (int*)calloc(numsSize, sizeof(int));
    int* indices = (int*)malloc(numsSize * sizeof(int));
    
    for (int i = 0; i < numsSize; ++i)
        indices[i] = i;
    
    mergeSort(nums, indices, counts, 0, numsSize - 1);
    
    free(indices);
    return counts;
}

int main() {
    int nums[] = {5, 2, 6, 1};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* result = countSmaller(nums, numsSize, &returnSize);
    
    printf("Input: [");
    for (int i = 0; i < numsSize; ++i) {
        printf("%d", nums[i]);
        if (i < numsSize - 1)
            printf(", ");
    }
    printf("]\nOutput: [");
    for (int i = 0; i < returnSize; ++i) {
        printf("%d", result[i]);
        if (i < returnSize - 1)
            printf(", ");
    }
    printf("]\n");
    
    free(result);
    return 0;
}

