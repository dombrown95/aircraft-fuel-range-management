#include "ScenarioLoader.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace AFRM
{
    namespace
    {
        std::vector<std::string> splitCsvLine(
            const std::string& line)
        {
            std::vector<std::string> fields;
            std::stringstream stream(line);
            std::string field;

            while (std::getline(stream, field, ','))
            {
                fields.push_back(field);
            }

            // Preserves a missing final field.
            if (!line.empty() && line.back() == ',')
            {
                fields.push_back("");
            }

            return fields;
        }

        double parseInput(
            const std::string& text,
            const std::string& inputName,
            bool mustBePositive)
        {
            if (text.empty())
            {
                throw std::runtime_error(
                    "Missing value for " + inputName);
            }

            std::size_t charactersRead = 0;
            double value;

            try
            {
                value = std::stod(text, &charactersRead);
            }
            catch (const std::exception&)
            {
                throw std::runtime_error(
                    "Invalid numeric value for " + inputName);
            }

            if (charactersRead != text.size())
            {
                throw std::runtime_error(
                    "Invalid numeric value for " + inputName);
            }

            if (!std::isfinite(value))
            {
                throw std::runtime_error(
                    "Non-finite value for " + inputName);
            }

            if (mustBePositive && value <= 0.0)
            {
                throw std::runtime_error(
                    inputName + " must be greater than zero");
            }

            if (!mustBePositive && value < 0.0)
            {
                throw std::runtime_error(
                    inputName + " must not be negative");
            }

            return value;
        }
    }

    Scenario loadScenario(
        const std::string& filePath,
        const std::string& scenarioId)
    {
        std::ifstream file(filePath);

        if (!file.is_open())
        {
            throw std::runtime_error(
                "Unable to open CSV file: " + filePath);
        }

        std::string line;

        // Reads and checks the header.
        if (!std::getline(file, line))
        {
            throw std::runtime_error("CSV file is empty");
        }

        const std::vector<std::string> expectedHeader = {
            "scenario_id",
            "available_fuel",
            "consumption_rate",
            "ground_speed",
            "distance",
            "reserve_fuel"
        };

        if (splitCsvLine(line) != expectedHeader)
        {
            throw std::runtime_error(
                "CSV file has an invalid header");
        }

        while (std::getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }

            std::vector<std::string> fields =
                splitCsvLine(line);

            if (fields.empty() || fields[0] != scenarioId)
            {
                continue;
            }

            if (fields.size() != 6)
            {
                throw std::runtime_error(
                    "Scenario has an incorrect number of fields");
            }

            Scenario scenario;

            scenario.id = fields[0];

            scenario.availableFuel = parseInput(
                fields[1], "Available fuel", false);

            scenario.consumptionRate = parseInput(
                fields[2], "Consumption rate", true);

            scenario.groundSpeed = parseInput(
                fields[3], "Ground speed", true);

            scenario.distance = parseInput(
                fields[4], "Journey distance", false);

            scenario.reserveFuel = parseInput(
                fields[5], "Reserve fuel", false);

            return scenario;
        }

        if (file.bad())
        {
            throw std::runtime_error(
                "Error while reading CSV file");
        }

        throw std::runtime_error(
            "Scenario not found: " + scenarioId);
    }
}
