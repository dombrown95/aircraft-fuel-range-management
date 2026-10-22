# aircraft-fuel-range-management

## Overview
The Aircraft Fuel Range Management (AFRM) prototype calculates the fuel status of an aircraft for a given journey, based on available fuel, consumption rate, ground speed, distance and reserve fuel. The prototype demonstrates how fuel calculations and status classifications can support flight planning decisions.

## Functional Requirements

| ID | Requirement |
|---|---|
| AFRM-001 | The prototype shall load a scenario selected by its ID from a CSV file containing available fuel, consumption rate, ground speed, distance and reserve fuel. |
| AFRM-002 | The prototype shall reject missing, non-numeric, non-finite or out-of-range inputs, using the Inputs and Units table. |
| AFRM-003 | The prototype shall identify the cause and end without displaying calculated results or fuel status if a file, scenario or input error occurs. |
| AFRM-004 | The prototype shall calculate flight time as distance divided by ground speed. |
| AFRM-005 | The prototype shall calculate journey fuel as flight time multiplied by consumption rate. |
| AFRM-006 | The prototype shall calculate fuel balance as available fuel minus journey fuel, identifying a negative result as a fuel deficit. |
| AFRM-007 | The prototype shall calculate theoretical maximum range as available fuel divided by consumption rate, multiplied by ground speed. |
| AFRM-008 | The prototype shall assign fuel status according to the Fuel Status Rules table. |
| AFRM-009 | The prototype shall display the scenario ID, inputs, calculated results and fuel status. Fuel, distance, speed and time values shall include units and two decimal places. Maximum range shall be labelled as including reserve fuel. |
| AFRM-010 | The prototype shall use unrounded values for calculations and comparisons. If a calculation produces a non-finite result, the prototype shall report an error and end without displaying calculated results or fuel status. |

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
scenario_id,available_fuel,consumption_rate,ground_speed,journey_distance,reserve_fuel
SCN-001,1200,200,150,600,200
SCN-002,900,200,150,600,200
SCN-003,700,200,150,600,200
```

## Output Units

| Output | Unit |
|---|---|
| Flight time | hours |
| Journey fuel | kg |
| Fuel balance | kg |
| Maximum range | nautical miles |
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
- All fuel values are measured in kg, distances in nautical miles and speeds in knots.
- Maximum range is theoretical and includes reserve fuel.
- Calculations use unrounded values, with results displayed to two decimal places.

Note: The prototype is intended for demonstration and testing purposes as part of a university assignment. It is not intended for real-world flight planning.

## Building and Running
The prototype is developed using C++17 and Visual Studio 2022 with the MSVC v143 toolset.

To build locally:

Open aircraft-fuel-range-management.slnx in Visual Studio.

Select the Release and x64 configuration.

Select Build > Build Solution.

GitHub Actions automatically builds the project using MSBuild on a Windows runner when changes are pushed to main or a pull request targets main.

The workflow is defined in the .github/workflows/windows-build.yml file.

## Testing

### Running tests: 
The project uses Google Test with Visual Studio's Test Adapter for Google Test. If tests are not discovered automatically, set the discovery regex under Tools → Options → Test Adapter for Google Test → General to .*AFRM\.Tests\.exe$.

### Requirements Verification Traceability Matrix

The following matrix links each AFRM software requirement to its corresponding automated Google Tests. All 46 tests passed during local verification.

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

**Verification summary:** 46 automated tests passed across 10 software requirements.