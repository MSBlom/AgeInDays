// Project 1.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <string>
#include <windows.h>

#include <chrono>
#include <ctime>

#include "counting_days.h"

using std::cin;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;

using namespace age_in_days;

struct Person {
  string name;
  int age;

  Person(string n, int a) { // constructor (returnt impliciet void)
    name = n;
    age = a;
    if (age > 130) {
      throw std::runtime_error("Impossible age.");
    }
  }
};

Person matthijs = Person("Matthijs", 38);

Datum ask_for_date(bool allowed_to_be_past) {
  int date_today_month, date_today_day, date_today_year;

  cout << "Year: ";
  cin >> date_today_year;
  if (date_today_year > 2122 || date_today_year <= 2021) {
    throw runtime_error("Year invalid.");
  }

  cout << "Month: ";
  cin >> date_today_month;
  if (date_today_month > 12 || date_today_month <= 0) {
    throw runtime_error("ajdfkl invalid.");
  }
  cout << "Day: ";
  cin >> date_today_day;
  int month_length = days_in_month(date_today_year, date_today_month);
  if (date_today_day > month_length || date_today_day <= 0) {
    throw std::runtime_error("Day invalid.");
  }

  Datum today = {date_today_year, date_today_month, date_today_day};
  return today;
}

Datum get_today_date() {
  auto time = std::chrono::system_clock::now();
  std::time_t end_time = std::chrono::system_clock::to_time_t(time);

  tm local_tm = *localtime(&end_time);
  return {local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday};
}

int main() {
  Datum birthday{0, 0, 0};
  Datum today{0, 0, 0};

  try {
    today = get_today_date();

    cout << "What is your birthday (Y / M / D)?" << endl;
    birthday = ask_for_date(true);
  } catch (std::runtime_error the_error) {
    cout << "This is not possible." << endl;
    return 0;
  }

  int difference = difference_days(birthday, today);

  if (birthday > today) {
    cout << "This doesn't make sense." << endl;
  } else {
    cout << "You are " << difference << " days old." << endl;
  }

  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
