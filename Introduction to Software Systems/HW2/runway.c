#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "flight.h"
#include "runway.h"

struct FlightElem
{
	PFlight pFlight;
	struct FlightElem* pNext;
}; 

struct runway {
	int runwayNum;
	FlightType rType;
	PFlightElem List;
};
//*********************************************************************************
//* function name: create FlightElem
//* Description  : make new flight element form given flight
//* Parameters   : pFlight- pointer to flight to connect the element
//*				   pf_Next- pointer the next elemnet to connect
//* Return value : PFlightElem- pointer to the new element
//*********************************************************************************
PFlightElem createFlightElem(PFlight pFlight, PFlightElem pf_Next) {
	PFlight newpFlight = createFlight(getAFlightNum(pFlight), getFlightType(pFlight),
		getFlightDest(pFlight), isFlightEmer(pFlight));
	if (newpFlight == NULL) return NULL;
	PFlightElem pFlightElem = (PFlightElem)malloc(sizeof(struct FlightElem));
	if (pFlightElem == NULL) return NULL;
	pFlightElem->pFlight = newpFlight;
	pFlightElem->pNext = pf_Next;
	return pFlightElem;
}


//*********************************************************************************
//* function name: getRunwayList
//* Description  : get the pointer of the first flight element of the runway
//* Parameters   : pRunway- pointer to the runway
//* Return value : PFlightElem- the pointer of the first flight element of the runway
//*********************************************************************************
PFlightElem getRunwayList(PRunway pRunway) {
	return pRunway->List;
}


//*********************************************************************************
//* function name: getRunwayType
//* Description  : return the type of given runway
//* Parameters   : pRunway- pointer to the runway
//* Return value : FlightType- the type of the runway
//*********************************************************************************
FlightType getRunwayType(PRunway pRunway) {
	return pRunway->rType;
}


//*********************************************************************************
//* function name: getRunwayNum
//* Description  : return the number of given runway
//* Parameters   : pRunway- pointer to the runway
//* Return value : int- the number of the runway
//*********************************************************************************
int getRunwayNum(PRunway pRunway) {
	if (pRunway == NULL) return -1;
	return pRunway->runwayNum;
}


//*********************************************************************************
//* function name: destroyFlightElem
//* Description  : delete given flight element
//* Parameters   : pFlight- pointer to flight to connect the element
//* Return value : Result- SUCCESS for run success or FAILURE for run failure
//*********************************************************************************
Result destroyFlightElem(PFlightElem pFElem) {
	if (pFElem == NULL) return FAILURE;
	destroyFlight(pFElem->pFlight);
	free(pFElem);
	return SUCCESS;
}


//*********************************************************************************
//* function name: destryListOfFlights
//* Description  : delete list of flight of given runway element
//* Parameters   : pRunway- pointer to the runway
//* Return value : None
//*********************************************************************************
void destryListOfFlights(PRunway pRunway) {
	while (pRunway->List != NULL) {
		PFlightElem temp = pRunway->List;
		pRunway->List = pRunway->List->pNext;
		destroyFlightElem (temp);
	}
}


//*********************************************************************************
//* function name: destroyRunway
//* Description  : delete given runway element
//* Parameters   : runwayToDestroy- pointer to the runway
//* Return value : None
//*********************************************************************************
void destroyRunway(PRunway runwayToDestroy) {
	destryListOfFlights(runwayToDestroy);
	free(runwayToDestroy);
}


//*********************************************************************************
//* function name: addFlightToList
//* Description  : add given flight to a given place in a given runway's List.
//* Parameters   : pRunway- pointer to the runway
//*                pFlight- pointer to the flight
//*                place- intenger to the palce in the runway
//* Return value : Result- SUCCESS for run success or FAILURE for run failure
//*********************************************************************************
Result addFlightToList(PRunway pRunway, PFlight pFlight, int place) {
	PFlightElem flightToLink = createFlightElem(pFlight, NULL);
	if (flightToLink == NULL || pRunway==NULL) { return FAILURE; }
	if (pRunway->List == NULL) {//for empty runway
		flightToLink->pNext = NULL; pRunway->List = flightToLink; return SUCCESS;
	}
	if (place == 0) {
		flightToLink->pNext = pRunway->List; pRunway->List = flightToLink; return SUCCESS;
	}
	if (place == 1) {
		flightToLink->pNext = pRunway->List->pNext;
		pRunway->List->pNext = flightToLink;
		return SUCCESS;
	}
	PFlightElem ip =  pRunway->List;
	for(int i = 1; i < place && ip; i++)
		ip = ip->pNext;
	flightToLink->pNext = ip->pNext;
	ip->pNext = flightToLink;
	return SUCCESS;
}


//*********************************************************************************
//* function name: createRunway
//* Description  : creat new runway form give runway number and given type
//* Parameters   : runwayNum- number of the new runway
//*                rType- type of the new runway
//* Return value : PRunway- pointer of the new ruway
//*********************************************************************************
PRunway createRunway(int runwayNum, FlightType rType) {
	if ((runwayNum > MAX_ID) || (runwayNum < 1))
		return NULL;
	if ((rType != DOMESTIC) && (rType != INTERNATIONAL))
		return NULL;

	PRunway pRunway = (PRunway)malloc(sizeof(struct runway));
	if (pRunway == NULL)
		return NULL;

	pRunway->runwayNum = runwayNum;
	pRunway->rType = rType;
	pRunway->List = NULL;

	return pRunway;

}


//*********************************************************************************
//* function name: isFlightExists
//* Description  : cheking if there are flight with given number in given runway
//* Parameters   : pRunway- pointer to the runway
//*                flightNum- intenger og the flight number
//* Return value : BOOL- TRUE if we found the number ald FALSE if not
//*********************************************************************************
BOOL isFlightExists(PRunway pRunway, int flightNum) {
	if (pRunway == NULL)
		return FALSE;
	if ((flightNum > MAX_ID) || (flightNum < 1))
		return FALSE;

	PFlightElem ip = pRunway->List;
	while (ip) {
		if (flightNum == getAFlightNum(ip->pFlight))
			return TRUE;
		ip = ip->pNext;
	}
	return FALSE;
}


//*********************************************************************************
//* function name: getFlightNum
//* Description  : return the number of flights in given runway
//* Parameters   : pRunway- pointer to the runway
//* Return value : int- -1 if the runway didnt exists , or the number of the flights in the runway
//*********************************************************************************
int getFlightNum(PRunway pRunway) {
	if (pRunway == NULL)
		return (-1);
	PFlightElem ip = pRunway->List;
	int i = 0;
	while (ip) {
		i++;
		ip = ip->pNext;
	}
	return i;
}


//*********************************************************************************
//* function name: getEmergencyNum
//* Description  : return the number of emerg flights in given runway
//* Parameters   : pRunway- pointer to the runway
//* Return value : int- -1 if the runway didnt exists , or the number of the emerge flights in the runway
//*********************************************************************************
int getEmergencyNum(PRunway pRunway) {
	if (pRunway == NULL)
		return (-1);
	PFlightElem ip = pRunway->List;
	int i = 0;
	while ( (ip != NULL) && (isFlightEmer(ip->pFlight)) )
	{
		i++; ip = ip->pNext;
	}
	return i;
}


//*********************************************************************************
//* function name: addFlight
//* Description  : adding given flight to given runway
//* Parameters   : pRunway- pointer to the runway
//*                pFlight- pointer to the flight
//* Return value : Result- SUCCESS for run success or FAILURE for run failur
//*********************************************************************************
Result addFlight(PRunway pRunway, PFlight pFlight) {
	if (isFlightExists(pRunway, getAFlightNum(pFlight))) return FAILURE;// check if the number of the flight already exists
	if (pRunway->rType != getFlightType(pFlight)) return FAILURE;// check if the type match
	PFlight flightToAdd = createFlight(getAFlightNum(pFlight), getFlightType(pFlight),
		getFlightDest(pFlight), isFlightEmer(pFlight));// create new flight
	if (pRunway == NULL || pFlight == NULL || flightToAdd == NULL) return FAILURE; //checks aloccation
	int numOfEmer = getEmergencyNum(pRunway);//check the number of the emergency flights fpr knowing the place to insert the flight, if it's emergency
	int numOfFlights = getFlightNum(pRunway);// check the number of flights to know where to insert the flight if its regular flight.
	if (isFlightEmer(pFlight))                        //use aux func for insert the flight to list in the place calculated above.
		addFlightToList(pRunway, pFlight, numOfEmer);
	else
		addFlightToList(pRunway, pFlight,numOfFlights);
	return SUCCESS;
}


//*********************************************************************************
//* function name: removeFlight
//* Description  : remove flight with given number from given runway
//* Parameters   : pRunway- pointer to the runway
//*                flightNum- intenger of the flight number
//* Return value : Result- SUCCESS for run success or FAILURE for run failur
//*********************************************************************************
Result removeFlight(PRunway pRunway, int flightNum) {
	if (isFlightExists(pRunway, flightNum) == FALSE) return FAILURE;//check if there is flight with this number
	if (getAFlightNum(pRunway->List->pFlight) == flightNum) {//for the first flight
		departFromRunway(pRunway); return SUCCESS;
	}
	PFlightElem ip = pRunway->List, prev;
	prev = ip;
	while (ip != NULL && (getAFlightNum(ip->pFlight) != flightNum))//run the list until we found the flight
	{
		prev = ip;
		ip = ip->pNext;
	}
	if (ip == NULL) return FAILURE;
	prev->pNext = ip->pNext;
	destroyFlightElem(ip);
	return SUCCESS;
}


//*********************************************************************************
//* function name: departFromRunway
//* Description  : remove the first flight from given runway
//* Parameters   : pRunway- pointer to the runway
//* Return value : Result- SUCCESS for run success or FAILURE for run failur
//*********************************************************************************
Result departFromRunway(PRunway pRunway) {
	if (pRunway == NULL || pRunway->List == NULL)
		return FAILURE;
	PFlightElem temp = pRunway->List;
	pRunway->List = pRunway->List->pNext;
	destroyFlightElem(temp);
	return SUCCESS;
}


//*********************************************************************************
//* function name: printRunway
//* Description  : print details of given runway
//* Parameters   : pRunway- pointer to the runway
//* Return value : Result- SUCCESS for run success or FAILURE for run failur
//*********************************************************************************
Result printRunway(PRunway pRunway) {
	if (pRunway == NULL) return FAILURE;
	char* s;
	if (pRunway->rType == INTERNATIONAL)
		s = "international";
	else s = "domestic";
	int num = getFlightNum(pRunway);
	PFlightElem ip = pRunway->List;
	if (num == (-1)) return FAILURE;
	printf("Runway %d %s\n", pRunway->runwayNum,s);
	printf("%d flights are waiting:\n",num);
	while (ip) {
		printFlight(ip->pFlight);
		ip = ip->pNext;
	}
	return SUCCESS;
}


//*********************************************************************************
//* function name: runwayChangeDest
//* Description  : change the destination of all flight in given runway with given
//*                destination to new given destination
//* Parameters   : runwayToChangeDest- pointer to the runway
//*                fDestinationOld-  pointer to the destination to change
//*                fDestinationNew- pointer to the new destination
//* Return value : Result- SUCCESS for run success or FAILURE for run failur
//*********************************************************************************
Result runwayChangeDest(PRunway runwayToChangeDest, char* fDestinationOld, char* fDestinationNew) {//change dest of all flight
	PFlightElem thisElem = runwayToChangeDest->List;
	while (thisElem != NULL) {
		if (!strcmp(getFlightDest(thisElem->pFlight), fDestinationOld))
			if (changeFlightDest(thisElem->pFlight, fDestinationNew) == FAILURE)
				return FAILURE;
		thisElem = thisElem->pNext;
	}
	return SUCCESS;
}


//*********************************************************************************
//* function name: runwayDelay
//* Description  : delay all flight from given runway with given destination
//* Parameters   : runwayToDelay- pointer to the runway
//*                fDestinationToDelay- pointer to the destination
//* Return value : None
//*********************************************************************************
void runwayDelay(PRunway runwayToDelay, char* fDestinationToDelay) {
	PFlightElem thisElem = runwayToDelay->List;
	PFlightElem prevElem = NULL;
	PFlightElem tempList=NULL;// list of flight with the destination
	PFlightElem thisTempList=NULL;
	while (thisElem != NULL) {
		if (!strcmp(getFlightDest(thisElem->pFlight), fDestinationToDelay)) {
			if (prevElem == NULL)// check if its the first elem
				runwayToDelay->List = thisElem->pNext;// remove the flight from the list
			else
				prevElem->pNext = thisElem->pNext;// remove the flight from the list
			if(thisTempList==NULL){// save the flight to add later
                 tempList= thisElem;
                 thisTempList=thisElem;
			}
            else  {
                thisTempList->pNext=thisElem;
                thisTempList=thisTempList->pNext;
            }
		}
		else{
            prevElem=thisElem;
	}
	thisElem = thisElem->pNext;
	}
    while(tempList != NULL)// add back all the flights
    {
         addFlight(runwayToDelay, tempList->pFlight);
        tempList =tempList->pNext;
    }
}
