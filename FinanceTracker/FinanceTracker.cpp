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

	for (int i = 0; i < strLength; i++) {
		if (isCharacterUppercase(str[i])) {
			str[i] = str[i] + ('a' - 'A');
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

	for (int i = 0; i < firstStringLength; i++) {
		if (firstString[i] != secondString[i]) {
			return false;
		}
	}

	return true;
}

int getCommandIndex(const char* command) {
	if (!command) {
		return -1;
	}

	for (int i = 0; i < COMMANDS_COUNT; i++) {
		if (areStringsEqual(command, COMMANDS[i])) {
			return i;
		}
	}

	return -1;
}

void printMonthName(int monthIndex) {
	if (monthIndex < MONTHS_MIN_VALUE || monthIndex > MONTHS_MAX_VALUE) {
		std::cout << "Invalid month index." << std::endl;
		return;
	}

	std::cout << MONTH_NAMES[monthIndex - 1];
}

void setupProfile(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int& profileMonths, bool& isProfileSetup) {
	std::cout << "Enter number of months: ";
	std::cin >> profileMonths;

	if (profileMonths < MONTHS_MIN_VALUE || profileMonths > MONTHS_MAX_VALUE) {
		std::cout << "Invalid number of months for profile setup. It must be a number between " << MONTHS_MIN_VALUE << " and " << MONTHS_MAX_VALUE << "." << std::endl;
		return;
	}

	for (size_t month = 0; month < profileMonths; month++) {
		profileData[PROFILE_INCOME_INDEX][month] = 0;
		profileData[PROFILE_EXPENSE_INDEX][month] = 0;
	}

	std::cout << "Profile created successfully." << std::endl;
	isProfileSetup = true;
}

void addFinanceData(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup) {
	if (!isProfileSetup) {
		std::cout << "The profile is not created yet. Use 'setup' first." << std::endl;
		return;
	}

	int month = 0;
	std::cout << "Enter month number (1-" << profileMonths << "): ";
	std::cin >> month;

	if (month < MONTHS_MIN_VALUE || month > profileMonths) {
		std::cout << "Invalid month number. Please enter a value between " << MONTHS_MIN_VALUE << " and " << profileMonths << "." << std::endl;
		return;
	}

	int income = 0, expense = 0;

	std::cout << "Enter income: ";
	std::cin >> income;
	std::cout << "Enter expense: ";
	std::cin >> expense;

	profileData[PROFILE_INCOME_INDEX][month - 1] += income;
	profileData[PROFILE_EXPENSE_INDEX][month - 1] += expense;

	double balance = profileData[PROFILE_INCOME_INDEX][month - 1] - profileData[PROFILE_EXPENSE_INDEX][month - 1];

	std::cout << "Balance for ";
	printMonthName(month);
	std::cout << ": " << (balance > 0 ? "+" : "") << balance << std::endl;
}

void monthlyReport(double profileData[PROFILE_TOTAL_INDEX][MONTHS_MAX_VALUE], int profileMonths, bool isProfileSetup) {
	if (!isProfileSetup) {
		std::cout << "The profile is not created yet. Use 'setup' first." << std::endl;
		return;
	}

	std::cout << "Month | Income | Expense | Balance " << std::endl;
	std::cout << "---------------------------------- " << std::endl;

	double totalIncome = 0;
	double totalExpenses = 0;
	int activeMonths = 0;

	for (int month = 0; month < profileMonths; month++) {
		if (profileData[PROFILE_INCOME_INDEX][month] != 0 || profileData[PROFILE_EXPENSE_INDEX][month] != 0) {
			double income = profileData[PROFILE_INCOME_INDEX][month];
			double expense = profileData[PROFILE_EXPENSE_INDEX][month];
			double balance = income - expense;
			std::cout << MONTH_ABBREVIATIONS[month] << " | " << std::fixed << std::setprecision(2) << income << " | " << std::fixed << std::setprecision(2) << expense << " | " << (balance > 0 ? "+" : "") << std::fixed << std::setprecision(2) << balance << std::endl;

			totalIncome += income;
			totalExpenses += expense;
			activeMonths++;
		}
	}

	std::cout << "---------------------------------- " << std::endl;

	std::cout << "Total income: " << std::fixed << std::setprecision(2) << totalIncome << std::endl;
	std::cout << "Total expense: " << std::fixed << std::setprecision(2) << totalExpenses << std::endl;

	double averageBalance = (totalIncome - totalExpenses) / activeMonths;
	std::cout << "Average Balance: " << (averageBalance > 0 ? "+" : "") << std::fixed << std::setprecision(2) << averageBalance << std::endl;
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

		if (isProfileSetup && commandIndex == SETUP_INDEX) {
			std::cout << "The profile has already been set." << std::endl;
			std::cin >> command;
			continue;
		}

		switch (commandIndex) {
			case EXIT_INDEX:
				return;
			case SETUP_INDEX:
				setupProfile(profileData, profileMonths, isProfileSetup);
				break;
			case ADD_INDEX:
				addFinanceData(profileData, profileMonths, isProfileSetup);
				break;
			case REPORT_INDEX:
				monthlyReport(profileData, profileMonths, isProfileSetup);
				break;
			case SEARCH_INDEX:
				break;
			case SORT_INDEX:
				break;
			case FORECAST_INDEX:
				break;
			case CHART_INDEX:
				break;
			default:
				std::cout << "Invalid command. Please try again." << std::endl;
				break;
		}

		std::cin >> command;
	}
}

int main() {
	executeFinanceTracker();

	return 0;
}