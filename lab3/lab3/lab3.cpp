#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

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

void ChangeCapital(map<string, string>& countres, string country, string newCapital)
{
	if (countres.find(country) != countres.end())
	{
		auto countryMap = countres.find(country);
		if (countryMap->second != newCapital)
		{
			cout << "Country " << countryMap->first << " has changed its capital from " << countryMap->second << " to " << newCapital << "\n";
			countres.find(country)->second = newCapital;
		}
		else
		{
			cout << "Country" << countryMap->first << "hasn't changed its capital\n";
		}
	}
	else
	{
		countres.insert(pair<string, string>(country, newCapital));
		cout << "Introduce new country " << country << " with capital " << newCapital << "\n";
	}
}

void Rename(map<string, string>& countres, string oldCountryName, string newCountryName)
{
	if (countres.find(oldCountryName) != countres.end() && countres.find(newCountryName) == countres.end() && countres.find(oldCountryName)->second != "")
	{
		cout << "Country " << oldCountryName << " with capital " << countres.find(oldCountryName)->second << " has been renamed to " << newCountryName << "\n";

		auto saveCapital = countres.find(oldCountryName)->second;
		countres.erase(oldCountryName);
		countres.insert(pair<string, string>{newCountryName, saveCapital});
	}
	else
	{
		cout << "Incorrect rename, skip\n";
	}
}

void About(const map<string, string>& countres, string countryName)
{
	if (countres.find(countryName) != countres.end())
	{
		cout << "Country " << countryName << " has capital " << countres.find(countryName)->second << "\n";
	}
	else
	{
		cout << "Country" << countryName << " doesn't exist\n";
	}
}

void Dump(const map<string, string>& countres)
{
	for (auto it = countres.begin(); it != countres.end(); ++it)
	{
		cout << it->first << "/" << it->second << "\n";
	}
}

void RunOperations(const vector<string>& operations, map<string, string>& countres)
{
	for (auto operation : operations) {
		vector<string> split = Split(operation);
		if (split[0] == "CHANGE_CAPITAL") {
			ChangeCapital(countres, split[1], split[2]);
		}
		if (split[0] == "RENAME") {
			Rename(countres, split[1], split[2]);
		}
		if (split[0] == "ABOUT") {
			About(countres, split[1]);
		}
		if (split[0] == "DUMP") {
			Dump(countres);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string operation("");
	int operationCount = 0;
	vector<string> operations;

	map<string, string> Countres;

	cout << "Введите количество операций";
	cin >> operationCount;
	cin.ignore(1, '\n');
	for (int i = 0; i < operationCount; i++) {
		getline(cin, operation);
		operations.push_back(operation);
	}

	RunOperations(operations, Countres);
}


