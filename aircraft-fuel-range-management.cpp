
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "AFRM/ScenarioLoader.h"
#include "AFRM/ScenarioProcessor.h"

int main()
{

    try {
        std::vector<std::string> scenarioIds =
            AFRM::listScenarioIds("scenarios.csv");

        std::cout << "\nAvailable scenarios:\n";

        if (scenarioIds.empty()) {
            std::cout << "  No scenarios available.\n";
        }
        else {
            for (const auto& id : scenarioIds) {
                std::cout << "  " << id << '\n';
            }
        }

        std::cout << '\n';
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    while (true)
    {
        std::string scenarioId;

        std::cout << "\nEnter scenario ID (or Q to quit): ";

        if (!std::getline(std::cin, scenarioId))
        {
            break;
        }

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

            AFRM::Scenario scenario = AFRM::loadScenario(
                "scenarios.csv", scenarioId);

            AFRM::processScenario(scenario, std::cout);
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
