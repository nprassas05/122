#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int leftChild(int);
int rightChild(int);
void min_heapify(int A[], int, int);
void build_min_heap(int A[], int);
void heap_sort(int A[], int);
void printArray(int A[], int);
void swap(int A[], int, int);
int removeMin(int H[], int);

#define MAX_SIZE 101

int main() {
  int n = 5;
  int A[MAX_SIZE];
  srand(time(NULL));

  int i, j;
  for (i = 0; i < 3; ++i, n += 5) {
    printf("Case %d:\n", i + 1);
    for (j = 1; j <= n; ++j) {
      A[j] = rand() % 100;
    }
    
    printf("Array before heapsort: ");
    printArray(A, n);
    heap_sort(A, n);
    printf("Array after heapsort: ");
    printArray(A, n);
    putc('\n', stdout);
  }
  
  return 0;
}

int leftChild(int i) {
  return 2 * i;
}

int rightChild(int i) {
  return (2 * i) + 1;
}

void min_heapify(int A[], int i, int n) {
  int left = leftChild(i);
  int right = rightChild(i);

  while (left <= n) {
    int rightValue = right <= n ? A[right] : INT_MAX;
    int leftValue = A[left];

    if (A[i] <= leftValue && A[i] <= rightValue) {
      return;
    }

    if (rightValue < leftValue) {
      swap(A, i, right);
      i = right;
    } else {
      swap(A, i, left);
      i = left;
    }

    /* set the new left and child chilren */
    left = leftChild(i);
    right = rightChild(i);
  }
}

void build_min_heap(int A[], int n) {
  /* run min_heapify on the internal nodes of
     the array, which are in the range [1, n) */
  for (int i = n / 2; i >= 1; --i) {
    min_heapify(A, i, n);
  }
}

void heap_sort(int A[], int n) {
  int *sortedArray = malloc(sizeof(int) * n);
  build_min_heap(A, n);

  int size = n;
  int i = 1;
  while (size > 0) {
    sortedArray[i++] = removeMin(A, size--);
  }

  /* copy the sorted array back over to the original array */
  for (i = 1; i <= n; ++i) {
    A[i] = sortedArray[i];
  }
  free(sortedArray);
}

void printArray(int A[], int n) {
  int i;
  for (i = 1; i <= n; ++i)
    printf("%d ", A[i]);
  printf("\n");
}

void swap(int A[], int i, int j) {
  int temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

int removeMin(int heap[], int n) {
  int elem = heap[1];
  heap[1] = heap[n];
  min_heapify(heap, 1, n);
  
  return elem;
}
