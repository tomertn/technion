#include <stdio.h>
#include <stdlib.h>
#include "flight.h"
#include "ex2.h"
#include "airport.h"
#include "runway.h"

//*********************************************************************************
//* function name:
//* Description  :
//* Parameters   :
//* Return value :
//*********************************************************************************
typedef struct _runwayElem {
	PRunway pRunway;
	struct _runwayElem*  pNextRunway;
}runwayElem;
typedef struct _runwayElem* PRunwayElemm;
PRunwayElemm airport=NULL;

//*********************************************************************************
//* function name: addRunway
//* Description  : makes new runway and add it to the airport
//* Parameters   : runwayNum- intenger of the runway nmber
//*                runwayType- the taype of the runway
//* Return value : Result- SUCCESS for run success or FAILURE for run failur
//*********************************************************************************
 Result addRunway(int runwayNum, FlightType runwayType) {
	 PRunwayElemm thisElem;
	 if ((airport == NULL))//check if its empty air port, and craet the run way
	 {
		 PRunwayElemm newRunway= (PRunwayElemm)malloc(sizeof(runwayElem));
		 if (newRunway == NULL)
			 return FAILURE;
		 newRunway->pRunway= createRunway(runwayNum, runwayType);
		 if (newRunway->pRunway == NULL)
			 return FAILURE;
		 newRunway->pNextRunway = NULL;
		 airport = newRunway;
	 }
	 else {// if the airport already exists
		 thisElem = airport;
		 if (getRunwayNum(thisElem->pRunway) == runwayNum)//checking if there is runwaynum like this one
			 return FAILURE;
		 while ((thisElem->pNextRunway) != NULL) {
			 if (getRunwayNum(thisElem->pNextRunway->pRunway) == runwayNum)//checking if there is runwaynum like this one
				 return FAILURE;
			 thisElem = thisElem->pNextRunway;
		 }
		 PRunwayElemm newRunway = (PRunwayElemm)malloc(sizeof(runwayElem));// makes the new runway
		 if (newRunway == NULL)
			 return FAILURE;
		 newRunway->pRunway = createRunway(runwayNum, runwayType);
		 if (newRunway->pRunway == NULL)
			 return FAILURE;
		 newRunway->pNextRunway = NULL;
		 thisElem->pNextRunway = newRunway;
	 }
	 return SUCCESS;
 }


 //*********************************************************************************
 //* function name: removeRunway
 //* Description  : find runway whith given runway num and remove it
 //* Parameters   : runwayNum- intenger of the runway to remove
 //* Return value : Result- SUCCESS for run success or FAILURE for run failur
 //*********************************************************************************
 Result removeRunway(int runwayNum) {
	 PRunwayElemm thisElem = airport;
	 PRunwayElemm prevElem;
	 if (thisElem == NULL){ //check if its empty air port
		 return FAILURE;
 }
	 if (getRunwayNum(thisElem->pRunway) == runwayNum) {//we check if the first is the one to remove
		 destroyRunway(thisElem->pRunway);
		 airport = thisElem->pNextRunway;
		 free(thisElem);
		 return SUCCESS;
	 }
	 prevElem = thisElem;//we stepup one element
	 thisElem = thisElem->pNextRunway;
	 while (thisElem != NULL) {//we run on the list until we found our number, if we cant find it, we return failurre
		 if (getRunwayNum(thisElem->pRunway) == runwayNum) {
			 destroyRunway(thisElem->pRunway);
			 prevElem->pNextRunway = thisElem->pNextRunway;
			 free(thisElem);
			 return SUCCESS;
		 }
		 prevElem = thisElem;
		thisElem = thisElem->pNextRunway;
	 }
	 return FAILURE;
 }


 //*********************************************************************************
 //* function name: addFlightToAirport
 //* Description  : gets ditels of flight and add it to the airport
 //* Parameters   : flightNum- interger of the flight number
 //*				    fType- the flight type
 //*				    fDestination- a pointer to the flight destination
 //*				    isEmergency- TRUE for emergency flight and FALSE for regular
 //* Return value : Result- SUCCESS for run success or FAILURE for run failur
 //*********************************************************************************
 Result addFlightToAirport(int flightNum, FlightType fType, char* fDestination, BOOL isEmergency) {
	 PRunwayElemm thisElem = airport;
	 if (thisElem == NULL)//check if the airport is empty
		 return FAILURE;
	 while (thisElem != NULL) {//check if the flight num alradey used
		 if(isFlightExists(thisElem->pRunway, flightNum))
			 return FAILURE;
		 thisElem=thisElem->pNextRunway;
	 }
	 thisElem = airport;
	 PRunway runwayToAdd = NULL;
	 while (thisElem != NULL) {//we run on the all runways and find the one that need we to add to him
		 if (getRunwayType(thisElem->pRunway) == fType){
			 if (runwayToAdd == NULL)//set for first
				 runwayToAdd = thisElem->pRunway;
			 else {
				 if (getFlightNum(thisElem->pRunway) < getFlightNum(runwayToAdd))
					 runwayToAdd = thisElem->pRunway;
				 if ((getFlightNum(thisElem->pRunway) == getFlightNum(runwayToAdd)) && (getRunwayNum(thisElem->pRunway) < getRunwayNum(runwayToAdd)))
					 runwayToAdd = thisElem->pRunway;
			 }
		 }
			 thisElem=thisElem->pNextRunway;
	 }
	 if (runwayToAdd == NULL) {//this check if there is one runway from our type
		 return FAILURE;
	 }
	 PFlight theNewFlight = createFlight(flightNum, fType, fDestination, isEmergency);
	 if (theNewFlight == NULL)
		 return FAILURE;
	 return addFlight(runwayToAdd, theNewFlight);
 }


 //*********************************************************************************
 //* function name: depart
 //* Description  : remove a flight form the airport, in the gaidlines
 //* Parameters   : None
 //* Return value : Result- SUCCESS for run success or FAILURE for run failur
 //*********************************************************************************
 Result depart() {
	 PRunwayElemm thisElem = airport;
	 if (thisElem == NULL)//check if the airport is empty
		 return FAILURE;
	 PRunway runwayToDepart = NULL;
	 int MaxOfEmerg = -1;//first we check if we have one max of emerge
	 int thisMax = -1;
	 BOOL twoOfMax = FALSE;
	 while (thisElem != NULL) {
		 thisMax = getEmergencyNum(thisElem->pRunway);
		 if (thisMax == -1)//getEmergencyNum check
			 return FAILURE;
		 if (MaxOfEmerg == -1) {//if its the first max, so we set MaxOfEmerg
			 MaxOfEmerg = thisMax;
			 runwayToDepart = thisElem->pRunway;
		 }
		 else {
			 if (MaxOfEmerg == thisMax)
				 twoOfMax = TRUE;
			 if (MaxOfEmerg < thisMax) {
				 MaxOfEmerg = thisMax;
				 runwayToDepart = thisElem->pRunway;
				 twoOfMax = FALSE;
			 }
		 }
		 thisElem=thisElem->pNextRunway;
		 }
		 if ((thisMax == 0) || (twoOfMax)) {//this case is about the case that we dont have on max of emerg
			 thisElem = airport;//we check if there is one max of flights
			 runwayToDepart = NULL;
			 int MaxOfFlight = -1;
			 thisMax = -1;
			 twoOfMax = FALSE;
			 while (thisElem != NULL) {
				 thisMax = getFlightNum(thisElem->pRunway);
				 if (thisMax == -1)//getFlightNum check
					 return FAILURE;
				 if (MaxOfFlight == -1) {//if its the first max, so we set MaxOfEmerg
					 MaxOfFlight = thisMax;
					 runwayToDepart = thisElem->pRunway;
				 }
				 else {
					 if (MaxOfFlight == thisMax)
						 twoOfMax = TRUE;
					 if (MaxOfFlight < thisMax) {
						 MaxOfFlight = thisMax;
						 runwayToDepart = thisElem->pRunway;
						 twoOfMax = FALSE;
					 }
				 }
			 thisElem=thisElem->pNextRunway;
			 }
			 if (thisMax == 0)//check if there are no flights
				 return FAILURE;
			 if (twoOfMax){	//this case is about the case that we dont have  max of flight
				 thisElem = airport;//we find the min num of runway
				 runwayToDepart = thisElem->pRunway;
				 while (thisElem != NULL) {
					 if ((getRunwayNum(thisElem->pRunway) < getRunwayNum(runwayToDepart)))
						 runwayToDepart = thisElem->pRunway;
                    thisElem = thisElem->pNextRunway;
				 }

		 }
	 }
	return departFromRunway(runwayToDepart);
 }


 //*********************************************************************************
 //* function name: changeDest
 //* Description  : change destination of all flight whith given destination to new 
 //*					given destination
 //* Parameters   : fDestinationOld- the destination to change
 //*					fDestinationNew- the new destination
 //* Return value : Result- SUCCESS for run success or FAILURE for run failur
 //*********************************************************************************
 Result changeDest(char* fDestinationOld, char* fDestinationNew) {
	 PRunwayElemm thisElem = airport;
	 while (thisElem != NULL) {
			 if (runwayChangeDest(thisElem->pRunway, fDestinationOld, fDestinationNew) == FAILURE)
				 return FAILURE;
			 thisElem = thisElem->pNextRunway;
	 }
	 return SUCCESS;
 }


 //*********************************************************************************
 //* function name: delay
 //* Description  : delay all the flight in the airport this given destination in gaidlines
 //* Parameters   : fDestination- destination to delay
 //* Return value : Result- SUCCESS for run success or FAILURE for run failur
 //*********************************************************************************
 Result delay(char* fDestination) {
	 PRunwayElemm thisElem = airport;
	 if (isDestLegal(fDestination) == FALSE)
		 return FAILURE;
	 while (thisElem != NULL) {
		 runwayDelay(thisElem->pRunway, fDestination);
		 thisElem = thisElem->pNextRunway;
	 }
	 return SUCCESS;
 }


 //*********************************************************************************
 //* function name: destroyAirport
 //* Description  : delete the airport
 //* Parameters   : None
 //* Return value : None
 //*********************************************************************************
 void destroyAirport()
 {
	 while (airport != NULL)
	 {
		 removeRunway(getRunwayNum(airport->pRunway));
	 }
 }


 //*********************************************************************************
 //* function name: printAirport
 //* Description  : print the details of the airport
 //* Parameters   : None
 //* Return value : Result- SUCCESS for run success or FAILURE for run failur
 //*********************************************************************************
 Result printAirport() {
	 PRunwayElemm thisElem = airport;
	 printf("Airport status :\n");
	 while (thisElem != NULL) {
		 if (printRunway(thisElem->pRunway) == FAILURE)
			 return FAILURE;
		 thisElem = thisElem->pNextRunway;
	 }
	 return SUCCESS;
 }
