
#include <gtest/gtest.h>

#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include "AFRM/ScenarioLoader.h"

namespace AFRM::Tests
{
    namespace
    {
        constexpr const char* csvHeader =
            "scenario_id,available_fuel,consumption_rate,"
            "ground_speed,distance,reserve_fuel\n";

        // Creates a temporary CSV file for each test.
        class ScenarioLoaderTest : public ::testing::Test
        {
        protected:
            std::filesystem::path filePath;

            void SetUp() override
            {
                static unsigned long long fileCounter = 0;

                filePath = std::filesystem::temp_directory_path() /
                    ("afrm_test_" +
                        std::to_string(
                            std::chrono::steady_clock::now()
                            .time_since_epoch().count()) +
                        "_" + std::to_string(++fileCounter) + ".csv");
            }

            void TearDown() override
            {
                std::error_code error;
                std::filesystem::remove(filePath, error);
            }

            void writeCsv(const std::string& content)
            {
                std::ofstream file(filePath, std::ios::trunc);

                if (!file)
                {
                    throw std::runtime_error(
                        "Unable to create test CSV file");
                }

                file << content;

                if (!file)
                {
                    throw std::runtime_error(
                        "Unable to write test CSV file");
                }
            }

            AFRM::Scenario load(const std::string& id = "SCN-001")
            {
                return AFRM::loadScenario(filePath.string(), id);
            }

            void expectInvalidRow(const std::string& row)
            {
                writeCsv(std::string(csvHeader) + row + "\n");

                EXPECT_THROW(load(), std::runtime_error);
            }
        };
    }

    // AFRM-001: Load a selected CSV scenario

    TEST_F(ScenarioLoaderTest, AFRM001_LoadsValidScenario)
    {
        writeCsv(std::string(csvHeader) +
            "SCN-001,1500,500,200,400,300\n");

        AFRM::Scenario scenario = load();

        EXPECT_EQ(scenario.id, "SCN-001");
        EXPECT_DOUBLE_EQ(scenario.availableFuel, 1500.0);
        EXPECT_DOUBLE_EQ(scenario.consumptionRate, 500.0);
        EXPECT_DOUBLE_EQ(scenario.groundSpeed, 200.0);
        EXPECT_DOUBLE_EQ(scenario.distance, 400.0);
        EXPECT_DOUBLE_EQ(scenario.reserveFuel, 300.0);
    }

    TEST_F(ScenarioLoaderTest, AFRM001_SelectsCorrectScenario)
    {
        writeCsv(std::string(csvHeader) +
            "SCN-001,1500,500,200,400,300\n"
            "SCN-002,1200,400,180,350,200\n");

        AFRM::Scenario scenario = load("SCN-002");

        EXPECT_EQ(scenario.id, "SCN-002");
        EXPECT_DOUBLE_EQ(scenario.availableFuel, 1200.0);
        EXPECT_DOUBLE_EQ(scenario.consumptionRate, 400.0);
        EXPECT_DOUBLE_EQ(scenario.groundSpeed, 180.0);
        EXPECT_DOUBLE_EQ(scenario.distance, 350.0);
        EXPECT_DOUBLE_EQ(scenario.reserveFuel, 200.0);
    }

    // AFRM-002: Validate inputs against documented ranges

    TEST_F(ScenarioLoaderTest, AFRM002_AcceptsZeroWherePermitted)
    {
        writeCsv(std::string(csvHeader) +
            "SCN-001,0,500,200,0,0\n");

        AFRM::Scenario scenario = load();

        EXPECT_DOUBLE_EQ(scenario.availableFuel, 0.0);
        EXPECT_DOUBLE_EQ(scenario.distance, 0.0);
        EXPECT_DOUBLE_EQ(scenario.reserveFuel, 0.0);
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsNegativeAvailableFuel)
    {
        expectInvalidRow("SCN-001,-1,500,200,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsZeroConsumptionRate)
    {
        expectInvalidRow("SCN-001,1500,0,200,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsNegativeConsumptionRate)
    {
        expectInvalidRow("SCN-001,1500,-1,200,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsZeroGroundSpeed)
    {
        expectInvalidRow("SCN-001,1500,500,0,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsNegativeGroundSpeed)
    {
        expectInvalidRow("SCN-001,1500,500,-1,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsNegativeDistance)
    {
        expectInvalidRow("SCN-001,1500,500,200,-1,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsNegativeReserveFuel)
    {
        expectInvalidRow("SCN-001,1500,500,200,400,-1");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsMissingValue)
    {
        expectInvalidRow("SCN-001,1500,,200,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsMissingFinalValue)
    {
        expectInvalidRow("SCN-001,1500,500,200,400,");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsNonNumericValue)
    {
        expectInvalidRow("SCN-001,1500,abc,200,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsPartiallyNumericValue)
    {
        expectInvalidRow("SCN-001,1500,500abc,200,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsNaN)
    {
        expectInvalidRow("SCN-001,nan,500,200,400,300");
    }

    TEST_F(ScenarioLoaderTest, AFRM002_RejectsInfinity)
    {
        expectInvalidRow("SCN-001,inf,500,200,400,300");
    }

    // AFRM-003: Reject invalid files and scenarios

    TEST_F(ScenarioLoaderTest, AFRM003_RejectsMissingFile)
    {
        EXPECT_THROW(load(), std::runtime_error);
    }

    TEST_F(ScenarioLoaderTest, AFRM003_RejectsEmptyFile)
    {
        writeCsv("");

        EXPECT_THROW(load(), std::runtime_error);
    }

    TEST_F(ScenarioLoaderTest, AFRM003_RejectsInvalidHeader)
    {
        writeCsv(
            "id,fuel,rate,speed,distance,reserve\n"
            "SCN-001,1500,500,200,400,300\n");

        EXPECT_THROW(load(), std::runtime_error);
    }

    TEST_F(ScenarioLoaderTest, AFRM003_RejectsUnknownScenario)
    {
        writeCsv(std::string(csvHeader) +
            "SCN-001,1500,500,200,400,300\n");

        EXPECT_THROW(load("SCN-999"), std::runtime_error);
    }

    TEST_F(ScenarioLoaderTest, AFRM003_RejectsIncorrectFieldCount)
    {
        expectInvalidRow("SCN-001,1500,500,200,400");
    }
}
