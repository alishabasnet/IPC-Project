/******************************************************************************
Assignment 1 - Milestone 3
Full Name  : Alisha Basnet
Student ID#: 161963210
Email      : abasnet9@myseneca.ca
Section    : NCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "core.h"
#include <stdio.h>

// As demonstrated in the course notes:
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void) {
  // Discard all remaining char's from the standard input buffer:
  while (getchar() != '\n') {
    ; // do nothing!
  }
}

// Wait for user to input the "enter" key to continue
void suspend(void) {
  printf("<ENTER> to continue...");
  clearInputBuffer();
  putchar('\n');
}

int inputInt() {
  int x;
  char newLine = 'x';
  int value;
  for (x = 0; x == 0;) {
    scanf("%d%c", &value, &newLine);
    if (newLine != '\n') {
      clearInputBuffer();
      printf("Error! Input a whole number: ");
    } else {
      x++;
    }
  }
  return value;
}

int inputIntPositive() {
  int x;
  char newLine = 'x';
  int value;
  for (x = 0; x == 0;) {
    scanf("%d%c", &value, &newLine);
    if (newLine != '\n') {
      clearInputBuffer();
      printf("Error! Input a whole number: ");
    } else if (value <= 0) {
      printf("ERROR! Value must be > 0: ");
    } else {
      x++;
    }
  }
  return value;
}

int inputIntRange(int lower, int upper) {
  int x;
  char newLine = 'x';
  int value;
  for (x = 0; x == 0;) {
    scanf("%d%c", &value, &newLine);
    if (newLine != '\n') {
      clearInputBuffer();
      printf("Error! Input a whole number: ");
    } else if (value < lower || value > upper) {
      printf("ERROR! Value must be between %d and %d inclusive: ", lower,
             upper);
    } else {
      x++;
    }
  }
  return value;
}

char inputCharOption(const char valid[]) {
  int x, exit;
  char value;
  for (x = 0; x == 0;) {
    scanf(" %c", &value);
    for (exit = 0; valid[exit] != '\0'; exit++) {
      if (value == valid[exit]) {
        x++;
      }
    }
    if (x == 0) {
      printf("ERROR: Character must be one of [%s]: ", valid);
    }
  }
  clearInputBuffer();

  return value;
}

void inputCString(char *str, int min, int max) {
  int exit = 0;
  char ch;
  int x = 0;
  while (!exit) {
    ch = getchar();
    if (x < max)
      str[x] = ch;
    x++;
    if (min == max && ch == '\n') {
      if (x != min + 1) {
        printf("ERROR: String length must be exactly %d chars: ", min);
        x = 0;
      } else {
        exit = 1;
        str[x - 1] = '\0';
      }
    } else if (min < max && ch == '\n') {
      if (x > max + 1) {
        printf("ERROR: String length must be no more than %d chars: ", max);
        x = 0;
      } else if (x < min + 1) {
        printf("ERROR: String length must be between %d and %d chars: ", min,
               max);
        x = 0;
      } else {
        exit = 1;
        str[x - 1] = '\0';
      }
    }
  }
}

void displayFormattedPhone(const char *str) {
  int x = 0, NONDIGIT = 0;
  if (str == NULL) {
    printf("(___)___-____");
  } else {
    for (x = 0; str[x] != '\0' && NONDIGIT == 0; x++) {
      if (str[x] < '0' || str[x] > '9') {
        NONDIGIT++;
      }
    }
    if (x == 10 && NONDIGIT == 0) {
      printf("(%c%c%c)%c%c%c-%c%c%c%c", str[0], str[1], str[2], str[3], str[4],
             str[5], str[6], str[7], str[8], str[9]);
    } else {
      printf("(___)___-____");
    }
  }
}

void assignCString(char *source, const char *value) {
  int i;
  for (i = 0; value[i] != '\0'; i++) {
    source[i] = value[i];
  }
  source[i] = '\0';
}