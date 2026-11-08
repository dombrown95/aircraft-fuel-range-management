#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <format>

#include "ScenarioLoader.h"
#include "ScenarioProcessor.h"
#include "AircraftProfile.h"

int main()
{
    const std::string filePath = "scenarios.csv";

    std::cout << "Aircraft Fuel Range Management (AFRM)\n";
    std::cout << "-------------------------------------\n";

    try {
        std::vector<AFRM::ScenarioInfo> scenarios =
            AFRM::listScenarios(filePath);

        std::cout << "\nAvailable scenarios:\n\n";

        // Formats the scenario table using C++20 std::format
        std::cout << std::format("{:<10}{}\n", "ID", "Description");

        std::cout << std::string(40, '-') << '\n';

        for (const auto& scenario : scenarios) {
            std::cout << std::format(
                "{:<10}{}\n",
                scenario.id,
                scenario.description
            );
        }

        if (scenarios.empty()) {
            std::cout << "No scenarios available.\n";
        }

        std::cout << '\n';
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    while (true) {
        std::string scenarioId;

        std::cout << "Enter a scenario ID (Q to quit): ";

        if (!std::getline(std::cin, scenarioId)) {
            break;
        }

        if (scenarioId == "Q" || scenarioId == "q") {
            std::cout << "Exiting AFRM.\n";
            break;
        }

        try {
            if (scenarioId.empty()) {
                throw std::runtime_error("Scenario ID cannot be empty");
            }

            AFRM::Scenario scenario =
                AFRM::loadScenario(filePath, scenarioId);

            // Allows the user to select an aircraft profile
            std::cout << "\nAvailable aircraft profiles:\n";
            std::cout << "1. Light  (0.80)\n";
            std::cout << "2. Medium (1.00)\n";
            std::cout << "3. Heavy  (1.20)\n\n";

            std::cout << "Select an aircraft profile (1-3): ";

            std::string profileChoice;

            if (!std::getline(std::cin, profileChoice)) {
                break;
            }

            AFRM::AircraftType aircraftType;

            if (profileChoice == "1") {
                aircraftType = AFRM::AircraftType::Light;
            }
            else if (profileChoice == "2") {
                aircraftType = AFRM::AircraftType::Medium;
            }
            else if (profileChoice == "3") {
                aircraftType = AFRM::AircraftType::Heavy;
            }
            else {
                throw std::invalid_argument(
                    "Invalid aircraft profile selection");
            }

            AFRM::processScenario(
                scenario,
                std::cout,
                true,
                aircraftType);

            std::cout << '\n';
        }
        catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
            return 1;
        }
    }

    return 0;
}
