#include "s21_cat.h"

#include <math.h>

void readFlags(int argc, char* argv[], flags* flags_list) {
  unsigned count = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      count++;
      while (count < strlen(argv[i])) {
        if (argv[i][count] == 'b') {
          flags_list->b = 1;
        } else if (argv[i][count] == 'e') {
          flags_list->e = 1, flags_list->v = 1;
        } else if (argv[i][count] == 'E') {
          flags_list->e = 1;
        } else if (argv[i][count] == 'n') {
          flags_list->n = 1;
        } else if (argv[i][count] == 's') {
          flags_list->s = 1;
        } else if (argv[i][count] == 't') {
          flags_list->t = 1, flags_list->v = 1;
        } else if (argv[i][count] == 'T') {
          flags_list->t = 1;
        } else if (argv[i][count] == 'v') {
          flags_list->v = 1;
        } else if (strcmp(argv[i], "--number-nonblank") == 0) {
          flags_list->b = 1;
          break;
        } else if (strcmp(argv[i], "--number") == 0) {
          flags_list->n = 1;
          break;
        } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
          flags_list->s = 1;
          break;
        } else {
          printf(
              "s21_cat: illegal option -- %c\nusage: s21_cat [-benstv] "
              "[file "
              "...]\n",
              argv[i][count]);
          exit(1);
        }
        count++;
      }
    }
    count = 0;
  }
}

void flag_s(char* str, int* k) {
  if (strlen(str) == 1) {
    *k = 1;
  }
  if (strlen(str) > 1) {
    *k = 0;
  }
}

void flag_b(flags flags_list, char* str, int* j) {
  if (flags_list.b == 1 && flags_list.t != 1) {
    char str1[4096] = {0};
    if (strlen(str) > 1) {
      snprintf(str1, sizeof(str1), "%6d\t", *(j));
      *(j) += 1;
    }
    strncat(str1, str, strlen(str));
    int size = strlen(str1) + strlen(str);
    strncpy(str, str1, size);
  }
}

void flag_e(flags flags_list, char* str) {
  if (flags_list.e == 1) {
    int length = strlen(str);
    if (str[length - 1] == '\n') {
      str[length - 1] = '$';
      strncat(str, "\n\0", 2);
    }
  }
}

void flag_n(flags flags_list, char* str, int* j) {
  if (flags_list.n == 1 && flags_list.b != 1) {
    char str1[4096] = {0};
    snprintf(str1, sizeof(str1), "%6d\t", *(j));
    strncat(str1, str, strlen(str));
    int size = strlen(str) + strlen(str1);
    strncpy(str, str1, size);
    *(j) += 1;
  }
}

void flag_t(flags flags_list, char* str) {
  if (flags_list.t == 1 && flags_list.b != 1) {
    char str1[4096] = {0};
    int length = strlen(str);
    int b = 0, l = 0;
    while (b <= length) {
      str1[l] = str[b];
      if (str[b] == '\t') {
        str1[l] = '^';
        str1[l + 1] = 'I';
        l++;
      }
      b++;
      l++;
    }
    length = length + strlen(str1);
    strncpy(str, str1, length);
  }
}

void flag_bt(flags flags_list, char* str, int* j) {
  if (flags_list.t == 1 && flags_list.b == 1) {
    char str1[4096] = {0};
    char str2[4096] = {0};
    if (strlen(str) > 1) {
      snprintf(str1, sizeof(str1), "%6d\t", *(j));
      *(j) += 1;
    }
    int length = strlen(str);
    size_t b = 0, l = 0;
    while (b <= strlen(str)) {
      str2[l] = str[b];
      if (str[b] == '\t') {
        str2[l] = '^';
        str2[l + 1] = 'I';
        l++;
      }
      b++;
      l++;
    }
    length = length + strlen(str2);
    strncpy(str, str2, length);
    strncat(str1, str, strlen(str));
    int size = strlen(str1) + strlen(str);
    strncpy(str, str1, size);
  }
}

void flag_v(flags flags_list, char* str) {
  if (flags_list.v == 1) {
    char str1[4096] = "\0";
    int length = strlen(str);
    int b = 0, l = 0;
    while (b <= length) {
      unsigned char ch = str[b];
#if defined(__linux__)
      if (ch < 32 && ch != 9 && ch != 10 && ch != 13 && ch != 0) {
        str1[l] = '^';
        str1[l + 1] = str[b] + 64;
        l++;
      } else if (ch == 127 || ch == 255) {
        str1[l] = '^';
        str1[l + 1] = '?';
        l++;
      } else if (ch > 127 && ch < 160) {
        str1[l] = 'M';
        str1[l + 1] = '-';
        str1[l + 2] = '^';
        str1[l + 3] = str[b] - 64;
        l = l + 3;
      } else if (ch > 159 && ch < 255) {
        // printf("tut");
        str1[l] = 'M';
        str1[l + 1] = '-';
        str1[l + 2] = str[b] + 128;
        l = l + 2;
      }
      if (((ch > 0) && (ch < 9)) || ((ch > 10) && (ch < 32))) {
        str1[l] = '^';
        str1[l + 1] = str[b] + 64;
        l++;
      } else if (ch == 127) {
        str1[l] = '^';
        str1[l + 1] = '?';
        l++;
      } else {
        str1[l] = str[b];
      }
      b++;
      l++;
#elif defined(__APPLE__)
      if (ch > 127 && ch < 160) {
        str1[l] = 'M';
        str1[l + 1] = '-';
        str1[l + 2] = '^';
        str1[l + 3] = str[b] - 64;
        l = l + 3;
      } else if (ch < 32 && ch != 9 && ch != 10 && ch != 13 && ch != 0) {
        str1[l] = '^';
        str1[l + 1] = str[b] + 64;
        l++;
      } else if (ch == 127) {
        str1[l] = '^';
        str1[l + 1] = '?';
        l++;
      } else {
        str1[l] = str[b];
      }
      b++;
      l++;
#endif
    }
    length = length + strlen(str1);
    strncpy(str, str1, length);
  }
}

void adaptationFile(int argc, char* argv[], flags flags_list) {
  FILE* work_file = NULL;
  int count = 1, k = 0, j = 1;
  static char str[4096];
  while (count < argc) {
    if (*argv[count] == '-') {
      count++;
    } else {
      work_file = fopen(argv[count], "r");
      if (work_file == NULL) {
        printf("s21_cat: %s: No such file or directory\n", argv[count]);
        count++;
      } else {
        count++;
        while (fgets(str, 4096, work_file)) {
          if (flags_list.s == 1) {
            if (k == 1 && strlen(str) == 1) {
              continue;
            }
            flag_s(str, &k);
          }
          flag_v(flags_list, str);
          flag_b(flags_list, str, &j);
          flag_n(flags_list, str, &j);
          flag_t(flags_list, str);
          flag_bt(flags_list, str, &j);
          flag_e(flags_list, str);
          printf("%s", str);
        }
        fclose(work_file);
      }
    }
  }
}

int main(int argc, char* argv[]) {
  flags flags_list = {0, 0, 0, 0, 0, 0};
  readFlags(argc, argv, &flags_list);
  adaptationFile(argc, argv, flags_list);
  return 0;
}
