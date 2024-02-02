#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readfile(char *argv[], int *error, int argc, int file_num);
void flag_checking(FILE *fp, int *regime, int *error, char *x);
void just_space(int num);
void b_func(char read, int *count, int *b_read);
void e_func(int read);
void s_func(char read, int *check, int *b_read, int *bb_read);
void n_func(int read, int *b_read, int *count);
void t_func(int read);
void func_E(int read);
void func_T(int read);
void pre_b_n(int read, int *check);
int flag_detector(char *argv[], char **filename, int file_num, int argc);

int main(int argc, char *argv[]) {
  int error = 0;
  for (int i = 1; i < argc; i++) {
    readfile(argv, &error, argc, i);
  }
  if (error > 0) {
    printf("ERROR %d", error);
  }
  return 0;
}

void readfile(char *argv[], int *error, int argc, int file_num) {
  if ((argv[1][0] == '-' && file_num != argc - 1) || argv[1][0] != '-') {
    int regime = 0;
    FILE *fp;
    char *filename = NULL;
    regime = flag_detector(argv, &filename, file_num, argc);
    fp = fopen(filename, "r");

    if ((file_num != argc - 1 && regime == 0) || regime == 1) {
      if (fp != NULL) {
        flag_checking(fp, &regime, error, argv[1]);
      } else {
        *error = 1;
      }
    }
    if (filename) free(filename);
    if (fp != NULL) fclose(fp);
  }
}

void flag_checking(FILE *fp, int *regime, int *error, char *x) {
  int read, b_read = 0, bb_read = 0;
  int count = 1, check = 0;
  while ((read = fgetc(fp)) != -1 && *error != 1) {
    if (strcmp(x, "-b") == 0 || strcmp(x, "--number-nonblank") == 0) {
      // нумерует непустые строки
      pre_b_n(read, &check);
      b_func(read, &count, &b_read);
    } else if (strcmp(x, "-e") == 0) {
      e_func(read);  // показывает $ у перен. стр и +v
    } else if (strcmp(x, "-n") == 0 || strcmp(x, "--number") == 0) {
      // нумерует все вых. строки
      pre_b_n(read, &check);
      n_func(read, &b_read, &count);
    } else if (strcmp(x, "-s") == 0 || strcmp(x, "--squeeze-blank") == 0) {
      // сжимает несколько смежн строк
      s_func(read, &check, &b_read, &bb_read);
    } else if (strcmp(x, "-t") == 0) {  // показывает табы и неотобр. символы
      t_func(read);
    } else if (strcmp(x, "-E") == 0) {
      func_E(read);
    } else if (strcmp(x, "-T") == 0) {
      func_E(read);
    } else {
      if (*regime == 1) {
        printf("%c", read);
      } else {
        *error = 2;
      }
    }
  }
}

void b_func(char read, int *count, int *b_read) {
  if (read == '\n' && *b_read == '\n') {
    // printf("       ");
    printf("%c", read);
  } else {
    n_func(read, b_read, count);
  }
}

void e_func(int read) {
  if ((read >= 0 && read <= 31) ||
      read == 127) {  // проверка на непечатаемый символ
    if (read == '\n') {
      printf("$%c", read);
    } else if (read == '\t') {
      printf("%c", read);
    } else {
      printf("^%c", read ^ 64);
    }
  } else {
    printf("%c", read);
  }
}

void n_func(int read, int *b_read, int *count) {
  if (*b_read == '\n') printf("%6d\t", *count);
  if (read == '\n') *count = *count + 1;
  printf("%c", read);
  *b_read = read;
}

void s_func(char read, int *check, int *b_read, int *bb_read) {
  if (*check < 2 && read != '\n') {
    (*check)++;
    printf("%c", read);
    if (*check == 1) {
      *bb_read = read;
    } else {
      *b_read = read;
    }
  } else {
    if (*bb_read != '\n' || read != '\n' || *b_read != '\n') printf("%c", read);
    *bb_read = *b_read;
    *b_read = read;
  }
}

void t_func(int read) {
  if ((read >= 0 && read <= 31) ||
      read == 127) {  // проверка на непечатаемый символ
    if (read == '\n') {
      printf("%c", read);
    } else if (read == '\t') {
      printf("^I");
    } else {
      printf("^%c", read ^ 64);
    }
  } else {
    printf("%c", read);
  }
}

void func_E(int read) {
  if (read == '\n') {
    printf("$%c", read);
  } else {
    printf("%c", read);
  }
}

void func_T(int read) {
  if (read == '\t') {
    printf("^I");
  } else {
    printf("%c", read);
  }
}

void pre_b_n(int read, int *check) {
  if (read != EOF && *check == 0) {
    printf("%6d\t", 1);
    (*check)++;
  }
}

int flag_detector(char *argv[], char **filename, int file_num, int argc) {
  int regime = 0;
  if (argv[1][0] != '-') {  // обработка с флагом или без флага
    (*filename) = (char *)malloc(sizeof(char) * (strlen(argv[file_num]) + 2));
    strcpy((*filename), argv[file_num]);
    if (argv[argc - 1][0] != '-') argv[2] = argv[1];
    regime = 1;
  } else {
    (*filename) =
        (char *)malloc(sizeof(char) * (strlen(argv[file_num + 1]) + 2));
    strcpy((*filename), argv[file_num + 1]);
  }
  return regime;
}