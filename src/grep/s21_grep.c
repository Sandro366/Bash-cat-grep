#include "s21_grep.h"

int main(int argc, char* argv[]) {
  Flags flags_list = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int count_pattern = 0, file_index = 0;
  char** templates = NULL;
  char** file = NULL;
  if (argc > 2) {
    readFlags(argc, argv, &flags_list);
    if (flags_list.f == 0) {
      templates = findTemplates(argc, argv, &count_pattern);
      file = findFiles(argc, argv, &file_index);
      file_open(file, templates, flags_list, file_index, count_pattern);
      for (int i = 0; i < count_pattern; i++) {
          free(templates[i]);
      }
      free(templates);
      for (int i = 0; i < file_index; i++) {
          free(file[i]);
      }
      free(file);
    } else {
      file = findFiles(argc, argv, &file_index);
      if (file_index >= 2) {
        templates = (char**)malloc(1 * sizeof(char*));
        flag_f(flags_list, file, templates, &count_pattern);
        file_open(file, templates, flags_list, file_index, count_pattern);
        for (int i = 0; i < count_pattern; i++) {
          free(templates[i]);
        }
        free(templates);
        for (int i = 0; i < file_index; i++) {
            free(file[i]);
        }
        free(file);
      }
    }
  }
  return 0;
}

void readFlags(int argc, char* argv[], Flags* flags_list) {
  int count = 0;
  for (int i = 1; i < argc; i++) {
    int size = (int)strlen(argv[i]);
    if (argv[i][0] == '-') {
      count++;
      while (count < size) {
        if (argv[i][count] == 'i') {
          flags_list->i = 1;
        } else if (argv[i][count] == 'v') {
          flags_list->v = 1;
        } else if (argv[i][count] == 'c') {
          flags_list->c = 1;
        } else if (argv[i][count] == 'l') {
          flags_list->l = 1;
        } else if (argv[i][count] == 'n') {
          flags_list->n = 1;
        } else if (argv[i][count] == 'h') {
          flags_list->h = 1;
        } else if (argv[i][count] == 's') {
          flags_list->s = 1;
        } else if (argv[i][count] == 'f') {
          flags_list->f = 1;
        } else if (argv[i][count] == 'o') {
          flags_list->o = 1;
        } else if (argv[i][count] == 'e') {
          while (argv[i][count] != '\0') count++;
        } else {
          fprintf(stderr, "s21_grep: Invalid argument");
          exit(1);
        }
        count++;
      }
      count = 0;
    }
  }
  if (flags_list->l) flags_list->c = 0;
}

char** findTemplates(int argc, char* argv[], int* count_pattern) {
  int flag = 0, count = 1;
  char** templates = (char**)malloc(1 * sizeof(char*));
  char** ptr;
  while (count < argc) {
    if (argv[count][0] == '-') {
      for (int q = 0; argv[count][q] != '\0'; q++) {
        if (argv[count][q] == 'e') {
          flag = 1;
          break;
        }
      }
    }
    count++;
  }
  if (flag == 1) {
    int i = 1;
    while (i < argc) {
      for (int j = 0; j <= (int)strlen(argv[i]); j++) {
        if (argv[i][0] == '-' && argv[i][j] == 'e' && argv[i][j + 1] == '\0') {
          templates[*count_pattern] = (char*)malloc(1000 * sizeof(char));
          strncpy(templates[*count_pattern], argv[i + 1], 999);
          ptr = (char**)realloc(templates, (*count_pattern + 2) * sizeof(char*));
          if (ptr != NULL) {
            templates = ptr;
            *(count_pattern) += 1;
            argv[i + 1] = "\0";
          }
        } else if (argv[i][0] == '-' && argv[i][j] == 'e' &&
                   argv[i][j + 1] != '\0') {
          templates[*count_pattern] = (char*)malloc(1000 * sizeof(char));
          strncpy(templates[*count_pattern], &argv[i][j + 1], 1);
          ptr = (char**)realloc(templates, (*count_pattern + 2) * sizeof(char*));
          if (ptr != NULL) {
            templates = ptr;
            *(count_pattern) += 1;
            argv[i] = "\0";
          }
        }
      }
      i++;
    }
  } else {
    if (argv[1][0] == '-' && argv[1][1] != '\0') {
      int y = 1;
      while (argv[y][0] == '-') {
        y++;
      }
      templates[0] = (char*)malloc(1000 * sizeof(char));
      strncpy(templates[0], argv[y], 999);
      ptr = (char**)realloc(templates, (*count_pattern + 2) * sizeof(char*));
      if (ptr != NULL) {
        templates = ptr;
        *(count_pattern) += 1;
        argv[y] = "\0";
      }
    } else {
      templates[0] = (char*)malloc(1000 * sizeof(char));
      strncpy(templates[*count_pattern], argv[1], 999);
      ptr = (char**)realloc(templates, (*count_pattern + 2) * sizeof(char*));
      if (ptr != NULL) {
        templates = ptr;
        *(count_pattern) += 1;
        argv[1] = "\0";
      }
    }
  }
  return templates;
}

char** findFiles(int argc, char* argv[], int* file_index) {
  int u = 1;
  char** file = (char**)malloc(1 * sizeof(char*));
  char** ptr = NULL;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-' && strcmp(argv[i], "\0") != 0) {
      ptr = (char**)realloc(file, (u += 1) * sizeof(char*));
      if (ptr != NULL) {
          file = ptr;
          file[*file_index] = (char*)malloc(1000 * sizeof(char));
          strncpy(file[*file_index], argv[i], 999);
          *(file_index) += 1;
      } else {
        exit(1);
      }
    }
  }
  return file;
}

void file_open(char** files_list, char** templates, Flags flags_list,
               int file_index, int count_pattern) {
  FILE* file_ptr = NULL;
  int i = 0;
  if (flags_list.f) {
    i = 1;
  }
  while (i < file_index) {
    file_ptr = fopen(files_list[i], "r");
    if (!file_ptr) {
      if (!flags_list.s) {
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                files_list[i]);
      }
      i++;
    } else {
      file_read(file_ptr, templates, flags_list, file_index, files_list[i],
                count_pattern);
      fclose(file_ptr);
      i++;
    }
  }
}

void file_read(FILE* file_ptr, char** templates, Flags flags_list,
               int file_index, char* fileUse, int count_pattern) {
  int reg_flag = flags_list.i ? (REG_EXTENDED | REG_ICASE) : REG_EXTENDED;
  if (flags_list.f) {
    file_index--;
  }
  regex_t regex;
  regmatch_t regmatch;
  size_t bufSize = 0;
  int count = 0;
  char* buffer = NULL;
  char* template_buf = NULL;
  char* tmp;
  int length = 0;
  for (int j = 0; j < count_pattern; j++) {
    int len_arg = (int)strlen(templates[count]);
    tmp = realloc(template_buf, sizeof(char) * (length + len_arg + 2));
    if (tmp) {
      template_buf = tmp;
      if (length != 0) template_buf[length++] = '|';
      strcpy(&template_buf[length], templates[count]);
    }
    length += len_arg;
    count++;
  }
  regcomp(&regex, template_buf, reg_flag);
  free(template_buf);
  int get = 0, countSimilarity = 0, num_line = 0;
  while ((get = getline(&buffer, &bufSize, file_ptr)) != EOF) {
    num_line++;
    int result = 0, compare = result;
    if (buffer && get != EOF) {
      result = regexec(&regex, buffer, 1, &regmatch, 0);
      if (flags_list.v) compare = REG_NOMATCH;
      if (result == compare) {
        countSimilarity++;
        if (flags_list.l) {
          printf("%s\n", fileUse);
          break;
        } else if (!flags_list.c) {
          if (file_index > 1 && !flags_list.h) {
            printf("%s:", fileUse);
          }
          if (flags_list.o) {
            char* buffer_o = calloc(1000 + 2, sizeof(char));
            opt_o(buffer, buffer_o, flags_list, num_line, regex, regmatch,
                  file_index, fileUse);
            free(buffer_o);
          } else {
            if (flags_list.n) {
              printf("%d:%s", num_line, buffer);
            } else {
              printf("%s", buffer);
            }
          }
        }
      }
    }
  }
  if (flags_list.c) {
    if (file_index > 1 && !flags_list.h) {
      printf("%s:", fileUse);
    }
    printf("%d\n", countSimilarity);
  }
  free(buffer);
  regfree(&regex);
}

int opt_o(char* buffer, char* buffer_o, Flags flags_list, int num_line,
          regex_t regex, regmatch_t regmatch, int file_index, char* fileUse) {
  int res = 0;
  size_t size = regmatch.rm_eo - regmatch.rm_so;
  memset(buffer_o, 0, strlen(buffer_o));
  memmove(buffer_o, &buffer[regmatch.rm_so], size);
  puts(buffer_o);
  char* ptr = &buffer[regmatch.rm_eo];
  if (regexec(&regex, ptr, 1, &regmatch, 0) == 0) {
    if (opt_o(ptr, buffer_o, flags_list, num_line, regex, regmatch, file_index,
              fileUse)) {
      res = 1;
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
  return res;
}

void flag_f(Flags flags_list, char** files_list, char** templates, int* count_patterns) {
  FILE* file;
  char** str1 = (char**)malloc(1 * sizeof(char*));
  char** ptr;
  if ((file = fopen(files_list[0], "r"))) {
    char str[1000] = {0};
    int count = 0;
    while (fgets(str, 1000, file)) {
      int u = 1;
      str1[count] = (char*)malloc(1000 * sizeof(char));
      if (strlen(str) != 1 && str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
      snprintf(str1[count], sizeof(char) * 1000, "%s", str);
      ptr = (char**)realloc(str1, (u += 1) * sizeof(char*));
      if (ptr != NULL) {
        str1 = ptr;
        templates[count] = (char*)malloc(1000 * sizeof(char));
        strncpy(templates[count], str1[count], 999);
        count++;
      } else {
        for (int i = 0; i < count; i++) {
          free(str1[i]);
        }
        free(str1);
        exit(1);
      }
      *count_patterns = count;
    }
    for (int i = 0; i < count; i++) {
      free(str1[i]);
    }
    fclose(file);
  } else if (flags_list.s != 1) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", files_list[0]);
    exit(1);
  }
  free(str1);
}
