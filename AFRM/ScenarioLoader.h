#pragma once

#include <string>

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
}
