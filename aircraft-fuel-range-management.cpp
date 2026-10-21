
#include <iostream>
#include <exception>
#include <cmath>

#include "AFRM/FuelCalculations.h"
#include "AFRM/FuelStatus.h"
#include "AFRM/ScenarioLoader.h"

int main()
{
    try
    {
        // Loads the selected scenario from CSV
        AFRM::Scenario scenario = AFRM::loadScenario(
            "scenarios.csv", "SCN-005");

        // Calculates the fuel requirements and range
        double flightTime = AFRM::calculateFlightTime(
            scenario.distance, scenario.groundSpeed);

        double journeyFuel = AFRM::calculateJourneyFuel(
            flightTime, scenario.consumptionRate);

        double fuelBalance = AFRM::calculateFuelBalance(
            scenario.availableFuel, journeyFuel);

        double maximumRange = AFRM::calculateMaximumRange(
            scenario.availableFuel,
            scenario.consumptionRate,
            scenario.groundSpeed);

        // Rejects any non-finite calculation results
        if (!std::isfinite(flightTime) ||
            !std::isfinite(journeyFuel) ||
            !std::isfinite(fuelBalance) ||
            !std::isfinite(maximumRange))
        {
            throw std::runtime_error(
                "Calculation produced a non-finite result");
        }

        // Determines the fuel status
        AFRM::FuelStatus status = AFRM::determineFuelStatus(
            fuelBalance, scenario.reserveFuel);

        // Displays the results
        std::cout << "Scenario: " << scenario.id << "\n";
        std::cout << "Flight time: " << flightTime << " hours\n";
        std::cout << "Journey fuel: " << journeyFuel << " kg\n";
        std::cout << "Fuel balance: " << fuelBalance << " kg\n";
        std::cout << "Maximum range (including reserve): "
            << maximumRange << " NM\n";
        std::cout << "Fuel status: "
            << AFRM::fuelStatusToString(status) << "\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }
}
