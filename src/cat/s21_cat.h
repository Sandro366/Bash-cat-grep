#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flags;

void readFlags(int argc, char *argv[], flags *flags_list);
void flag_s(char *str, int *k);
void flag_b(flags fl, char *str, int *j);
void flag_e(flags fl, char *str);
void flag_n(flags fl, char *str, int *j);
void flag_v(flags fl, char *str);
void flag_t(flags fl, char *str);
void flag_bt(flags fl, char *str, int *j);
void adaptationFile(int argc, char *argv[], flags flags_list);

#endif  //  SRC_CAT_S21_CAT_H_
