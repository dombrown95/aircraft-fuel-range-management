
#include <gtest/gtest.h>
#include <algorithm>
#include <cmath>

#include "AFRM/FuelCalculations.h"

namespace
{
    void expectCalculationNear(double actual, double expected)
    {
        double tolerance = std::max(
            0.000001,
            0.000001 * std::abs(expected));

        EXPECT_NEAR(actual, expected, tolerance);
    }
}

namespace AFRM::Tests
{

// AFRM-004: Flight time = distance / ground speed

TEST(AFRM004, CalculatesFlightTime)
{
    double actual = AFRM::calculateFlightTime(400.0, 200.0);
    expectCalculationNear(actual, 2.0);
}

TEST(AFRM004, ZeroDistanceProducesZeroTime)
{
    double actual = AFRM::calculateFlightTime(0.0, 200.0);
    expectCalculationNear(actual, 0.0);
}

TEST(AFRM004, CalculatesFractionalFlightTime)
{
    double actual = AFRM::calculateFlightTime(250.0, 200.0);
    expectCalculationNear(actual, 1.25);
}

// AFRM-005: Journey fuel = flight time * consumption rate

TEST(AFRM005, CalculatesJourneyFuel)
{
    double actual = AFRM::calculateJourneyFuel(2.0, 500.0);
    expectCalculationNear(actual, 1000.0);
}

TEST(AFRM005, ZeroFlightTimeProducesZeroFuel)
{
    double actual = AFRM::calculateJourneyFuel(0.0, 500.0);
    expectCalculationNear(actual, 0.0);
}

// AFRM-006: Fuel balance = available fuel - journey fuel

TEST(AFRM006, CalculatesPositiveFuelBalance)
{
    double actual = AFRM::calculateFuelBalance(1500.0, 1000.0);
    expectCalculationNear(actual, 500.0);
}

TEST(AFRM006, CalculatesNegativeFuelBalance)
{
    double actual = AFRM::calculateFuelBalance(900.0, 1000.0);
    expectCalculationNear(actual, -100.0);
}

TEST(AFRM006, CalculatesZeroFuelBalance)
{
    double actual = AFRM::calculateFuelBalance(1000.0, 1000.0);
    expectCalculationNear(actual, 0.0);
}

// AFRM-007: Maximum range =
// (available fuel / consumption rate) * ground speed

TEST(AFRM007, CalculatesMaximumRange)
{
    double actual = AFRM::calculateMaximumRange(
        1500.0, 500.0, 200.0);

    expectCalculationNear(actual, 600.0);
}

TEST(AFRM007, ZeroAvailableFuelProducesZeroRange)
{
    double actual = AFRM::calculateMaximumRange(
        0.0, 500.0, 200.0);

    expectCalculationNear(actual, 0.0);
}

TEST(AFRM007, CalculatesFractionalMaximumRange)
{
    double actual = AFRM::calculateMaximumRange(
        1250.0, 400.0, 180.0);

    expectCalculationNear(actual, 562.5);
}

} // namespace AFRM::Tests
