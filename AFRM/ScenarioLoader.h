#pragma once

#include <string>
#include <vector>

namespace AFRM {

    struct Scenario
    {
        std::string id;
        double availableFuel = 0.0;
        double consumptionRate = 0.0;
        double groundSpeed = 0.0;
        double distance = 0.0;
        double reserveFuel = 0.0;
    };

    struct ScenarioInfo {
        std::string id;
        std::string description;
    };

    Scenario loadScenario(
        const std::string& filePath,
        const std::string& scenarioId
    );

    std::vector<ScenarioInfo> listScenarios(
        const std::string& filePath
    );

}