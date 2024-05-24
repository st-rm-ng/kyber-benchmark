#include <stdlib.h>
#include <stdio.h>
#include "cpucycles.h"
#include "speed_print.h"

static int cmp_uint64(const void *a, const void *b) {
  if(*(uint64_t *)a < *(uint64_t *)b) return -1;
  if(*(uint64_t *)a > *(uint64_t *)b) return 1;
  return 0;
}

static uint64_t median(uint64_t *l, size_t llen) {
  qsort(l,llen,sizeof(uint64_t),cmp_uint64);

  if(llen%2) return l[llen/2];
  else return (l[llen/2-1]+l[llen/2])/2;
}

static uint64_t average(uint64_t *t, size_t tlen) {
  size_t i;
  uint64_t acc=0;

  for(i=0;i<tlen;i++)
    acc += t[i];

  return acc/tlen;
}

void print_results(const char *s, uint64_t *tm, uint64_t *t, size_t tlen) {
  size_t i;
  static uint64_t overhead = -1;

  if(tlen < 2) {
    fprintf(stderr, "ERROR: Need at least two cycle counts!\n");
    return;
  }

  if(overhead == (uint64_t)-1)
    overhead = cpucycles_overhead();

  tlen--;
  for(i=0;i<tlen;++i)
    t[i] = t[i+1] - t[i] - overhead;

  median(tm, tlen);
  printf("%s: \n", s);
  printf("\tmedian: \n\t\t%llu cycles/ticks\n\t\t%.3f millis\n", (unsigned long long)median(t, tlen), (((double)median(tm, tlen)) / CLOCKS_PER_SEC) * 1000);
  printf("\taverage: \n\t\t%llu cycles/ticks\n\t\t%.3f millis\n", (unsigned long long)average(t, tlen), (((double)average(tm, tlen)) / CLOCKS_PER_SEC) * 1000);
  printf("\n");
}
