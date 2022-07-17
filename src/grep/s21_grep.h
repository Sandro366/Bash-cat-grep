#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} Flags;

void readFlags(int argc, char* argv[], Flags* flags_list);
void file_open(char** files_list, char** templates, Flags flags_list,
               int file_index, int count_pattern);
void file_read(FILE* file_ptr, char** templates, Flags flags_list,
               int file_index, char* file, int count_pattern);
char** findTemplates(int argc, char* argv[], int* k);
char** findFiles(int argc, char* argv[], int* file_index);
void flag_f(Flags flags_list, char** files_list, char** templates, int* k);
int opt_o(char* buffer, char* buffer_o, Flags flags_list, int num_line,
          regex_t regex, regmatch_t regmatch, int file_index, char* fileUse);

#endif  //  SRC_GREP_S21_GREP_H_
