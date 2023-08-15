#include <stdio.h>
#include <stdlib.h> // Include the standard library for malloc and free

int main(int argc, char *argv[]) {

  int size;

  printf("Set the size of an array: ");
  scanf("%d", &size);
  printf("Size: %d\n", size);

  int *arr = (int *)malloc(size * sizeof(int)); // Allocate memory for the array

  if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < size; i++) {
    int newValue;

    printf("Add value %d to array: ", i);
    scanf("%d", &newValue);

    arr[i] = newValue;
  }

  printf("Array after adding numbers:\n");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // Don't forget to free the allocated memory when done
  free(arr);

  return 0;
}
