#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"

#define MAX_INPUT_SIZE 256


int main() {

	//input vars
	int runwayNum;
	int flightNum;
	FlightType runwayType;
	BOOL isEmerg;
	char commandLine[MAX_INPUT_SIZE];
	char* dest;
	char* newDest;

	const char* delimiters = " \t\n";
	char *currentWord;


	/*/check
	dest = (char*)malloc(8);
	strcpy(dest, "strcpy");
	printf("%s\n", dest);
	free(dest);
	printf("%s\n", dest);
	scanf("%d", &numOfFlights);
	exit(-1);
	//check*/

	//now we will extract the first word, to understand the functionality//

	while (fgets(commandLine, MAX_INPUT_SIZE, stdin)) {
		currentWord = strtok(commandLine, delimiters);
		if (currentWord == NULL) {		//command not found
			fprintf(stderr, "Command not found.\n");
			continue;
		}
		//Insert Runway!//
		if (!strcmp(currentWord, "Insert")) {
			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}
			runwayNum = atoi(currentWord);
			if (runwayNum == 0) {
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}
			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}
			if (!strcmp(currentWord, "I")) runwayType = INTERNATIONAL;
			else if (!strcmp(currentWord, "D")) runwayType = DOMESTIC;
			else {
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}
			if (addRunway(runwayNum, runwayType) == FAILURE) fprintf(stderr, "Insert execution failed.\n");
		}
		//Remove Runway
		else if (!strcmp(currentWord, "Remove")) {
			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				continue;
			}
			runwayNum = atoi(currentWord);
			if (runwayNum == 0) {
				fprintf(stderr, "Remove execution failed.\n");
				continue;
			}
			if (removeRunway(runwayNum) == FAILURE) fprintf(stderr, "Remove execution failed.\n");
		}
		//Add flight
		else if (!strcmp(currentWord, "Add")) {

			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			flightNum = atoi(currentWord);
			if (flightNum == 0) {
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}

			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			if (!strcmp(currentWord, "I")) runwayType = INTERNATIONAL;
			else if (!strcmp(currentWord, "D")) runwayType = DOMESTIC;
			else {
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			dest = currentWord;

			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			if (!strcmp(currentWord, "E")) isEmerg = 1;
			else if (!strcmp(currentWord, "R")) isEmerg = 0;
			else {
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
			if (addFlightToAirport(flightNum, runwayType, dest, isEmerg) == FAILURE) fprintf(stderr, "Add execution failed.\n");

		}
		//Depart
		else if (!strcmp(currentWord, "Depart")) {
			if (depart() == FAILURE) fprintf(stderr, "Depart execution failed.\n");
		}
		//Change
		else if (!strcmp(currentWord, "Change")) {
			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Change failed: not enough parameters.\n");
				continue;
			}
			dest = currentWord;

			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Change failed: not enough parameters.\n");
				continue;
			}
			newDest = currentWord;
			if (changeDest(dest, newDest) == FAILURE) {
				fprintf(stderr, "Change failed: not enough parameters.\n");
				continue;
			}
		}
		//delay
		else if (!strcmp(currentWord, "Delay")) {
			currentWord = strtok(NULL, delimiters);
			if (currentWord == NULL) {		//not enough parameters. print error and continue to next command.
				fprintf(stderr, "Delay failed: not enough parameters.\n");
				continue;
			}
			if (delay(currentWord) == FAILURE) {
				fprintf(stderr, "Delay  execution failed.\n");
				continue;
			}
		}

		//Print or destroy
		else if (!strcmp(currentWord, "Print")) printAirport();
		else if (!strcmp(currentWord, "Exit")) {
			destroyAirport();
			return 0;
		}
		else {		//not enough parameters. print error and continue to next command.
			fprintf(stderr, "Command not found.\n");
			continue;
		}

	}
	return 0;
}
