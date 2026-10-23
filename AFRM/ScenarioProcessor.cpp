#include "ScenarioProcessor.h"

#include "FuelCalculations.h"
#include "FuelStatus.h"

#include <cmath>
#include <format>
#include <ostream>
#include <stdexcept>
#include <string>

namespace AFRM
{
    void processScenario(
        const Scenario& scenario,
        std::ostream& output,
        bool useColour)
    {
        // Calculates the results using unrounded values
        double flightTime = calculateFlightTime(
            scenario.distance, scenario.groundSpeed);

        double journeyFuel = calculateJourneyFuel(
            flightTime, scenario.consumptionRate);

        double fuelBalance = calculateFuelBalance(
            scenario.availableFuel, journeyFuel);

        double maximumRange = calculateMaximumRange(
            scenario.availableFuel,
            scenario.consumptionRate,
            scenario.groundSpeed);

        // Validates the results before displaying anything
        if (!std::isfinite(flightTime) ||
            !std::isfinite(journeyFuel) ||
            !std::isfinite(fuelBalance) ||
            !std::isfinite(maximumRange))
        {
            throw std::runtime_error(
                "Calculation produced a non-finite result");
        }

        FuelStatus status = determineFuelStatus(
            fuelBalance, scenario.reserveFuel);

        // Formats the displayed values using C++20 std::format
        output << "\nScenario: " << scenario.id << "\n\n";

        output << "Inputs:\n";

        output << std::format(
            "Available fuel: {:.2f} kg\n",
            scenario.availableFuel);

        output << std::format(
            "Consumption rate: {:.2f} kg/hour\n",
            scenario.consumptionRate);

        output << std::format(
            "Ground speed: {:.2f} knots\n",
            scenario.groundSpeed);

        output << std::format(
            "Journey distance: {:.2f} NM\n",
            scenario.distance);

        output << std::format(
            "Reserve fuel: {:.2f} kg\n",
            scenario.reserveFuel);

        output << "\nCalculated results:\n";

        output << std::format(
            "Flight time: {:.2f} hours\n",
            flightTime);

        output << std::format(
            "Journey fuel: {:.2f} kg\n",
            journeyFuel);

        output << std::format(
            "Fuel balance: {:.2f} kg\n",
            fuelBalance);

        output << std::format(
            "Maximum range (including reserve fuel): {:.2f} NM\n",
            maximumRange);

        // Applies colour to output fuel statuses when requested
        std::string colour;

        if (useColour)
        {
            switch (status)
            {
            case FuelStatus::SUFFICIENT:
                colour = "\033[32m";
                break;

            case FuelStatus::RESERVE_SHORTFALL:
                colour = "\033[33m";
                break;

            case FuelStatus::INSUFFICIENT:
                colour = "\033[31m";
                break;
            }
        }

        output << "\nFuel status: ";

        if (useColour)
        {
            output << colour;
        }

        output << fuelStatusToString(status);

        if (useColour)
        {
            output << "\033[0m";
        }

        output << '\n';
    }
}