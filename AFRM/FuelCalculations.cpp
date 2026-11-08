#include "FuelCalculations.h"

#include <algorithm>

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

    double calculateAdjustedConsumption(double baseConsumption,
        double consumptionFactor)
    {
        return baseConsumption * consumptionFactor;
    }

    double calculateReserveAwareRange(double availableFuel,
        double reserveFuel,
        double adjustedConsumption,
        double groundSpeed)
    {
        const double usableFuel =
            std::max(0.0, availableFuel - reserveFuel);

        return (usableFuel / adjustedConsumption) * groundSpeed;
    }
}
