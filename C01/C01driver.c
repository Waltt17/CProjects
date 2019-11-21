// Test driver for CS 2505 C01 Spring 2019
//
// Invocation:  C01driver <results file name> [-rand]
//
// Build an executable with the command:
//
//   gcc -o C01driver -std=c11 -Wall C01driver.c sumMatches.c Generate.o checkAnswer.o
//
// After executing, check the contents of the file created by this program.
//
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "Generate.h"
#include "sumMatches.h"
#include "checkAnswer.h"

int main(int argc, char** argv) {
	
	// Command-line validation section
	// First, check for minimum number of command-line arguments:
	if ( argc < 2 ) {
		printf("Invocation: c01driver <results file name> [-rand]\n");
		return 1;
	}
	
	// Next, try to open an output file with the specified name;
	// this will create a new file if none exists, and truncate an
	// existing file with the same name.
	// If the file cannot be opened (unlikely), exit.
	FILE* results = fopen(argv[1], "w");
	if ( results == NULL ) {
		printf("Failed to create file for results: %s\n", argv[1]);
		return 2;
	}
	
	// Check to see if we are supposed to generate random test data.
	// It only makes sense to NOT select randomization if you've already
	// executed this test driver, and the file seed.txt still exists in
	// the current directory.
	bool randomize = false;
	if ( argc == 3 && strcmp(argv[2], "-rand") == 0 ) {
		randomize = true;
	}
	
	// Here, we handle the issue of randomizing the test data:
	uint32_t seed = 0;
	if ( randomize ) {
		// Get the current system clock time to seed rand():
		seed = time(NULL);
		// Save it to a file (for future calls without -rand):
		FILE* fp = fopen("seed.txt", "w");
		fprintf(fp, "%"PRIu32"\n", seed);
		fclose(fp);
	}
	else {
		// Get the seed value saved from the last randomization run:
		FILE* fp = fopen("seed.txt", "r");
		if ( fp == NULL ) {
			printf("Failed to open seed file.\n");
			return false;
		}
		fscanf(fp, "%"SCNu32, &seed);
		fclose(fp);
	}
	// Either way, seed the rand() function:
	srand( seed );

   // We will hardwire the number of test cases to be employed:
   uint32_t numTestsToRun = 10;
   
   // We will award 10 points for each successful case, and store the
   // current total score here:
   uint32_t totalScore =  0;
   uint32_t caseValue  = 10;
   
   // Generate and run the test cases:
   for (uint32_t test = 1; test <= numTestsToRun; test++) {
   
      uint32_t left = 0, right = 0;
      // Generate a new test case:
      generate(&left, &right);
			
	   // Call student's function to compute result:
	   int8_t stuSum = sumMatches(left, right);
		   
	   // Call function to check result:
	   int8_t refResult = 0;
	   if ( checkAnswer(left, right, stuSum, &refResult) ) {
			totalScore += caseValue;
			fprintf(results, "Test case %"PRIu32" results are correct:\n", test);
	      fprintf(results, "%12"PRIu32"\n%12"PRIu32"\n%12"PRId8"\n", left, right, stuSum);
	   }
	   else {
			fprintf(results, "Test case %"PRIu32" results are NOT correct:\n", test);
	      fprintf(results, "%12"PRIu32"\n%12"PRIu32"\n%12"PRId8"\n", left, right, stuSum);
	      fprintf(results, "   Correct result is: %"PRId8"\n", refResult);
		}
   }
   
   // Record the total score results:
   fprintf(results, "\n>> 1  Score: %"PRIu32" / %"PRIu32"\n", 
           totalScore, numTestsToRun * caseValue);
   
   // Close the output file; this flushes buffered output to the disk,
   // and releases the file.
   fclose(results);
   return 0;
}
