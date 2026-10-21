#pragma once

#include <string>

namespace AFRM
{
    enum class FuelStatus
    {
        Sufficient,
        Reserve,
        Deficit
    };

    FuelStatus determineFuelStatus(double fuelBalance, double reserveFuel);

    std::string fuelStatusToString(FuelStatus status);
}
