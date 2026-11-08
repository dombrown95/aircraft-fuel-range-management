#pragma once

namespace AFRM
{
    // AFRM-004: Calculate flight time in hours
    double calculateFlightTime(double distance, double groundSpeed);

    // AFRM-005: Calculate journey fuel in kg
    double calculateJourneyFuel(double flightTime, double consumptionRate);

    // AFRM-006: Calculate remaining fuel in kg
    double calculateFuelBalance(double availableFuel, double journeyFuel);

    // AFRM-007: Calculate theoretical maximum range in NM
    double calculateMaximumRange(double availableFuel,
        double consumptionRate,
        double groundSpeed);

    // AFRM-012: Adjust consumption using the aircraft profile factor
    double calculateAdjustedConsumption(double baseConsumption,
        double consumptionFactor);

    // AFRM-013: Calculate range while maintaining reserve fuel
    double calculateReserveAwareRange(double availableFuel,
        double reserveFuel,
        double adjustedConsumption,
        double groundSpeed);
}
