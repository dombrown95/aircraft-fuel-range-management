#include "AircraftProfile.h"

#include <stdexcept>

AircraftProfile getAircraftProfile(AircraftType type)
{
    switch (type)
    {
    case AircraftType::Light:
        return { type, "Light", 20000.0, 0.80 };

    case AircraftType::Medium:
        return { type, "Medium", 40000.0, 1.00 };

    case AircraftType::Heavy:
        return { type, "Heavy", 60000.0, 1.20 };

    default:
        throw std::invalid_argument("Invalid aircraft profile");
    }
}