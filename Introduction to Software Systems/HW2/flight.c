#include <stdio.h>
#include <stdlib.h>
#include "flight.h"


struct flight {
	int flightNum;
	FlightType fType;
	char* fDestination;
	BOOL isEmergency;
};
//*********************************************************************************
//* function name: isDestLegal
//* Description  : chack if the destination is legal
//* Parameters   : s- a pointer to destination name
//* Return value : BOOL,TRUE for legal destination and FALSE for ilegal
//*********************************************************************************
BOOL isDestLegal(char* s) {
	int i = 0;
	for (; s[i]; i++) {
		if((s[i]>'Z')||(s[i]<'A'))
			return FALSE;
	}
	if (strlen(s)!=3) return FALSE;
	return TRUE;
}

//*********************************************************************************
//* function name: createFlight
//* Description  : the func check if the parametrs of the flight is legal and creat 
//*					new flight
//* Parameters   : flightNum- interger of the flight number
//*				   fType- the flight type
//*				   fDestination- a pointer to the flight destination
//*				   isEmergency- TRUE for emergency flight and FALSE for regular
//* Return value : PFlight- pointer to the new flight
//*********************************************************************************
PFlight createFlight(int flightNum, FlightType fType, char* fDestination, BOOL isEmergency) {
	if ((flightNum > MAX_ID) || (flightNum < 1))//check the flight Number
		return NULL;
	if ((fType != DOMESTIC) && (fType != INTERNATIONAL))//check the flight type
		return NULL;
	if (isDestLegal(fDestination) == FALSE)//check the destination
		return NULL;
	if ((isEmergency != TRUE) && (isEmergency != FALSE))//check isEmergency 
		return NULL;
	PFlight pFlight = (PFlight)malloc(sizeof(struct flight));
	if (pFlight == NULL)
		return NULL;
	pFlight->flightNum = flightNum;
	pFlight->fType = fType;
	pFlight->fDestination = (char*)malloc(sizeof(char)*strlen(fDestination));
	if(pFlight->fDestination==NULL)
	{
		free(pFlight); return NULL;
	}
	strcpy(pFlight->fDestination, fDestination);
	pFlight->isEmergency = isEmergency;
	return pFlight;
}


//*********************************************************************************
//* function name: destroyFlight
//* Description  : delete a flight
//* Parameters   :fToDestroy- a pointer to the flight we need to destroy
//* Return value :None
//*********************************************************************************
void destroyFlight(PFlight fToDestroy) {
	if (fToDestroy == NULL)
		return;
	free(fToDestroy->fDestination);
	free(fToDestroy);
}


//*********************************************************************************
//* function name: printFlight
//* Description  : printing the flight details
//* Parameters   : fToPrint- a pointer to the flight 
//* Return value : None
//*********************************************************************************
Result printFlight(PFlight fToPrint) {
	char emerg = 'R';
	char fTypeAux = 'D';
	if (fToPrint == NULL)
		return FAILURE;
	if (fToPrint->isEmergency == TRUE)
		emerg = 'E';
	if (fToPrint->fType == INTERNATIONAL)
		fTypeAux = 'I';
	printf("Flight %d %c %s %c\n", fToPrint->flightNum, fTypeAux, fToPrint->fDestination, emerg);
	return SUCCESS;
}


//*********************************************************************************
//* function name: getAFlightNum
//* Description  : return the flight number
//* Parameters   : fToPrint- a pointer to the flight
//* Return value : int- the flight number
//*********************************************************************************
int getAFlightNum(PFlight pFlight) {
	if (pFlight == NULL) return -1;
	return pFlight->flightNum;
}


//*********************************************************************************
//* function name: getFlightType
//* Description  : return the flight type
//* Parameters   : fToPrint- a pointer to the flight
//* Return value : FlightType- the flight type
//*********************************************************************************
FlightType getFlightType(PFlight pFlight) {
	return pFlight->fType;
}


//*********************************************************************************
//* function name: getFlightDest
//* Description  : return the flight destination
//* Parameters   : fToPrint- a pointer to the flight
//* Return value : char*-  a pointer to the destination
//*********************************************************************************
char* getFlightDest(PFlight pFlight) {
	if (pFlight == NULL)
        return "FAIL";
	return pFlight->fDestination;
}


//*********************************************************************************
//* function name: isFlightEmer
//* Description  : return if the flight is emerg or not
//* Parameters   : fToPrint- a pointer to the flight
//* Return value : BOOL-  TRUE if the flight is emerg and if not FALSE
//*********************************************************************************
BOOL isFlightEmer(PFlight pFlight) {
	if (pFlight == NULL)
        return FALSE;
	return pFlight->isEmergency;
}


//*********************************************************************************
//* function name: changeFlightDest
//* Description  : change the destination of the given flight to new given destination
//* Parameters   : fToChangeDest- a pointer to the flight
//*				   fNewDestination-  a pointer to the new destination
//* Return value : Result- SUCCESS for change success or FAILURE for change failure
//*********************************************************************************
Result changeFlightDest(PFlight fToChangeDest, char* fNewDestination)
{
	if (!(isDestLegal(fNewDestination)))
		return FAILURE;
	else {
		//fToChangeDest->fDestination = fNewDestination; 
		strcpy(fToChangeDest->fDestination, fNewDestination);
	}
	return SUCCESS;
}



