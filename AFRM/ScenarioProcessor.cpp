#include "ScenarioProcessor.h"

#include "FuelCalculations.h"
#include "FuelStatus.h"

#include <cmath>
#include <iomanip>
#include <stdexcept>

namespace AFRM
{
    void processScenario(
        const Scenario& scenario,
        std::ostream& output)
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

        // Formats the displayed values only
        output << std::fixed << std::setprecision(2);

        output << "\nScenario: " << scenario.id << "\n\n";

        output << "Inputs:\n";
        output << "Available fuel: "
            << scenario.availableFuel << " kg\n";
        output << "Consumption rate: "
            << scenario.consumptionRate << " kg/hour\n";
        output << "Ground speed: "
            << scenario.groundSpeed << " knots\n";
        output << "Journey distance: "
            << scenario.distance << " NM\n";
        output << "Reserve fuel: "
            << scenario.reserveFuel << " kg\n";

        output << "\nCalculated results:\n";
        output << "Flight time: "
            << flightTime << " hours\n";
        output << "Journey fuel: "
            << journeyFuel << " kg\n";
        output << "Fuel balance: "
            << fuelBalance << " kg\n";
        output << "Maximum range (including reserve fuel): "
            << maximumRange << " NM\n";

        output << "\nFuel status: "
            << fuelStatusToString(status) << "\n";
    }
}
