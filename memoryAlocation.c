#include <stdio.h>


int main(int argc, char *argv[]) {

  int size;

  printf("set the size of an array: ");
  scanf("%d", &size);
  printf("print %d\n", size);
  int arr[size];

  for (int i = 0; i < size; i++) {

    int newValue;

    printf("add value %d to array: ", i);
    scanf("%d", &newValue);

    arr[i] = newValue;

  }

  printf("Array after adding number:\n");
      for (int i = 0; i < size; i++) {
          printf("%d ", arr[i]);
      }
      printf("\n");

  return 0;
}
