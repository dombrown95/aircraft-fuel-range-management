#include <gtest/gtest.h>
#include <stdexcept>

#include "AFRM.Core/AircraftProfile.h"

namespace AFRM::Tests
{
    // AFRM-011: Aircraft profile selection and validation

    TEST(AFRM011, SelectsLightAircraftProfile)
    {
        auto profile = getAircraftProfile(AircraftType::Light);

        EXPECT_EQ(profile.name, "Light");
        EXPECT_DOUBLE_EQ(profile.consumptionFactor, 0.80);
    }

    TEST(AFRM011, SelectsMediumAircraftProfile)
    {
        auto profile = getAircraftProfile(AircraftType::Medium);

        EXPECT_EQ(profile.name, "Medium");
        EXPECT_DOUBLE_EQ(profile.consumptionFactor, 1.00);
    }

    TEST(AFRM011, SelectsHeavyAircraftProfile)
    {
        auto profile = getAircraftProfile(AircraftType::Heavy);

        EXPECT_EQ(profile.name, "Heavy");
        EXPECT_DOUBLE_EQ(profile.consumptionFactor, 1.20);
    }

    TEST(AFRM011, RejectsInvalidAircraftProfile)
    {
        EXPECT_THROW(
            getAircraftProfile(static_cast<AircraftType>(99)),
            std::invalid_argument);
    }
}
