
#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

#include "AFRM/ScenarioProcessor.h"

namespace AFRM::Tests
{
    // AFRM-009: Displays scenario inputs and results

    TEST(AFRM009, DisplaysScenarioIdAndInputs)
    {
        Scenario scenario{
            "SCN-001", 1500.0, 500.0,
            200.0, 400.0, 300.0
        };

        std::ostringstream output;

        processScenario(scenario, output);

        std::string text = output.str();

        EXPECT_NE(text.find("Scenario: SCN-001"), std::string::npos);
        EXPECT_NE(text.find("Available fuel: 1500.00 kg"), std::string::npos);
        EXPECT_NE(text.find("Consumption rate: 500.00 kg/hour"), std::string::npos);
        EXPECT_NE(text.find("Ground speed: 200.00 knots"), std::string::npos);
        EXPECT_NE(text.find("Journey distance: 400.00 NM"), std::string::npos);
        EXPECT_NE(text.find("Reserve fuel: 300.00 kg"), std::string::npos);
    }

    TEST(AFRM009, DisplaysCalculatedResults)
    {
        Scenario scenario{
            "SCN-001", 1500.0, 500.0,
            200.0, 400.0, 300.0
        };

        std::ostringstream output;

        processScenario(scenario, output);

        std::string text = output.str();

        EXPECT_NE(text.find("Flight time: 2.00 hours"), std::string::npos);
        EXPECT_NE(text.find("Journey fuel: 1000.00 kg"), std::string::npos);
        EXPECT_NE(text.find("Fuel balance: 500.00 kg"), std::string::npos);
        EXPECT_NE(
            text.find("Maximum range (including reserve fuel): 600.00 NM"),
            std::string::npos);
    }

    TEST(AFRM009, DisplaysCorrectFuelStatus)
    {
        Scenario scenario{
            "SCN-002", 1200.0, 500.0,
            200.0, 400.0, 300.0
        };

        std::ostringstream output;

        processScenario(scenario, output);

        EXPECT_NE(
            output.str().find("Fuel status: RESERVE SHORTFALL"),
            std::string::npos);
    }

    TEST(AFRM009, FormatsFractionalValuesToTwoDecimals)
    {
        Scenario scenario{
            "SCN-003", 1500.125, 500.0,
            200.0, 250.0, 300.0
        };

        std::ostringstream output;

        processScenario(scenario, output);

        std::string text = output.str();

        EXPECT_NE(text.find("Available fuel: 1500.12 kg"), std::string::npos);
        EXPECT_NE(text.find("Flight time: 1.25 hours"), std::string::npos);
    }

    // AFRM-010: Uses unrounded values and rejects non-finite results

    TEST(AFRM010, UsesUnroundedValuesForCalculations)
    {
        Scenario scenario{
            "SCN-004", 1000.0, 300.0,
            200.0, 100.0, 900.0
        };

        std::ostringstream output;

        processScenario(scenario, output);

        std::string text = output.str();

        // Flight time is 0.5 hours.
        // Journey fuel is 150 kg.
        // Fuel balance is 850 kg.
        EXPECT_NE(text.find("Flight time: 0.50 hours"), std::string::npos);
        EXPECT_NE(text.find("Journey fuel: 150.00 kg"), std::string::npos);
        EXPECT_NE(text.find("Fuel balance: 850.00 kg"), std::string::npos);
        EXPECT_NE(text.find("Fuel status: RESERVE SHORTFALL"), std::string::npos);
    }

    TEST(AFRM010, RejectsNonFiniteCalculationResult)
    {
        Scenario scenario{
            "SCN-005",
            std::numeric_limits<double>::max(),
            4.0,
            2.0,
            std::numeric_limits<double>::max(),
            0.0
        };

        std::ostringstream output;

        EXPECT_THROW(
            processScenario(scenario, output),
            std::runtime_error);

        EXPECT_TRUE(output.str().empty());
    }


    TEST(AFRM010, UsesUnroundedBalanceForFuelStatus)
    {
        Scenario scenario{
            "SCN-006",
            1000.0,
            100.0,
            3.0,
            1.0,
            966.668
        };

        std::ostringstream output;

        processScenario(scenario, output);

        std::string text = output.str();

        EXPECT_NE(text.find("Flight time: 0.33 hours"), std::string::npos);
        EXPECT_NE(text.find("Journey fuel: 33.33 kg"), std::string::npos);
        EXPECT_NE(text.find("Fuel status: RESERVE SHORTFALL"), std::string::npos);
    }
}
