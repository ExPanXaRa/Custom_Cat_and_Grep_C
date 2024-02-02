#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readfile(char *argv[], int *error, int argc, int file_num, int *cycle);
void flag_checking(FILE *fp, int regime, int *error, char *argv[], int kolvo,
                   char *filename, int argc);
void vanil(char *line, int read, char *argv[], int *count, int mode, int kolvo,
           char *filename, int num_of_str, int argc, int *error);
int flag_detector(char *argv[], char **filename, int file_num);
void post_while_print(int kolvo, int mode, int count, char *filename);
void sym_by_sym_check(char *line, int read, char *argv[], int *checker,
                      char *filename, int e_debuff, int kolvo);
void to_low(char *line, char *argv[], int read, int *checker, char *filename,
            int kolvo);
void o_print(int checker, char *filename, int argv_len, int read, char *line,
             int i, int kolvo);
void func_f(char *argv[], int *error, char *line, int *checker);
int e_checker(char *argv[], int argc);
int mode_develop(char *argv[], int *error, int regime);
void print_vanil(int checker, int kolvo, char *line, int read, int mode,
                 int num_of_str, char *filename, int *count);
void sym_by_for_o(char *line, int read, char *argv[], int *checker,
                  char *filename, int e_debuff, int kolvo);

int main(int argc, char *argv[]) {
  int error = 0, cycle = 0;
  int check_e = e_checker(argv, argc);
  int i = 2 * check_e;
  for (; i < argc; i++) {
    readfile(argv, &error, argc, i, &cycle);
  }

  if (error != 0) {
    printf("ERROR %d", error);
  }
  return 0;
}

void readfile(char *argv[], int *error, int argc, int file_num, int *cycle) {
  if ((argv[1][0] == '-' && file_num != argc - 1) || argv[1][0] != '-') {
    int kolvo = 0;
    FILE *fp;
    char *filename = NULL;
    // обработка с флагом/без флага
    int regime = flag_detector(argv, &filename, file_num);
    fp = fopen(filename, "r");
    // определение один или более файлов
    if (*cycle == 0 && ((regime == 1 && argc + 2 - file_num < 4) ||
                        (regime == 0 && argc + 2 - file_num < 5))) {
      kolvo = 0;
    } else {
      kolvo = 1;
      (*cycle)++;
    }
    if ((file_num + 1 < argc && regime == 0) ||
        regime == 1) {  // обработка лишних вызовов при отсутствии флага
      if (!strcmp(argv[1], "-s") && fp == NULL) {
      } else if (fp != NULL) {
        flag_checking(fp, regime, error, argv, kolvo, filename, argc);
      } else {
        *error = 1;
      }
    }
    if (filename) free(filename);
    if (fp != NULL) fclose(fp);
  }
}

void flag_checking(FILE *fp, int regime, int *error, char *argv[], int kolvo,
                   char *filename, int argc) {
  size_t len = 0;
  int read = 0;
  char *line = NULL;
  int count = 0, count_str = 0, mode = 0;
  // обработка флагов
  mode = mode_develop(argv, error, regime);

  while ((read = getline(&line, &len, fp)) != -1 && *error == 0) {
    count_str++;
    vanil(line, read, argv, &count, mode, kolvo, filename, count_str, argc,
          error);
  }
  // печатать без содержимого
  if (*error == 0) post_while_print(kolvo, mode, count, filename);
  if (line) free(line);
}

void vanil(char *line, int read, char *argv[], int *count, int mode, int kolvo,
           char *filename, int num_of_str, int argc, int *error) {
  int checker = 0;
  if (mode == 4) {
    to_low(line, argv, read, &checker, filename, kolvo);
  } else if (mode == 5) {
    sym_by_sym_check(line, read, argv, &checker, filename, 2, kolvo);
    checker = (checker > 0 ? 0 : 1);  // реверс поиск
  } else if (mode == 9) {
    int check_e = e_checker(argv, argc);
    for (int m = 2; m <= check_e * 2; m = m + 2) {
      sym_by_sym_check(line, read, argv, &checker, filename, m, kolvo);
    }
  } else if (mode == 8) {
    func_f(argv, error, line, &checker);
  } else {
    sym_by_sym_check(line, read, argv, &checker, filename, 2, kolvo);
  }

  print_vanil(checker, kolvo, line, read, mode, num_of_str, filename, count);
}

int flag_detector(char *argv[], char **filename, int file_num) {
  int regime = 0;
  if (argv[1][0] != '-') {  // обработка с флагом/без флага
    (*filename) = (char *)malloc(sizeof(char) * (strlen(argv[file_num]) + 1));
    strcpy((*filename), argv[file_num]);
    argv[2] = argv[1];
    regime = 1;
  } else {
    (*filename) =
        (char *)malloc(sizeof(char) * (strlen(argv[file_num + 1]) + 1));
    strcpy((*filename), argv[file_num + 1]);
  }
  return regime;
}

void post_while_print(int kolvo, int mode, int count, char *filename) {
  if (kolvo == 0) {
    if (mode == 1) {
      printf("%d\n", count);
    } else if (mode == 2 && count > 0) {
      printf("%s\n", filename);
    }
  } else {
    if (mode == 1) {
      printf("%s:%d\n", filename, count);
    } else if (mode == 2 && count > 0) {
      printf("%s\n", filename);
    }
  }
}

void to_low(char *line, char *argv[], int read, int *checker, char *filename,
            int kolvo) {
  char *buffer = NULL;
  if (line != NULL) {
    buffer = (char *)malloc(strlen(line) * sizeof(char));
  }
  for (int i = 0; i < (int)strlen(line); i++) {
    buffer[i] = line[i];
    line[i] = tolower(line[i]);
  }
  for (int i = 0; i < (int)strlen(argv[2]); i++) {
    argv[2][i] = tolower(argv[2][i]);
  }

  sym_by_sym_check(line, read, argv, checker, filename, 2, kolvo);

  for (int i = 0; i < (int)strlen(line); i++) {
    line[i] = buffer[i];
  }
  if (buffer) free(buffer);
}

void sym_by_sym_check(char *line, int read, char *argv[], int *checker,
                      char *filename, int e_debuff, int kolvo) {
  if (!strcmp(argv[1], "-o")) {
    sym_by_for_o(line, read, argv, checker, filename, e_debuff, kolvo);
  } else {
    if (strstr(line, argv[e_debuff]) != NULL) (*checker)++;
  }
}

void o_print(int checker, char *filename, int argv_len, int read, char *line,
             int i, int kolvo) {
  if (kolvo == 0) {
    if (checker != 0) {
      printf("\n");
    }
    for (int j = 0; j < argv_len && i + j < read; j++) {
      printf("%c", line[i + j]);
    }
  } else {
    if (checker == 0) {
      printf("%s:", filename);
    } else {
      printf("\n");
    }
    for (int j = 0; j < argv_len && i + j < read; j++) {
      printf("%c", line[i + j]);
    }
  }
}

void func_f(char *argv[], int *error, char *line, int *checker) {
  FILE *fp2;
  fp2 = fopen(argv[2], "r");
  if (fp2 == NULL) {
    *error = 1;
  } else {
    size_t len_arg = 0;
    char *line_arg = NULL;
    while ((getline(&line_arg, &len_arg, fp2)) != -1) {
      if (strstr(line, line_arg) != NULL) (*checker)++;
    }
    if (line_arg) free(line_arg);
  }
  if (fp2 != NULL) fclose(fp2);
}

int e_checker(char *argv[], int argc) {
  int check_e = 0;
  if (argc > 3) {
    if (!strcmp(argv[1], "-e") && !strcmp(argv[3], "-e")) {
      for (int j = 1; j < argc; j++) {
        if (!strcmp(argv[j], "-e")) check_e++;
      }
    }
  }
  return (check_e > 0 ? check_e : 1);
}

int mode_develop(char *argv[], int *error, int regime) {
  int mode = 0;
  if (!strcmp(argv[1], "-c")) {  //
    mode = 1;
  } else if (!strcmp(argv[1], "-l")) {  //
    mode = 2;
  } else if (!strcmp(argv[1], "-n")) {  //
    mode = 3;
  } else if (!strcmp(argv[1], "-i")) {  //
    mode = 4;
  } else if (!strcmp(argv[1], "-v")) {  //
    mode = 5;
  } else if (!strcmp(argv[1], "-h")) {  //
    mode = 6;
  } else if (!strcmp(argv[1], "-o")) {  //
    mode = 7;
  } else if (!strcmp(argv[1], "-f")) {  //
    mode = 8;
  } else if (!strcmp(argv[1], "-e")) {  //
    mode = 9;
  } else {
    if (regime == 1 || !strcmp(argv[1], "-s")) {
      mode = 0;
    } else {
      *error = 2;
    }
  }
  return mode;
}

void print_vanil(int checker, int kolvo, char *line, int read, int mode,
                 int num_of_str, char *filename, int *count) {
  if (checker > 0) {
    if (kolvo == 0) {
      if (line[read] == '\0' && line[read - 1] != '\n') line[read] = '\n';
      if (mode == 0 || mode == 4 || mode == 5 || mode == 6 || mode == 9 ||
          mode == 8) {
        printf("%s", line);
      } else if (mode == 3) {
        printf("%d:%s", num_of_str, line);
      } else if (mode == 7) {
        printf("\n");
      }
    } else {
      if (line[read] == '\0' && line[read - 1] != '\n') line[read] = '\n';
      if (mode == 0 || mode == 4 || mode == 5 || mode == 9 || mode == 8) {
        printf("%s:%s", filename, line);
      } else if (mode == 3) {
        printf("%s:%d:%s", filename, num_of_str, line);
      } else if (mode == 6) {
        printf("%s", line);
      } else if (mode == 7) {
        printf("\n");
      }
    }
    *count = *count + 1;
  }
}

void sym_by_for_o(char *line, int read, char *argv[], int *checker,
                  char *filename, int e_debuff, int kolvo) {
  for (int i = 0; i < read; i++) {
    if (line[i] == argv[e_debuff][0]) {
      int loc_checker = 0;
      int argv_len = strlen(argv[e_debuff]);
      for (int j = 1; j < argv_len && i + j <= read; j++) {
        if (line[i + j] != argv[e_debuff][j] || i + j + 1 > read)
          loc_checker = 1;
      }
      if (loc_checker == 0) {
        if (!strcmp(argv[1], "-o"))
          o_print(*checker, filename, argv_len, read, line, i, kolvo);
        (*checker)++;
      }
    }
  }
}