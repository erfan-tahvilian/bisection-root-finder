# Bisection Method (Serial & Parallel with OpenMP) - C++

## Overview

This project implements the **Bisection Method** for root finding using both **serial and parallel (OpenMP) approaches** in **C++**. The Bisection Method is a numerical technique for finding roots of a continuous function within a given interval. The project allows users to define functions, modify intervals, and compare results between serial and parallel computations.

## Features

- **Serial Bisection Method:** Computes the root using a standard iterative approach.
- **Parallel Bisection Method (OpenMP):** Optimized root computation using multi-threading.
- **Custom Function Input:** Users can modify the function to test different root-finding scenarios.
- **Configurable Interval & Precision:** Users can specify:
  - The number of points used in calculations.
  - The starting and ending points of the interval.
  - The acceptable calculation error.
- **Performance Comparison:** Displays computed root values from serial and parallel methods.
- **Interactive CLI Menu:** Provides an intuitive interface for testing and modifying parameters.

## Capabilities

1. **Root Calculation using the Bisection Method** - Users can compute roots for a given function within a defined interval.
2. **Parallel Execution with OpenMP** - Enables multi-threaded root computation for improved performance.
3. **Modify Function Definition** - Allows users to test different mathematical functions.
4. **Adjust Calculation Precision** - Users can set a custom error margin for root approximation.
5. **Dynamic Interval Adjustment** - The start and end values of the interval can be modified.
6. **Tabulated Output Comparison** - Results from the serial and parallel methods are displayed in a structured table.

## Installation

### Prerequisites

- **C++ Compiler with OpenMP Support** (e.g., `g++`, `clang++`)
- **Windows Operating System** (required due to Windows-specific library used)

### Build and Run

```sh
# Clone the repository
git clone https://github.com/erfan-tahvilian/bisection-root-finder.git
cd bisection-root-finder

# Compile the project (with OpenMP support)
g++ -o bisection.exe main.cpp -fopenmp -std=c++17

# Run the program
bisection.exe
```

## Usage

1. **Select an option** from the main menu:
   - `[1] Calculate Root In The Interval` → Computes the root using serial and parallel methods.
   - `[2] Change Function` → Modify the mathematical function being evaluated.
   - `[3] Change The Number of Points` → Adjust the granularity of the computation.
   - `[4] Change Start of The Interval` → Set a new starting point.
   - `[5] Change End of The Interval` → Set a new ending point.
   - `[6] Change Calculation Error` → Modify the precision of the root approximation.
   - `[7] Exit` → Close the application.
2. **If root calculation is selected (Option 1), results are displayed as:**
   - **Root Table:** Shows the computed root using both serial and parallel methods.
   - **Comparison of Serial vs. Parallel Execution:** Displays performance differences.

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.

## Support & Donations

If you find this project useful and would like to support further development, you can donate via:

- **Tron (TRX) Address:** `TL8WyZLLGu8UraHAT8dCoeMsnzGpX2oAYn`
- **Binance Coin (BNB - BEP20) Address:** `0xeC4F61F21238685cC842bC236D86684e5fc2Bc57`
- **Bitcoin (BTC) Address:** `bc1q2y9m8y02fqgsr4c6533duwmqtmrhadc8k8mkt4`

Your support is greatly appreciated! 🚀