#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "dataSelector.h"
#include "StringBundle.h"
#include "checkStringBundle.h"

#define MAXNAMELENGTH 100

static char* copyOf(const char* const str);

int main(int argc, char** argv) {
	
	if ( argc < 3 ) {
		printf("Error: input file not specified.\n");
		printf("Invocation: c04driver <name of GIS record file> <name of output file> [-repeat]\n");
		exit(1);
	}

	FILE* input  = fopen(argv[1], "r");
	FILE*	output = fopen(argv[2], "w");
	if ( input == NULL ) {
		fprintf(output, "GIS record file %s was not found.\n", argv[1]);
		exit(2);
	}
	
	uint32_t seed;
	if ( argc == 4 && strcmp(argv[3], "-repeat") == 0 ) {
		FILE* fp = fopen("seed.txt", "r");
		if ( fp == NULL ) {
			printf("Could not open seed file.\n");
			printf("You must first run this program without the switch -repeat.\n");
			exit(3);
		}
		fscanf(fp, "%"PRIu32, &seed);
		fclose(fp);
	}
	else {
		seed = (uint32_t) time( NULL );
		FILE* fp = fopen("seed.txt", "w");
		fprintf(fp, "%"PRIu32"\n", seed);
		fclose(fp);
	}
	srand(seed);
	
	// load GIS records from file
	loadRecords(input);
	
	uint32_t totalScore = 0;
	uint32_t nCases = 10;
	for (uint32_t idx = 1; idx <= nCases; idx++) {
		
		char* pRecord = selectTestCase();
		char* pCopy = copyOf(pRecord);
		
		StringBundle* currBundle = createStringBundle(pRecord);
		
		fprintf(output, "Results for test case %"PRIu32" follow:\n\n", idx);
		fprintf(output, "  Test string: %s\n\n", pRecord);
		fprintf(output, "  Student's string bundle:\n");
		printStringBundle(output, currBundle);
		fprintf(output, "\n");
		
		uint32_t testScore = checkStringBundle(output, currBundle, pCopy);
		clearStringBundle(currBundle);
		free(currBundle);
		free(pCopy);
		
		totalScore += testScore;
		
		fprintf(output, ">> %"PRIu32" score: %2"PRIu32" / %"PRIu32"\n", 
		        idx, testScore, MAX_TOKENS);
		
		fprintf(output, "--------------------------------------------------\n");
	}
	
	fprintf(output, "\n");
	fprintf(output, "Total: %"PRIu32" / %"PRIu32"\n", totalScore, MAX_TOKENS * nCases);
	
	// free records
	clearRecords();
	
	// close files
	fclose(input);
	fclose(output);
	
	return 0;
}

static char* copyOf(const char* const str) {
	
	char* cpy;
	if ( str == NULL ) {
		cpy = calloc(1, sizeof(char));
		return cpy;
	}
	
	cpy = calloc(sizeof(char), strlen(str) + 1);
	strcpy(cpy, str);
	return cpy;
}
