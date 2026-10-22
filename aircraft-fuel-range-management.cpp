
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>

#include "ScenarioLoader.h"
#include "ScenarioProcessor.h"

int main()
{
    const std::string filePath = "scenarios.csv";

    std::cout << "Aircraft Fuel Range Management (AFRM)\n";
    std::cout << "-------------------------------------\n";

    try {
        std::vector<AFRM::ScenarioInfo> scenarios =
            AFRM::listScenarios(filePath);

        std::cout << "\nAvailable scenarios:\n\n";

        std::cout << std::left
            << std::setw(10) << "ID"
            << "Description\n";

        std::cout << std::string(40, '-') << '\n';

        for (const auto& scenario : scenarios) {
            std::cout << std::left
                << std::setw(10) << scenario.id
                << scenario.description << '\n';
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

            AFRM::processScenario(scenario, std::cout);

            std::cout << '\n';
        }
        catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
            return 1;
        }
    }

    return 0;
}
