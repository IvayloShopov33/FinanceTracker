# Finance Tracker - Course Project #03
**Introduction to Programming Course @ FMI, Sofia University** **Winter Semester 2025/2026**

## Project Overview
This project is a terminal-based financial management system designed to help users track their incomes and expenses over a set period. It provides tools for data entry, detailed reporting, financial forecasting, and data visualization via ASCII charts.

## Author
* **Name:** Ivaylo Shopov
* **Faculty Number:** 2MI0600565
* **Compiler:** VC (Visual C++)
* **Faculty:** Faculty of Mathematics and Informatics, Sofia University

---

## Features
- **Profile Setup:** Initialize a profile with a specific number of months (1-12).
- **Transaction Management:** Add income and expense data for specific months.
- **Reporting:** Generate monthly summaries including total income, expenses, and average balance.
- **Search:** Quickly retrieve financial data for a specific month by name.
- **Sorting:** View the top 3 months based on income, expense, or balance using a descending Bubble Sort algorithm.
- **Financial Forecast:** Predict future savings and estimate when funds might run out based on current spending trends.
- **Data Visualization:** Vertical ASCII bar charts for incomes, expenses, or balance levels.

---

## Command Reference
| Command | Argument | Description |
| :--- | :--- | :--- |
| `setup` | `[months]` | Initializes the profile. |
| `add` | - | Adds income/expense for a chosen month number. |
| `report` | - | Displays the overall summary table. |
| `search` | `[MonthName]` | Shows details for a specific month (e.g., `search January`). |
| `sort` | `[type]` | Sorts top 3 by `income`, `expense`, or `balance`. |
| `forecast` | `[n]` | Predicts finances after `n` months. |
| `chart` | `[type]` | Displays an ASCII chart for the chosen type. |
| `exit` | - | Shows a final report and closes the program. |

---

## Technical Details
- **Logic:** Implemented without external STL classes (using raw arrays and standard streams) to comply with course requirements.
- **Validation:** Includes robust input validation to prevent infinite loops (using `cin.fail()`, `cin.clear()`, and `cin.ignore()`).
- **Mathematical Models:** Uses linear projection for forecasting: $S = S_0 + n \times \Delta$.
- **Code Style:** Modular architecture with functions strictly under 40 lines of code.

---

## How to Run
1. Compile the `main.cpp` file using a C++ compiler (VC++, GCC, or Clang).
2. Run the executable.
3. Start by typing `setup` to initialize your financial profile.

## License
This project ist licensed under the [MIT License](https://github.com/IvayloShopov33/FinanceTracker/blob/master/LICENSE.txt).
