# aircraft-fuel-range-management

## Overview
The Aircraft Fuel Range Management (AFRM) prototype calculates the fuel status of an aircraft for a given journey, based on available fuel, consumption rate, ground speed, distance and reserve fuel. The prototype demonstrates how fuel calculations and status classifications can support flight planning decisions.

## Functional Requirements

| ID | Requirement |
|---|---|
| AFRM-001 | The prototype shall load a selected CSV scenario containing available fuel, consumption rate, ground speed, distance and reserve fuel. |
| AFRM-002 | The prototype shall reject missing, non-numeric, non-finite or out-of-range inputs, using the Inputs and Units table. |
| AFRM-003 | The prototype shall identify the cause and end without displaying calculated results or fuel status if a file, scenario or input error occurs. |
| AFRM-004 | The prototype shall calculate flight time as distance divided by ground speed. |
| AFRM-005 | The prototype shall calculate journey fuel as flight time multiplied by consumption rate. |
| AFRM-006 | The prototype shall calculate fuel balance as available fuel minus journey fuel, identifying a negative result as a fuel deficit. |
| AFRM-007 | The prototype shall calculate theoretical maximum range as available fuel divided by consumption rate, multiplied by ground speed. |
| AFRM-008 | The prototype shall assign fuel status according to the Fuel Status Rules table. |
| AFRM-009 | The prototype shall display the scenario ID, inputs, calculated results and fuel status. Numerical values shall include units and two decimal places. Maximum range shall be labelled as including reserve fuel. |
| AFRM-010 | The prototype shall use unrounded values for calculations and comparisons. Non-finite calculation results shall produce an error and end processing without displaying results or fuel status. |

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

Running tests: The project uses Google Test with Visual Studio's Test Adapter for Google Test. If tests are not discovered automatically, set the discovery regex under Tools → Options → Test Adapter for Google Test → General to .*AFRM\.Tests\.exe$.