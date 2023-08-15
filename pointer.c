#include <stdio.h>

int num1 = 1;
int num2 = 2;

void swapNums(int *arg1, int *arg2) {
  int temp = *arg1;
  *arg1 = *arg2;
  *arg2 = temp;
}

int main() {
  int *ptr1 = &num1; // Pointer to num1
  int *ptr2 = &num2; // Pointer to num2

  swapNums(ptr1, ptr2);

  printf("num1: %d\n", num1);
  printf("num2: %d\n", num2);

  return 0;
}
