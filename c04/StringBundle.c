#include "StringBundle.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


 
 
static char* copyOf(const char* const str);
static char* nextField(const char* const Line);

StringBundle* createStringBundle(const char* const str) {
	
   // location tracks location in text string
   // i is for for loop
   // real word is the real whole word to be added to array
   
   	int location = 0;
	int i;
	char* realWord;
	
	// thisAr is the array that is going to store values
	char** thisAr;
	thisAr = malloc(20 * sizeof(char*));
	
	// for loop for parsing line of text
	for(i = 0; i < 20; i++){
		
		// word is the temp word not optimized
		// sscanf parses the line to the next pipe
		char* word = calloc(50, sizeof(char));
		sscanf(str + location,"%[^|]", word);
		location = location + strlen(word) + 1;
		int wordLeng = strlen(word);
		
		realWord = calloc(wordLeng + 1, sizeof(char));
		strncpy(realWord, word, wordLeng);
		thisAr[i] = realWord;
		free(word);
		
	}
	
	// creates the optimized array
   static StringBundle* returnBundle;
   returnBundle = malloc(sizeof(StringBundle));
   
   returnBundle->Tokens = thisAr;
   returnBundle->nTokens = 20;
   
	return returnBundle;
}

void printStringBundle(FILE* fp, const StringBundle* const sb) {
	
	//fprintf(fp, "There are %"PRIu32" tokens:\n", sb->nTokens);
	
	for (uint32_t idx = 0; idx < sb->nTokens; idx++) {
		fprintf(fp, "   %3"PRIu32":  [%s]\n", idx, sb->Tokens[idx]);
	}
}

void clearStringBundle(StringBundle* sb) {
	
   // gets string bundle array
   char** contained = sb->Tokens;
   int j;
   
   //frees that array and values
   for(j = 0; j < 20; j++){
	   free(contained[j]);
   }
   free(sb->Tokens);
   
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

static char* nextField(const char* const Line) {
	
	static const char* currPos = NULL;
	if ( Line != NULL ) {         // reset if given fresh line to parse
		currPos = Line;
	}
	
	char dest[MAX_FIELDLENGTH] = {0};

	char* field = NULL;
	if ( *currPos == '|' ) {
		field = calloc(1, sizeof(char));
		currPos++;
	}
	else if ( sscanf(currPos, "%[^|]|", dest) > 0 )  {
	   field = calloc(1, strlen(dest) + 1);
	   strcpy(field, dest);
      currPos += strlen(dest);
      if ( *currPos != '\0' ) currPos++;
   }
   	
	return field;
}

