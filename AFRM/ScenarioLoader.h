#pragma once

#include <string>
#include <vector>

namespace AFRM
{
    struct Scenario
    {
        std::string id;
        double availableFuel;
        double consumptionRate;
        double groundSpeed;
        double distance;
        double reserveFuel;
    };

    Scenario loadScenario(
        const std::string& filePath,
        const std::string& scenarioId
    );

    Scenario loadScenario(
        const std::string& filePath, 
        const std::string& scenarioId
    );

    std::vector<std::string> 

        listScenarioIds(
            const std::string& filePath
        );

}
