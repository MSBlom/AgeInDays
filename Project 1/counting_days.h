#pragma once

namespace age_in_days {

	bool schrikkeljaar(int year) {
		// schikkeljaar als deelbaar door 4,
		// behalve als deelbaar door 100,
		// tenzij deelbaar door 400 (dus dan weer wel)
		if (year % 100 == 0) {
			int remainder = year % 400;
			return (year % 400 == 0);
		}
		return year % 4 == 0;
	}

	int schikkeljaren_tot(int end_year) {
		int result = 0;
		for (int year = 1800; year < end_year; year++) {
			if (schrikkeljaar(year)) {
				result++;
			}
		}
		return result;
	}

	struct Days_Result {
		bool valid;
		int days;
	};

	/// <summary>
	/// Returns the number of days in that month.
	/// </summary>
	/// <param name="year">The year</param>
	/// <param name="month">Month, indexed from 0 (jan.) to 11 (dec.)</param>
	/// <returns>Number of days in the month</returns>
	int days_in_month(int year, int month) {

		if (month < 0 || month > 11) {
			// sentinal value:
			// return -1;

			// flag in struct:
			//return {false,0};

			throw std::runtime_error("Invalid month " + month);
		}
		const int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		int schikkeldag = month == 1 && schrikkeljaar(year) ? 1 : 0;
		int result = months[month] + schikkeldag;
		return result;
	}


	int kengetal_van(int year, int month, int day) {
		// voorgaande jaren excl. schikkeljaar * 365
		int days_before_this_year = (year - 1800) * 365;
		// voorgaande schikkeljaren
		int voorgaande_jaren = schikkeljaren_tot(year);
		// voorgaande_maanden
		int voorgaande_maanden = 0;
		for (int i = 0; i < (month - 1); i++) {
			voorgaande_maanden += days_in_month(year, i);
		}
		// dag optellen
		return days_before_this_year + voorgaande_jaren + voorgaande_maanden + day;
	}


	struct Datum {
		int year;
		int month;
		int day;

		bool operator<(Datum rhs) {
			if (rhs.year > year)
				return true;

			if (rhs.year < year)
				return false;

			if (rhs.month > month)
				return true;

			if (rhs.month < month)
				return false;

			return rhs.day > day;
		}

		bool operator>(Datum rhs) {
			return rhs < *this;
		}
	};

	int difference_days(Datum geboorte_datum, Datum vandaag) {
		int kengetal_birth = kengetal_van(geboorte_datum.year, geboorte_datum.month, geboorte_datum.day);
		int kengetal_today = kengetal_van(vandaag.year, vandaag.month, vandaag.day);
		return kengetal_today - kengetal_birth;
	}

};