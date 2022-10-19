#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int capacity = 1;
int top = -1;
int *stack;

void print() {
  if (top != -1) {
    for (int i = 0; i <= top; i++)
      printf("[%2d]", stack[i]);
    puts("");
  }
}

void stackReduce() {
  stack = (int *)realloc(stack, capacity / 2 * sizeof(int));
  capacity /= 2;
}

void stackFull() {
  stack = (int *)realloc(stack, capacity * 2 * sizeof(int));
  capacity *= 2;
}

void push(int item) {
  if (top >= capacity - 1) {
    stackFull();
    stack[++top] = item;
    printf("doubling: %d", capacity);
    print();
  } else {
    stack[++top] = item;
    print();
  }
}

void pop() {
  if (top == -1) {
    printf("stack empty: cannot pop\n");
  } else {
    top -= 1;
    if (top == -1)
      printf("stack empty\n");
    else if (top + 1 <= capacity / 2) {
      stackReduce();
      printf("reducing size(/2): %d", capacity);
      print();
    } else
      print();
  }
}

int main(void) {
  stack = (int *)malloc(sizeof(int));
  FILE *f1 = fopen("in1.txt", "r"), *f2 = fopen("in2.txt", "r");
  if (!f1 | !f2) {
    puts("cannot open file!!");
    exit(1);
  }
  int num;
  while (!feof(f1)) {
    fscanf(f1, "%d", &num);
    if (num == -1) {
      printf("Pop ==>");
      pop();
    } else {
      printf("Push item: %d ==>", num);
      push(num);
    }
  }
  puts("최종 stack 출력");
  for (int i = top; i > -1; i--)
    printf("<%2d>\n", stack[i]);
  puts("");

  top = -1;
  capacity = 1;
  while (!feof(f2)) {
    fscanf(f2, "%d", &num);
    if (num == -1) {
      printf("Pop ==>");
      pop();
    } else {
      printf("Push item: %d ==>", num);
      push(num);
    }
  }
  puts("최종 stack 출력");
  for (int i = top; i > -1; i--)
    printf("<%2d>\n", stack[i]);
  puts("");

  fclose(f1);
  fclose(f2);
  return 0;
}