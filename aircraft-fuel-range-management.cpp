#include <iostream>
#include "AFRM/FuelCalculations.h"
#include "AFRM/FuelStatus.h"

int main()
{
    double availableFuel = 900.0;
    double consumptionRate = 500.0;
    double groundSpeed = 200.0;
    double distance = 400.0;
    double reserveFuel = 300.0;

    // Calculations for fuel requirements and range
    double flightTime = AFRM::calculateFlightTime(distance, groundSpeed);
    double journeyFuel = AFRM::calculateJourneyFuel(flightTime, consumptionRate);
    double fuelBalance = AFRM::calculateFuelBalance(availableFuel, journeyFuel);
    double maximumRange = AFRM::calculateMaximumRange(
        availableFuel, consumptionRate, groundSpeed);

    // Determines the fuel status
    AFRM::FuelStatus status = AFRM::determineFuelStatus(
        fuelBalance, reserveFuel);

    // Displays the results
    std::cout << "Flight time: " << flightTime << " hours\n";
    std::cout << "Journey fuel: " << journeyFuel << " kg\n";
    std::cout << "Fuel balance: " << fuelBalance << " kg\n";
    std::cout << "Maximum range: " << maximumRange << " NM\n";
    std::cout << "Fuel status: " << AFRM::fuelStatusToString(status) << "\n";

    return 0;
}
