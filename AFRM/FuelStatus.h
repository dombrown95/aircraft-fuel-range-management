
#pragma once

#include <string>

namespace AFRM
{
    enum class FuelStatus
    {
        SUFFICIENT,
        RESERVE_SHORTFALL,
        INSUFFICIENT
    };

    FuelStatus determineFuelStatus(
        double fuelBalance,
        double reserveFuel
    );

    std::string fuelStatusToString(FuelStatus status);
}
