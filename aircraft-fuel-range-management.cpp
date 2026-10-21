#include <iostream>
#include "AFRM/FuelCalculations.h"

int main()
{
    double availableFuel = 1500.0;
    double consumptionRate = 500.0;
    double groundSpeed = 200.0;
    double distance = 400.0;

    double flightTime = AFRM::calculateFlightTime(distance, groundSpeed);
    double journeyFuel = AFRM::calculateJourneyFuel(flightTime, consumptionRate);
    double fuelBalance = AFRM::calculateFuelBalance(availableFuel, journeyFuel);
    double maximumRange = AFRM::calculateMaximumRange(
        availableFuel, consumptionRate, groundSpeed);

    std::cout << "Flight time: " << flightTime << " hours\n";
    std::cout << "Journey fuel: " << journeyFuel << " kg\n";
    std::cout << "Fuel balance: " << fuelBalance << " kg\n";
    std::cout << "Maximum range: " << maximumRange << " NM\n";

    return 0;
}
