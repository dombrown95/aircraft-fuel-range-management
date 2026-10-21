
#include "FuelCalculations.h"

namespace AFRM
{
    double calculateFlightTime(double distance, double groundSpeed)
    {
        return distance / groundSpeed;
    }

    double calculateJourneyFuel(double flightTime, double consumptionRate)
    {
        return flightTime * consumptionRate;
    }

    double calculateFuelBalance(double availableFuel, double journeyFuel)
    {
        return availableFuel - journeyFuel;
    }

    double calculateMaximumRange(double availableFuel,
        double consumptionRate,
        double groundSpeed)
    {
        return (availableFuel / consumptionRate) * groundSpeed;
    }
}
