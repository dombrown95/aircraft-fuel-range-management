
#include <iostream>
#include <exception>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <string>

#include "AFRM/FuelCalculations.h"
#include "AFRM/FuelStatus.h"
#include "AFRM/ScenarioLoader.h"

int main()
{
    try
    {
        std::string scenarioId;

        std::cout << "Enter scenario ID: ";
        std::getline(std::cin, scenarioId);

        if (scenarioId.empty())
        {
            throw std::runtime_error("No scenario ID entered");
        }

        AFRM::Scenario scenario = AFRM::loadScenario(
            "scenarios.csv", scenarioId);

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

        // Displays the results (to 2 decimal places - AFRM-009)
        std::cout << std::fixed << std::setprecision(2);

        std::cout << "\nScenario: " << scenario.id << "\n\n";

        std::cout << "Inputs:\n";
        std::cout << "Available fuel: " << scenario.availableFuel << " kg\n";
        std::cout << "Consumption rate: " << scenario.consumptionRate << " kg/hour\n";
        std::cout << "Ground speed: " << scenario.groundSpeed << " knots\n";
        std::cout << "Journey distance: " << scenario.distance << " NM\n";
        std::cout << "Reserve fuel: " << scenario.reserveFuel << " kg\n";

        std::cout << "\nCalculated results:\n";
        std::cout << "Flight time: " << flightTime << " hours\n";
        std::cout << "Journey fuel: " << journeyFuel << " kg\n";
        std::cout << "Fuel balance: " << fuelBalance << " kg\n";
        std::cout << "Maximum range (including reserve fuel): "
            << maximumRange << " NM\n";

        std::cout << "\nFuel status: "
            << AFRM::fuelStatusToString(status) << "\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }
}