
#include "FuelStatus.h"

namespace AFRM
{
    FuelStatus determineFuelStatus(
        double fuelBalance,
        double reserveFuel)
    {
        if (fuelBalance < 0.0)
        {
            return FuelStatus::INSUFFICIENT;
        }

        if (fuelBalance < reserveFuel)
        {
            return FuelStatus::RESERVE_SHORTFALL;
        }

        return FuelStatus::SUFFICIENT;
    }

    std::string fuelStatusToString(FuelStatus status)
    {
        switch (status)
        {
        case FuelStatus::SUFFICIENT:
            return "SUFFICIENT";

        case FuelStatus::RESERVE_SHORTFALL:
            return "RESERVE SHORTFALL";

        case FuelStatus::INSUFFICIENT:
            return "INSUFFICIENT";

        default:
            return "UNKNOWN";
        }
    }
}
