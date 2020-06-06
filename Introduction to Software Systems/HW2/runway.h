#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex2.h"
#include "flight.h"

#ifndef _Runway_h
#define _Runway_h

struct runway;
typedef struct runway* PRunway;
struct FlightElem;
typedef struct FlightElem* PFlightElem;
PFlightElem getRunwayList(PRunway pRunway);
FlightType getRunwayType(PRunway pRunway);
int getRunwayNum(PRunway pRunway);
PRunway createRunway(int runwayNum, FlightType rType);
void destroyRunway(PRunway runwayToDestroy);
BOOL isFlightExists(PRunway pRunway, int flightNum);
int getFlightNum(PRunway pRunway);
int getEmergencyNum(PRunway pRunway);
Result addFlight(PRunway pRunway, PFlight pFlight);
Result removeFlight(PRunway pRunway, int flightNum);
Result departFromRunway(PRunway pRunway); //check name
Result printRunway(PRunway pRunway);
Result runwayChangeDest(PRunway runwayToChangeDest, char* fDestinationOld, char* fDestinationNew);
void runwayDelay(PRunway runwayToDelay, char* fDestinationToDelay);
Result destroyFlightElem(PFlightElem pFElem);

#endif


