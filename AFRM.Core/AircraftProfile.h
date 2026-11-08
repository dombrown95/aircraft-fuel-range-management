#pragma once

#include <string>

enum class AircraftType
{
    Light,
    Medium,
    Heavy
};

struct AircraftProfile
{
    AircraftType type;
    std::string name;
    double weightKg;
    double consumptionFactor;
};

AircraftProfile getAircraftProfile(AircraftType type);
