#pragma once

#include <iosfwd>
#include "ScenarioLoader.h"
#include "AircraftProfile.h"

namespace AFRM
{
    void processScenario(
        const Scenario& scenario,
        std::ostream& output,
        bool useColour = false,
        AircraftType aircraftType = AircraftType::Medium);
}
