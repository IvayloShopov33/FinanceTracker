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

const int MONTHS = 12;

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

size_t stringLength(const char* str)
{
	if (!str)
	{
		return 0;
	}

	size_t length = 0;
	while (str[length] != '\0')
	{
		length++;
	}

	return length;
}

bool isCharacterUppercase(char character)
{
	return character >= 'A' && character <= 'Z';
}

void toLowercase(char* str)
{
	if (!str)
	{
		return;
	}

	size_t strLength = stringLength(str);

	for (int i = 0; i < strLength; i++)
	{
		if (isCharacterUppercase(str[i]))
		{
			str[i] = str[i] + ('a' - 'A');
		}
	}
}

bool areStringsEqual(const char* firstString, const char* secondString)
{
	if (!firstString || !secondString)
	{
		return false;
	}

	size_t firstStringLength = stringLength(firstString);
	size_t secondStringLength = stringLength(secondString);

	if (firstStringLength != secondStringLength)
	{
		return false;
	}

	for (int i = 0; i < firstStringLength; i++)
	{
		if (firstString[i] != secondString[i])
		{
			return false;
		}
	}

	return true;
}

int getCommandIndex(const char* command)
{
	if (!command)
	{
		return -1;
	}

	for (int i = 0; i < COMMANDS_COUNT; i++)
	{
		if (areStringsEqual(command, COMMANDS[i]))
		{
			return i;
		}
	}

	return -1;
}

void executeFinanceTracker()
{
	int profileMonths = 0;
	double profileData[PROFILE_TOTAL_INDEX][MONTHS] = { 0 };

	char command[COMMAND_MAX_SIZE];
	std::cin.getline(command, COMMAND_MAX_SIZE, '\n');

	while (true)
	{
		toLowercase(command);
		int commandIndex = getCommandIndex(command);

		switch (commandIndex)
		{
			case EXIT_INDEX:
				return;
			case SETUP_INDEX:
				break;
			case ADD_INDEX:
				break;
			case REPORT_INDEX:
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

		std::cin.getline(command, COMMAND_MAX_SIZE, '\n');
	}
}

int main()
{
	executeFinanceTracker();

	return 0;
}