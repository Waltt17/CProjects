


#include <stdio.h>
#include <stdlib.h>

// Function declarations
int seconds(int input);
int minutes(int input);
int degree(int input);
int totalSeconds(int deg, int min, int sec);
int taxiCab(int x1, int y1, int x2, int y2);
int secondsToMixed(int input);


// Main
int main(int argc, char **argv)
{

	// Reads from the first file given and creates a new file 
	// named by the second input to write to
	FILE *In = fopen(argv[1],"r");
	FILE *Out = fopen(argv[2], "w");
	

	// chars to be read out from the file
	char xCoor1[50] = "\0";
	char xCoor2[50] = "\0";
	char xSign1[50] = "\0";
	char ySign1[50] = "\0";
	char yCoor1[50] = "\0";
	char yCoor2[50] = "\0";
	char xSign2[50] = "\0";
	char ySign2[50] = "\0";
	
	
	// Header for output file
	fprintf(Out, "First coordinate                        Second coordinate                   seconds    DMS\n");
	fprintf(Out, "-------------------------------------------------------------------------------------------------\n");
	
	
	// Reads given file until there is no more to read
	while( fscanf(In, "(%7c%1c, %6c%1c)    (%7c %1c %*c %6c %1c)\n", &xCoor1, &xSign1, &yCoor1, &ySign1, &xCoor2, &xSign2, &yCoor2, &ySign2) == 8){
		
		
		// Converts the x & y values for both coordinates into int
		int xtotal1 = atoi(xCoor1);
		int ytotal1 = atoi(yCoor1);
		int xtotal2 = atoi(xCoor2);
		int ytotal2 = atoi(yCoor2);		
		
		
		// Gets the seconds for the coordinate values
		int xs1 = seconds(xtotal1);
		int ys1 = seconds(ytotal1);
		int xs2 = seconds(xtotal2);
		int ys2 = seconds(ytotal2);	
		
		
		// Gets the minutes for the coordinate values
		int xm1 =  minutes(xtotal1);
		int ym1 = minutes(ytotal1);
		int xm2 =  minutes(xtotal2);
		int ym2 = minutes(ytotal2);
		
		
		// Gets the degrees for the coordinate values
		int xd1 = degree(xtotal1);
		int yd1 = degree(ytotal1);
		int xd2 = degree(xtotal2);
		int yd2 = degree(ytotal2);
		
		
		// Gets the total seconds for each coordinate value
		int xts1 = totalSeconds(xd1, xm1, xs1);
		int yts1 = totalSeconds(yd1, ym1, ys1);
		int xts2 = totalSeconds(xd2, xm2, xs2);
		int yts2 = totalSeconds(yd2, ym2, ys2);
		
		
		// Gets the taxi cab distance in seconds
		int taxiSec = taxiCab(xts1, yts1, xts2, yts2);
		// Gets the taxi cab distance as the mixed number
		int taxiMix = secondsToMixed(taxiSec);
		
		
		// Prints the values to the specified format with the specified values
		fprintf(Out, "(%dd %02dm %02ds W, %dd %02dm %02ds N)	(%dd %02dm %02ds W, %dd %02dm %02ds N)    %7d    %0dd %02dm %02ds\n",\
					xd1, xm1, xs1, yd1, ym1, ys1,\
					xd2, xm2, xs2, yd2, ym2, ys2, taxiSec, \
					degree(taxiMix), minutes(taxiMix), seconds(taxiMix));
		
	}
	
	
	fclose(In);
	fclose(Out);
	return 0;
}

// Given an input in the mixed form, gives the seconds back
int seconds(int input){
	return input % 100;
}

// Given an input in the mixed form, gives the minutes back
int minutes(int input){
	return ((input % 10000) / 100);
}

// Given an input in the mixed form, gives the degrees back
int degree(int input){
	return input / 10000;
}

// Given the degrees, minutes, and seconds, gives the total amount of seconds
int totalSeconds(int deg, int min, int sec){
	return (deg * 3600) + (min * 60) + sec;
}

// Given the coordinates in only seconds of two points, returns the taxi cab distace in seconds
int taxiCab(int x1, int y1, int x2, int y2){
	return (abs(x1 - x2) + abs(y1 - y2));
}

// Given seconds will convert to the mixed format
int secondsToMixed(int input){				
	int mixed = 0;
	mixed = mixed + ((input / 3600) * 10000);
	mixed = mixed + ((input / 60 - ((mixed / 10000) * 60)) * 100);
	mixed = mixed + ((input - ((mixed / 10000) * 3600) - (((mixed / 100) % 100) * 60)));
	return mixed;
}
