#pragma once

#include <iosfwd>

#include "ScenarioLoader.h"

namespace AFRM
{
    void processScenario(
        const Scenario& scenario,
        std::ostream& output);
}
