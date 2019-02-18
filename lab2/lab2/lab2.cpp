#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int daysOfMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct Day {
	vector<string> affairs;
};

vector<string> Split(const string& str)
{
	vector<string> result;
	string split;
	for (int i = 0; i < str.size(); i++) {

		if (str[i] != ' ')
		{
			split += str[i];
		}
		else
		{
			if (split != "")
			{
				result.push_back(split);
				split = "";
			}
		}
	}
	if (split != "")
	{
		result.push_back(split);
	}
	return result;
}

vector<Day> GetDays(int monthIndex)
{
	vector<Day> result;
	if (monthIndex > 11)
	{
		monthIndex = 0;
	}
	for (int i = 0; i < daysOfMonths[monthIndex]; i++) {
		Day day;
		result.push_back(day);
	}
	return result;
}

void Add(string affair, int i, vector<Day>& days)
{
	days[i - 1].affairs.push_back(affair);
}

void Dump(int i, const vector<Day>& days)
{
	cout << days[i - 1].affairs.size() << " ";
	for (auto affair : days[i - 1].affairs)
	{
		cout << affair << " ";
	}
	cout << "\n";
}

void Remove(int index, string s, vector<Day>& days)
{
	for (int i = 0; i < days[index - 1].affairs.size(); i++)
	{
		if (days[index - 1].affairs[i] == s)
		{
			days.erase(days.begin() + i);
		}
	}
}

void Next(int& lastMonthIndex, vector<Day>& days)
{
	vector<Day> result = GetDays(lastMonthIndex + 1);

	//for (auto day : days) {
	for (int i = 0; i < days.size(); i++)
	{
		if (i < result.size()) {
			for (auto affear : days[i].affairs)
			{


				result[i].affairs.push_back(affear);
			}
		}
		else
		{
			for (auto affear : days[i].affairs)
			{
				result[result.size() - 1].affairs.push_back(affear);
			}
		}
	}
	days.clear();
	days = result;
	lastMonthIndex++;
}

void RunOperations(const vector<string>& operations, int& lastMonthIndex, vector<Day>& days)
{
	for (auto operation : operations) {
		vector<string> split = Split(operation);
		if (split[0] == "ADD") {
			Add(split[2], stoi(split[1]), days);
		}
		if (split[0] == "DUMP") {
			Dump(stoi(split[1]), days);
		}
		if (split[0] == "NEXT") {
			Next(lastMonthIndex, days);
		}
		if (split[0] == "REMOVE") {
			Remove(stoi(split[1]), split[2], days);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string operation("");
	int monthIndex = 0;
	vector<Day> Days = GetDays(monthIndex);
	int operationCount = 0;
	vector<string> operations;
	cout << "Введите количество операций";
	cin >> operationCount;
	cin.ignore(1, '\n');
	for (int i = 0; i < operationCount; i++) {
		getline(cin, operation);
		operations.push_back(operation);
	}
	RunOperations(operations, monthIndex, Days);
}

