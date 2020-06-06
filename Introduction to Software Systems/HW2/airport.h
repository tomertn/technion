#include "ex2.h"
#include "runway.h"
#include "flight.h"
#ifndef _airport_h
#define _airport_h
struct airport;
typedef struct airport* Pairport;
Result addRunway(int runwayNum, FlightType runwayType);
Result removeRunway(int runwayNum);
Result addFlightToAirport(int flightNum, FlightType fType, char* fDestination, BOOL isEmergency);
Result depart();
Result changeDest(char* fDestinationOld, char* fDestinationNew);
Result delay(char* fDestination);
Result printAirport();
void destroyAirport();
//Result changeDest(char* fDestinationOld, char* fDestinationNew);
#endif // !_airport_h

