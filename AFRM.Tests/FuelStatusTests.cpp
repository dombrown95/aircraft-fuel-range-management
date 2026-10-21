
#include <gtest/gtest.h>

#include "AFRM/FuelStatus.h"

namespace AFRM::Tests
{
    // AFRM-008: Fuel status classification

    TEST(AFRM008, SufficientFuelAboveReserve)
    {
        auto status = AFRM::determineFuelStatus(500.0, 300.0);

        EXPECT_EQ(status, AFRM::FuelStatus::SUFFICIENT);
    }

    TEST(AFRM008, SufficientFuelAtReserveBoundary)
    {
        auto status = AFRM::determineFuelStatus(300.0, 300.0);

        EXPECT_EQ(status, AFRM::FuelStatus::SUFFICIENT);
    }

    TEST(AFRM008, ReserveShortfallBelowReserveBoundary)
    {
        auto status = AFRM::determineFuelStatus(299.99, 300.0);

        EXPECT_EQ(status, AFRM::FuelStatus::RESERVE_SHORTFALL);
    }

    TEST(AFRM008, ReserveShortfallWithZeroBalance)
    {
        auto status = AFRM::determineFuelStatus(0.0, 300.0);

        EXPECT_EQ(status, AFRM::FuelStatus::RESERVE_SHORTFALL);
    }

    TEST(AFRM008, InsufficientFuelBelowZero)
    {
        auto status = AFRM::determineFuelStatus(-0.01, 300.0);

        EXPECT_EQ(status, AFRM::FuelStatus::INSUFFICIENT);
    }

    TEST(AFRM008, ZeroReserveAndZeroBalance)
    {
        auto status = AFRM::determineFuelStatus(0.0, 0.0);

        EXPECT_EQ(status, AFRM::FuelStatus::SUFFICIENT);
    }

    TEST(AFRM008, ZeroReserveWithPositiveBalance)
    {
        auto status = AFRM::determineFuelStatus(100.0, 0.0);

        EXPECT_EQ(status, AFRM::FuelStatus::SUFFICIENT);
    }
}
