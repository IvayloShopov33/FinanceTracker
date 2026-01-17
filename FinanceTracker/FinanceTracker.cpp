/**
*
* Solution to course project # 03
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Ivaylo Shopov
* @idnumber 2MI0600565
* @compiler VC
*
* The implementation of the finance tracker project that helps users manage their personal finances.
*
*/

#include <iostream>
#include <iomanip> // for std::setprecision and std::fixed

const int MONTHS_MAX_VALUE = 12;
const int MONTHS_MIN_VALUE = 1;
const int MONTH_DEFAULT_EMPTY_VALUE = 0;

const int PROFILE_INCOME_INDEX = 0;
const int PROFILE_EXPENSE_INDEX = 1;
const int PROFILE_TOTAL_INDEX = 2;

const int COMMAND_MAX_SIZE = 100;
const int COMMANDS_COUNT = 8;
const char COMMANDS[COMMANDS_COUNT][COMMAND_MAX_SIZE] = {
	"setup",
	"add",
	"report",
	"search",
	"sort",
	"forecast",
	"chart",
	"exit"
};

const int SETUP_INDEX = 0;
const int ADD_INDEX = 1;
const int REPORT_INDEX = 2;
const int SEARCH_INDEX = 3;
const int SORT_INDEX = 4;
const int FORECAST_INDEX = 5;
const int CHART_INDEX = 6;
const int EXIT_INDEX = 7;

const int INVALID_INDEX = -1;
const int PERCENTAGE_CONVERSION_FACTOR = 100;
const int IGNORE_CHARACTERS_COUNT = 1000;

const int CHART_SCALE_FACTOR = 500;
const int CHART_SCALE_10K = 10000;
const int CHART_SCALE_1K = 1000;

const int SORTING_INCOME_INDEX = 0;
const int SORTING_EXPENSE_INDEX = 1;
const int SORTING_BALANCE_INDEX = 2;
const int SORTING_TYPES_COUNT = 3;
const int SORTING_TOP_LIMIT = 3;

const char* MONTH_NAMES[MONTHS_MAX_VALUE] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

const char* MONTH_ABBREVIATIONS[MONTHS_MAX_VALUE] = {
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

const char* TYPES[SORTING_TYPES_COUNT] = {
	"income",
	"expense",
	"balance"
};

double absValue(double value) {
	return (value < 0) ? -value : value;
}

size_t stringLength(const char* str) {
	if (!str) {
		return 0;
	}

	size_t length = 0;
	while (str[length] != '\0') {
		length++;
	}

	return length;
}

bool isCharacterUppercase(char character) {
	return character >= 'A' && character <= 'Z';
}

void toLowercase(char* str) {
	if (!str) {
		return;
	}

	size_t strLength = stringLength(str);

	for (size_t i = 0; i < strLength; i++) {
		if (isCharacterUppercase(str[i])) {
			str[i] = str[i] + ('a' - 'A');
		}
	}
}

void toUppercase(char* str) {
	if (!str) {
		return;
	}

	size_t strLength = stringLength(str);

	for (size_t i = 0; i < strLength; i++) {
		if (!isCharacterUppercase(str[i])) {
			str[i] = str[i] - ('a' - 'A');
		}
	}
}

bool areStringsEqual(const char* firstString, const char* secondString) {
	if (!firstString || !secondString) {
		return false;
	}

	size_t firstStringLength = stringLength(firstString);
	size_t secondStringLength = stringLength(secondString);

	if (firstStringLength != secondStringLength) {
		return false;
	}

	for (size_t i = 0; i < firstStringLength; i++) {
		if (firstString[i] != secondString[i]) {
			return false;
		}
	}

	return true;
}

int getCommandIndex(const char* command) {
	if (!command) {
		return INVALID_INDEX;
	}

	for (int i = 0; i < COMMANDS_COUNT; i++) {
		if (areStringsEqual(command, COMMANDS[i])) {
			return i;
		}
	}

	return INVALID_INDEX;
}

void printMonthName(int monthIndex) {
	if (monthIndex < MONTHS_MIN_VALUE || monthIndex > MONTHS_MAX_VALUE) {
		std::cout << "Invalid month index." << std::endl;
		return;
	}

	std::cout << MONTH_NAMES[monthIndex - 1];
}

int parseMonthName(char* monthName) {
	if (!monthName) {
		return INVALID_INDEX;
	}

	if (!isCharacterUppercase(monthName[0])) {
		monthName[0] -= 'a' - 'A';
	}

	for (int i = 0; i < MONTHS_MAX_VALUE; i++) {
		if (areStringsEqual(monthName, MONTH_NAMES[i])) {
			return i;
		}
	}

	return INVALID_INDEX;
}

int parseSortingType(char* sortType) {
	if (!sortType) {
		return INVALID_INDEX;
	}

	for (int i = 0; i < SORTING_TYPES_COUNT; i++) {
		if (areStringsEqual(sortType, TYPES[i])) {
			return i;
		}
	}

	return INVALID_INDEX;
}

void swap(int& firstValue, int& secondValue) {
	firstValue += secondValue;
	secondValue = firstValue - secondValue;
	firstValue -= secondValue;
}

double getValueByType(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int monthIndex, int sortingTypeIndex) {
	switch (sortingTypeIndex) {
		case SORTING_INCOME_INDEX:
			return profileData[PROFILE_INCOME_INDEX][monthIndex];
		case SORTING_EXPENSE_INDEX:
			return profileData[PROFILE_EXPENSE_INDEX][monthIndex];
		case SORTING_BALANCE_INDEX:
			return profileData[PROFILE_INCOME_INDEX][monthIndex] - profileData[PROFILE_EXPENSE_INDEX][monthIndex];
		default:
			return 0;
	}
}

void sortMonthIndices(int indicesOfMonths[MONTHS_MAX_VALUE], 
						int monthsCount, 
						double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], 
						int typeIndex) {
	for (int i = 0; i < monthsCount - 1; i++) {
		for (int j = 0; j < monthsCount - i - 1; j++) {
			double firstValue = getValueByType(profileData, indicesOfMonths[j], typeIndex);
			double secondValue = getValueByType(profileData, indicesOfMonths[j + 1], typeIndex);

			if (firstValue < secondValue) {
				swap(indicesOfMonths[j], indicesOfMonths[j + 1]);
			}
		}
	}
}

bool isInputInvalid() {
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(IGNORE_CHARACTERS_COUNT, '\n');
		std::cout << "Error: Please enter a valid number." << std::endl;

		return true;
	}

	return false;
}

bool isProfileNotCreated(bool isProfileSetup) {
	if (!isProfileSetup) {
		std::cout << "The profile is not created yet. Use 'setup' first." << std::endl;
		return true;
	}

	return false;
}

void setupProfile(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int& profileMonths, bool& isProfileSetup) {
	std::cout << "Enter number of months: ";
	std::cin >> profileMonths;

	if (isInputInvalid()) {
		return;
	}

	if (profileMonths < MONTHS_MIN_VALUE || profileMonths > MONTHS_MAX_VALUE) {
		std::cout << "Invalid number of months for profile setup. It must be a number between " 
			<< MONTHS_MIN_VALUE << " and " << MONTHS_MAX_VALUE << "." << std::endl;
		return;
	}

	for (int month = 0; month < profileMonths; month++) {
		profileData[PROFILE_INCOME_INDEX][month] = MONTH_DEFAULT_EMPTY_VALUE;
		profileData[PROFILE_EXPENSE_INDEX][month] = MONTH_DEFAULT_EMPTY_VALUE;
	}

	std::cout << "Profile created successfully." << std::endl;
	isProfileSetup = true;
}

void addFinanceData(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup) {
	if (isProfileNotCreated(isProfileSetup)) {
		return;
	}

	int month = 0;
	std::cout << "Enter month number (1-" << profileMonths << "): ";
	std::cin >> month;

	if (isInputInvalid()) {
		return;
	}

	if (month < MONTHS_MIN_VALUE || month > profileMonths) {
		std::cout << "Invalid month number. Please enter a value between " 
			<< MONTHS_MIN_VALUE << " and " << profileMonths << "." << std::endl;
		return;
	}

	if (profileData[PROFILE_INCOME_INDEX][month - 1] != MONTH_DEFAULT_EMPTY_VALUE || 
		profileData[PROFILE_EXPENSE_INDEX][month - 1] != MONTH_DEFAULT_EMPTY_VALUE) {
		std::cout << "[Note: Adding to existing data for ";
		printMonthName(month);
		std::cout << "]" << std::endl;
	}

	double income = 0, expense = 0;

	std::cout << "Enter income: ";
	std::cin >> income;

	if (isInputInvalid()) {
		return;
	}

	std::cout << "Enter expense: ";
	std::cin >> expense;

	if (isInputInvalid()) {
		return;
	}

	profileData[PROFILE_INCOME_INDEX][month - 1] += income;
	profileData[PROFILE_EXPENSE_INDEX][month - 1] += expense;

	double balance = profileData[PROFILE_INCOME_INDEX][month - 1] - profileData[PROFILE_EXPENSE_INDEX][month - 1];

	std::cout << "Balance for ";
	printMonthName(month);
	std::cout << ": " << (balance > 0 ? "+" : "") << std::fixed << std::setprecision(2) << balance << std::endl;
}

void monthlyReport(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup) {
	if (isProfileNotCreated(isProfileSetup)) {
		return;
	}

	std::cout << "Month | Income | Expense | Balance " << std::endl;
	std::cout << "---------------------------------- " << std::endl;

	double totalIncome = 0;
	double totalExpenses = 0;
	int activeMonths = 0;

	for (int month = 0; month < profileMonths; month++) {
		if (profileData[PROFILE_INCOME_INDEX][month] != MONTH_DEFAULT_EMPTY_VALUE || 
			profileData[PROFILE_EXPENSE_INDEX][month] != MONTH_DEFAULT_EMPTY_VALUE) {
			double income = profileData[PROFILE_INCOME_INDEX][month];
			double expense = profileData[PROFILE_EXPENSE_INDEX][month];
			double balance = income - expense;

			std::cout << MONTH_ABBREVIATIONS[month] << " | " << std::fixed << std::setprecision(2) << income << " | ";
			std::cout << std::fixed << std::setprecision(2) << expense << " | ";
			std::cout << (balance > 0 ? "+" : "") << std::fixed << std::setprecision(2) << balance << std::endl;

			totalIncome += income;
			totalExpenses += expense;
			activeMonths++;
		}
	}

	std::cout << "---------------------------------- " << std::endl;

	std::cout << "Total income: " << std::fixed << std::setprecision(2) << totalIncome << std::endl;
	std::cout << "Total expense: " << std::fixed << std::setprecision(2) << totalExpenses << std::endl;

	if (activeMonths > 0) {
		double averageBalance = (totalIncome - totalExpenses) / activeMonths;
		std::cout << "Average Balance: " << (averageBalance > 0 ? "+" : "") 
			<< std::fixed << std::setprecision(2) << averageBalance << std::endl;
	}
	else {
		std::cout << "Average Balance: 0.00 (No active months)" << std::endl;
	}
}

void searchByMonth(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup, char* targetMonth) {
	if (!targetMonth) {
		std::cout << "Invalid month input." << std::endl;
		return;
	}

	if (isProfileNotCreated(isProfileSetup)) {
		return;
	}

	toLowercase(targetMonth);
	int monthIndex = parseMonthName(targetMonth);

	if (monthIndex == INVALID_INDEX || monthIndex >= profileMonths) {
		std::cout << "Month not found in the profile." << std::endl;
		return;
	}

	double monthIncome = profileData[PROFILE_INCOME_INDEX][monthIndex];
	double monthExpense = profileData[PROFILE_EXPENSE_INDEX][monthIndex];

	std::cout << "Income: " << std::fixed << std::setprecision(2) << monthIncome << std::endl;
	std::cout << "Expense: " << std::fixed << std::setprecision(2) << monthExpense << std::endl;

	double balance = monthIncome - monthExpense;
	std::cout << "Balance: " << (balance > 0 ? "+" : "") << std::fixed << std::setprecision(2) << balance << std::endl;

	if (monthIncome != MONTH_DEFAULT_EMPTY_VALUE) {
		double expenseRatio = (monthExpense / monthIncome) * PERCENTAGE_CONVERSION_FACTOR;
		std::cout << "Expense Ratio: " << std::fixed << std::setprecision(1) << expenseRatio << "%" << std::endl;
	}
	else {
		std::cout << "Expense Ratio: N/A (No income recorded)" << std::endl;
	}
}

void sortByType(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup, char* sortType) {
	if (!sortType) {
		std::cout << "Invalid sorting type input." << std::endl;
		return;
	}

	if (isProfileNotCreated(isProfileSetup)) {
		return;
	}

	toLowercase(sortType);
	int sortingTypeIndex = parseSortingType(sortType);

	if (sortingTypeIndex == INVALID_INDEX) {
		std::cout << "Invalid sorting type. Please use sorting type between 'income', 'expense', 'balance'." << std::endl;
		return;
	}

	int indicesOfMonths[MONTHS_MAX_VALUE] = { 0 };
	for (int i = 0; i < profileMonths; i++) {
		indicesOfMonths[i] = i;
	}

	// Bubble sort - sorting in descending order
	sortMonthIndices(indicesOfMonths, profileMonths, profileData, sortingTypeIndex);

	int sortingLimit = (profileMonths < SORTING_TOP_LIMIT) ? profileMonths : SORTING_TOP_LIMIT;
	std::cout << "Top " << sortingLimit << " months by " << sortType << ":" << std::endl;

	for (int i = 0; i < sortingLimit; i++) {
		double sortedValue = getValueByType(profileData, indicesOfMonths[i], sortingTypeIndex);
		std::cout << i + 1 << ". " << MONTH_ABBREVIATIONS[indicesOfMonths[i]] << ": " << (sortedValue > 0 ? "+" : "") 
			<< std::fixed << std::setprecision(2) << sortedValue << std::endl;
	}
}

void forecastSavings(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup, int monthsAhead) {
	if (isProfileNotCreated(isProfileSetup)) {
		return;
	}

	double totalSavings = 0;
	int activeMonths = 0;

	for (int i = 0; i < profileMonths; i++) {
		double currentMonthIncome = profileData[PROFILE_INCOME_INDEX][i];
		double currentMonthExpense = profileData[PROFILE_EXPENSE_INDEX][i];

		if (currentMonthIncome != MONTH_DEFAULT_EMPTY_VALUE || currentMonthExpense != MONTH_DEFAULT_EMPTY_VALUE) {
			totalSavings += (currentMonthIncome - currentMonthExpense);
			activeMonths++;
		}		
	}

	if (activeMonths == 0) {
		std::cout << "No data available to perform a forecast." << std::endl;
		return;
	}

	double averageMonthlyChange = totalSavings / activeMonths;
	std::cout << "Current total savings: " << std::fixed << std::setprecision(2) << totalSavings << std::endl;
	std::cout << "Average monthly change: " << (averageMonthlyChange > 0 ? "+" : "") 
		<< std::fixed << std::setprecision(2) << averageMonthlyChange << std::endl;

	if (averageMonthlyChange >= 0) {
		double predictedSavings = totalSavings + monthsAhead * averageMonthlyChange;
		std::cout << "Predicted savings after " << monthsAhead << " months: " 
			<< std::fixed << std::setprecision(2) << predictedSavings << std::endl;
	}
	else {
		if (totalSavings <= 0) {
			std::cout << "Expected to run out of money after 0 months (already out of money)." << std::endl;
		}
		else {
			averageMonthlyChange = absValue(averageMonthlyChange);
			int monthsUntilReachingZero = (int)(totalSavings / averageMonthlyChange);

			std::cout << "Expected to run out of money after " << monthsUntilReachingZero << " months." << std::endl;
		}
	}
}

void validateMonthsInputAndCallForecast(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], 
											int profileMonths, 
											bool isProfileSetup, 
											int monthsAhead) {
	if (isInputInvalid()) {
		return;
	}

	if (monthsAhead < 0) {
		std::cout << "Error: Months ahead cannot be a negative number." << std::endl;
	}
	else {
		forecastSavings(profileData, profileMonths, isProfileSetup, monthsAhead);
	}
}

int getMaxValueForChart(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, int typeIndex) {
	if (profileMonths <= 0) {
		return 0;
	}

	int maxValue = (int)getValueByType(profileData, 0, typeIndex);

	for (int i = 1; i < profileMonths; i++) {
		double currentValue = getValueByType(profileData, i, typeIndex);

		if (currentValue > maxValue) {
			maxValue = (int)currentValue;
		}
	}

	return maxValue;
}

void printChartAxisMonths(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths) {
	for (int month = 0; month < profileMonths; month++) {
		if (profileData[PROFILE_INCOME_INDEX][month] != MONTH_DEFAULT_EMPTY_VALUE || 
			profileData[PROFILE_EXPENSE_INDEX][month] != MONTH_DEFAULT_EMPTY_VALUE) {
			std::cout << MONTH_ABBREVIATIONS[month] << " ";
		}
	}

	std::cout << std::endl;
}

void drawFinanceChart(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup, char* chartType) {
	if (!chartType) {
		std::cout << "Invalid chart type input." << std::endl;
		return;
	}

	if (isProfileNotCreated(isProfileSetup)) {
		return;
	}

	toLowercase(chartType);
	int chartTypeIndex = parseSortingType(chartType);

	if (chartTypeIndex == INVALID_INDEX) {
		std::cout << "Invalid chart type. Please use chart type between 'income', 'expense' or 'balance'." << std::endl;
		return;
	}

	int maxValue = getMaxValueForChart(profileData, profileMonths, chartTypeIndex);
	toUppercase(chartType);

	std::cout << "=== YEARLY FINANCIAL " << chartType << " CHART === " << std::endl;
	std::cout << "    | " << std::endl;

	for (int chartLevel = maxValue; chartLevel > 0; chartLevel -= CHART_SCALE_FACTOR) {
		if (chartLevel < CHART_SCALE_10K) std::cout << " ";
		if (chartLevel < CHART_SCALE_1K) std::cout << " ";
		std::cout << chartLevel << " | ";

		for (int month = 0; month < profileMonths; month++) {
			double monthValue = getValueByType(profileData, month, chartTypeIndex);
			if (monthValue >= chartLevel) {
				std::cout << "#   ";
			}
			else {
				std::cout << "    ";
			}
		}

		std::cout << std::endl;
	}

	std::cout << "    --------------------------- " << std::endl;
	std::cout << "     ";

	printChartAxisMonths(profileData, profileMonths);
}

void handleCommand(int commandIndex, double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int& profileMonths, bool& isProfileSetup) {
	switch (commandIndex) {
		case SETUP_INDEX:
			setupProfile(profileData, profileMonths, isProfileSetup);
			break;
		case ADD_INDEX:
			addFinanceData(profileData, profileMonths, isProfileSetup);
			break;
		case REPORT_INDEX:
			monthlyReport(profileData, profileMonths, isProfileSetup);
			break;
		case SEARCH_INDEX: {
			char targetMonth[COMMAND_MAX_SIZE];
			std::cin >> targetMonth;
			searchByMonth(profileData, profileMonths, isProfileSetup, targetMonth);
			break;
		}
		case SORT_INDEX: {
			char sortType[COMMAND_MAX_SIZE];
			std::cin >> sortType;
			sortByType(profileData, profileMonths, isProfileSetup, sortType);
			break;
		}
		case FORECAST_INDEX: {
			int monthsAhead = 0;
			std::cin >> monthsAhead;
			validateMonthsInputAndCallForecast(profileData, profileMonths, isProfileSetup, monthsAhead);
			break;
		}
		case CHART_INDEX: {
			char chartType[COMMAND_MAX_SIZE];
			std::cin >> chartType;
			drawFinanceChart(profileData, profileMonths, isProfileSetup, chartType);
			break;
		}
		default:
			std::cout << "Invalid command. Please try again." << std::endl;
			break;
	}
}

void executeFinanceTracker() {
	int profileMonths = 0;
	bool isProfileSetup = false;
	double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE] = { 0 };

	char command[COMMAND_MAX_SIZE];
	std::cin >> command;

	while (true) {
		toLowercase(command);
		int commandIndex = getCommandIndex(command);

		if (commandIndex == EXIT_INDEX) {
			monthlyReport(profileData, profileMonths, isProfileSetup);
			return;
		}

		if (isProfileSetup && commandIndex == SETUP_INDEX) {
			std::cout << "The profile has already been set." << std::endl;
			std::cin >> command;
			continue;
		}

		handleCommand(commandIndex, profileData, profileMonths, isProfileSetup);
		std::cin >> command;
	}
}

int main() {
	executeFinanceTracker();

	return 0;
}