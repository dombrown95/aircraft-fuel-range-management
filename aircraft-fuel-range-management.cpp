
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cmath>

#include "AFRM/FuelCalculations.h"
#include "AFRM/FuelStatus.h"
#include "AFRM/ScenarioLoader.h"

int main()
{
    while (true)
    {
        std::string scenarioId;

        std::cout << "\nEnter scenario ID (or Q to quit): ";
        if (!std::getline(std::cin, scenarioId))
        {
            break;
        }

        // Exits if the user chooses to quit
        if (scenarioId == "Q" || scenarioId == "q")
        {
            break;
        }

        try
        {
            if (scenarioId.empty())
            {
                throw std::runtime_error("No scenario ID entered");
            }

            // Loads the selected scenario
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

            // Checks for non-finite calculation results
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

            // Displays the scenario inputs and results
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
        }
        catch (const std::exception& error)
        {
            std::cerr << "\nError: " << error.what() << "\n";
            return 1;
        }
    }

    std::cout << "\nExiting AFRM application.\n";
    return 0;
}
