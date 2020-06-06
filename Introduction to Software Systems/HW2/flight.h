#include "ex2.h"
#include <string.h>
#ifndef _flight_h
#define _flight_h
struct flight;
typedef struct flight* PFlight;
PFlight createFlight(int flightNum, FlightType fType, char* fDestination, BOOL isEmergency);
void destroyFlight(PFlight fToDestroy);
Result printFlight(PFlight fToPrint);
int getAFlightNum(PFlight pFlight);
FlightType getFlightType(PFlight pFlight);
char* getFlightDest(PFlight pFlight);
BOOL isFlightEmer(PFlight pFlight);
Result changeFlightDest(PFlight fToChangeDest, char* fNewDestination);
BOOL isDestLegal(char* s);
#endif // !_flight_h

