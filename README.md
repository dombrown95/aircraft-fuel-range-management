# aircraft-fuel-range-management

## Overview
The Aircraft Fuel Range Management (AFRM) prototype calculates fuel requirements, remaining fuel and maximum range for a selected flight scenario. Users can select one of three aircraft profiles (Light, Medium or Heavy), which adjust fuel consumption using predefined factors. The application also calculates reserve-aware range and classifies whether the journey can be completed while maintaining the required fuel reserve.

The prototype demonstrates how fuel calculations and status classifications can support flight planning decisions.
## Functional Requirements

| ID | Requirement |
|---|---|
| AFRM-001 | The prototype shall load a scenario selected by its ID from a CSV file containing available fuel, consumption rate, ground speed, distance and reserve fuel. |
| AFRM-002 | The prototype shall reject missing, non-numeric, non-finite or out-of-range inputs, using the Inputs and Units table. |
| AFRM-003 | The prototype shall identify the cause and end without displaying calculated results or fuel status if a file, scenario or input error occurs. |
| AFRM-004 | The prototype shall calculate flight time as distance divided by ground speed. |
| AFRM-005 | The prototype shall calculate journey fuel as flight time multiplied by the adjusted consumption rate. |
| AFRM-006 | The prototype shall calculate fuel balance as available fuel minus journey fuel, identifying a negative result as a fuel deficit. |
| AFRM-007 | The prototype shall calculate theoretical maximum range using available fuel, adjusted consumption rate and ground speed. |
| AFRM-008 | The prototype shall assign fuel status according to the Fuel Status Rules table. |
| AFRM-009 | The prototype shall display the scenario ID, inputs, calculated results and fuel status. Fuel, distance, speed and time values shall include units and two decimal places. Maximum range shall be labelled as including reserve fuel. |
| AFRM-010 | The prototype shall use unrounded values for calculations and comparisons. If a calculation produces a non-finite result, the prototype shall report an error and end without displaying calculated results or fuel status. |
| AFRM-011 | The prototype shall allow selection of one of three predefined aircraft profiles and reject invalid selections. |
| AFRM-012 | The prototype shall calculate adjusted fuel consumption using the selected profile's factor. |
| AFRM-013 | The prototype shall calculate reserve-aware range using available fuel minus reserve fuel, adjusted consumption rate and ground speed, with a minimum result of 0 NM. |
| AFRM-014 | The prototype shall display the selected aircraft profile, adjusted consumption rate and reserve-aware range. |

## Aircraft Profiles (V1.1.0)

| Profile | Representative Weight (kg) | Consumption Factor |
|---------|---------------------------:|-------------------:|
| Light   | 20,000                     | 0.80               |
| Medium  | 40,000                     | 1.00               |
| Heavy   | 60,000                     | 1.20               |

Note: The weights and consumption factors are illustrative values used for testing and are not based on actual aircraft performance data.

## Inputs and Units

| Input | Unit | Valid range |
|---|---|---|
| Available fuel | kg | ≥ 0 |
| Consumption rate | kg/hour | > 0 |
| Ground speed | knots | > 0 |
| Journey distance | nautical miles | ≥ 0 |
| Reserve fuel | kg | ≥ 0 |

## CSV Scenario Format

Example CSV, with each row representing a flight scenario identified by a unique scenario ID:

```csv
scenario_id,available_fuel,consumption_rate,ground_speed,distance,reserve_fuel
SCN-001,5000,800,400,1000,1000
SCN-002,6500,900,450,2500,1000
SCN-003,4500,1200,400,1500,1000
```

## Output Units

| Output | Unit |
|---|---|
| Aircraft Profile | N/A (classification) |
| Adjusted Consumption Rate | kg/hour |
| Flight time | hours |
| Journey fuel | kg |
| Fuel balance | kg |
| Maximum range (including reserve fuel) | nautical miles |
| Reserve-aware range | nautical miles |
| Fuel status | N/A (classification) |

## Fuel Status Rules

| Status | Condition |
|---|---|
| SUFFICIENT | Available fuel ≥ journey fuel + reserve |
| RESERVE SHORTFALL | Available fuel ≥ journey fuel, but < journey fuel + reserve |
| INSUFFICIENT | Available fuel < journey fuel |

## Calculation Assumptions
The AFRM prototype uses the following assumptions to simplify the fuel and range calculations:

- Ground speed and fuel consumption remain constant throughout the journey.
- Fuel consumption does not account for changes in altitude, weather or flight conditions.
- Aircraft profiles use illustrative consumption factors of 0.80, 1.00 and 1.20, rather than validated aircraft performance data.
- Adjusted consumption is calculated by multiplying the scenario's consumption rate by the selected aircraft factor.
- Maximum range is theoretical and includes reserve fuel.
- Reserve-aware range excludes the required reserve fuel and cannot be less than 0 NM.
- Calculations use unrounded values, with results displayed to two decimal places.

**Adjusted consumption:**

`Adjusted consumption = Base consumption × Aircraft factor`

**Reserve-aware range:**

`Reserve-aware range = (max(0, Available fuel - Reserve fuel) / Adjusted consumption) × Ground speed`

Note: The prototype is intended for demonstration and testing purposes as part of a university assignment. It is not intended for real-world flight planning.

## Building the Prototype
The prototype is developed using C++20 and Visual Studio 2022 with the MSVC v143 toolset.

To build locally:
- Open aircraft-fuel-range-management.slnx in Visual Studio.
- Select the Release and x64 configuration.
- Select Build > Build Solution.
- GitHub Actions automatically builds the project using MSBuild on a Windows runner when a pull request targets main.
- The workflow is defined in the .github/workflows/windows-build.yml file.

## Running the Prototype
- After building the solution, run the aircraft-fuel-range-management project.
- Select a scenario using its ID (e.g. SCN-002).
- Select an aircraft profile: Light (1), Medium (2) or Heavy (3).
- The application displays the adjusted fuel calculations, reserve-aware range and fuel status.
- Enter another scenario ID to repeat the process, or Q to quit.
- Invalid aircraft profile selections are rejected with an error message.

## Testing

### Running tests: 
The project uses Google Test with Visual Studio's Test Adapter for Google Test. If tests are not discovered automatically, set the discovery regex under Tools → Options → Test Adapter for Google Test → General to .*AFRM\.Tests\.exe$.

### Requirements Verification Traceability Matrix

The following matrix links each AFRM software requirement to its corresponding automated GoogleTest cases. The original 46 tests have been retained (V1.0.0), with 13 additional tests introduced for AFRM-011 to AFRM-014 (V1.1.0). All 59 tests passed during local verification.
| Requirement | Test Name | Result |
|---|---|---|
| **AFRM-001** | `ScenarioLoaderTest.AFRM001_LoadsValidScenario` | Pass |
| | `ScenarioLoaderTest.AFRM001_SelectsCorrectScenario` | Pass |
| **AFRM-002** | `ScenarioLoaderTest.AFRM002_AcceptsZeroWherePermitted` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsNegativeAvailableFuel` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsZeroConsumptionRate` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsNegativeConsumptionRate` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsZeroGroundSpeed` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsNegativeGroundSpeed` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsNegativeDistance` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsNegativeReserveFuel` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsMissingValue` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsMissingFinalValue` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsNonNumericValue` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsPartiallyNumericValue` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsNaN` | Pass |
| | `ScenarioLoaderTest.AFRM002_RejectsInfinity` | Pass |
| **AFRM-003** | `ScenarioLoaderTest.AFRM003_RejectsMissingFile` | Pass |
| | `ScenarioLoaderTest.AFRM003_RejectsEmptyFile` | Pass |
| | `ScenarioLoaderTest.AFRM003_RejectsInvalidHeader` | Pass |
| | `ScenarioLoaderTest.AFRM003_RejectsUnknownScenario` | Pass |
| | `ScenarioLoaderTest.AFRM003_RejectsIncorrectFieldCount` | Pass |
| **AFRM-004** | `AFRM004.CalculatesFlightTime` | Pass |
| | `AFRM004.ZeroDistanceProducesZeroTime` | Pass |
| | `AFRM004.CalculatesFractionalFlightTime` | Pass |
| **AFRM-005** | `AFRM005.CalculatesJourneyFuel` | Pass |
| | `AFRM005.ZeroFlightTimeProducesZeroFuel` | Pass |
| **AFRM-006** | `AFRM006.CalculatesPositiveFuelBalance` | Pass |
| | `AFRM006.CalculatesNegativeFuelBalance` | Pass |
| | `AFRM006.CalculatesZeroFuelBalance` | Pass |
| **AFRM-007** | `AFRM007.CalculatesMaximumRange` | Pass |
| | `AFRM007.ZeroAvailableFuelProducesZeroRange` | Pass |
| | `AFRM007.CalculatesFractionalMaximumRange` | Pass |
| **AFRM-008** | `AFRM008.SufficientFuelAboveReserve` | Pass |
| | `AFRM008.SufficientFuelAtReserveBoundary` | Pass |
| | `AFRM008.ReserveShortfallBelowReserveBoundary` | Pass |
| | `AFRM008.ReserveShortfallWithZeroBalance` | Pass |
| | `AFRM008.InsufficientFuelBelowZero` | Pass |
| | `AFRM008.ZeroReserveAndZeroBalance` | Pass |
| | `AFRM008.ZeroReserveWithPositiveBalance` | Pass |
| **AFRM-009** | `AFRM009.DisplaysScenarioIdAndInputs` | Pass |
| | `AFRM009.DisplaysCalculatedResults` | Pass |
| | `AFRM009.DisplaysCorrectFuelStatus` | Pass |
| | `AFRM009.FormatsFractionalValuesToTwoDecimals` | Pass |
| **AFRM-010** | `AFRM010.UsesUnroundedValuesForCalculations` | Pass |
| | `AFRM010.RejectsNonFiniteCalculationResult` | Pass |
| | `AFRM010.UsesUnroundedBalanceForFuelStatus` | Pass |
| **AFRM-011** | `AFRM011.RejectsInvalidAircraftProfile` | Pass |
| | `AFRM011.SelectsHeavyAircraftProfile` | Pass |
| | `AFRM011.SelectsLightAircraftProfile` | Pass |
| | `AFRM011.SelectsMediumAircraftProfile` | Pass |
| **AFRM-012** | `AFRM012.CalculatesHeavyAircraftConsumption` | Pass |
| | `AFRM012.CalculatesLightAircraftConsumption` | Pass |
| | `AFRM012.CalculatesMediumAircraftConsumption` | Pass |
| **AFRM-013** | `AFRM013.CalculatesReserveAwareRange` | Pass |
| | `AFRM013.ReserveEqualToAvailableFuelProducesZeroRange` | Pass |
| | `AFRM013.ReserveExceedsAvailableFuelProducesZeroRange` | Pass |
| | `AFRM013.ZeroReserveMatchesMaximumRange` | Pass |
| **AFRM-014** | `AFRM014.AircraftProfileChangesFuelStatus` | Pass |
| | `AFRM014.DisplaysAircraftProfileAndAdjustedResults` | Pass |

**Verification summary:** 59 automated tests passed across 14 software requirements (46 baseline tests and 13 additional tests). Manual testing also confirmed that out-of-range, non-numeric and empty aircraft profile selections are rejected.