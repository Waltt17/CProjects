#ifndef DATASELECTOR_H
#define DATASELECTOR_H
#include <stdio.h>
#include <inttypes.h>

uint32_t loadRecords(FILE* fp);
char* selectTestCase();
void clearRecords();

#endif
