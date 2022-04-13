#include "pch.h"
#include "CppUnitTest.h"

#include "../Project 1/counting_days.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace age_in_days;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(SchikkelJaren)
		{
			Assert::AreEqual(false, schrikkeljaar(1900));
			Assert::AreEqual(false, schrikkeljaar(1877));
			Assert::AreEqual(false, schrikkeljaar(2017));
			Assert::AreEqual(false, schrikkeljaar(2021));

			Assert::AreEqual(true, schrikkeljaar(2400), L"deelbaar door 400 moet wel schikkeljaar zijn");
			Assert::AreEqual(true, schrikkeljaar(2000), L"deelbaar door 400 moet wel schikkeljaar zijn");

			Assert::AreEqual(true, schrikkeljaar(4));
			Assert::AreEqual(true, schrikkeljaar(1884));
			Assert::AreEqual(true, schrikkeljaar(1204), L"deelbaar door 4 moet schikkeljaar zijn");
		}

		TEST_METHOD(Voorgaande_Maanden)
		{
			int actual = kengetal_van(1800, 3, 3);
			Assert::AreEqual(62, actual, L"3 maart");
		}

		TEST_METHOD(Schrikkeljaar_proberen) 
		{
			int test1 = kengetal_van(2020, 3, 1);
			int test2 = kengetal_van(2020, 2, 25);
			int result = test1 - test2;
			Assert::AreEqual(5, result, L"schrikkeljaar, dus 26 27 28 29 1");
		}

		TEST_METHOD(Geen_Schrikkeljaar_proberen)
		{
			int test1 = kengetal_van(2021, 3, 1);
			int test2 = kengetal_van(2021, 2, 25);
			int result = test1 - test2;
			Assert::AreEqual(4, result, L"geen schrikkeljaar, dus 26 27 28 1");
		}
		TEST_METHOD(schikkeljaren_test)
		{
			int aantal_schikkeljaren = schikkeljaren_tot(1800);
			Assert::AreEqual(0, aantal_schikkeljaren, L"refferentie jaar is 1800");

			int aantal_schikkeljaren2 = schikkeljaren_tot(1805);
			Assert::AreEqual(1, aantal_schikkeljaren2, L"1 schikkeljaar is 1805");
		}

		TEST_METHOD(een_vol_jaar_van_365_dagen)
		{
			int datum_nu = kengetal_van(2022, 4, 22);
			int datum_geboorte = kengetal_van(2021, 4, 22);
			int result = datum_nu - datum_geboorte;
			Assert::AreEqual(365, result, L"een vol jaar");
		}
		TEST_METHOD(correct_date) 
		{
			Datum date_today{ 2022, 4, 11 };
			Datum date_birthday{ 2022, 5, 10 };
			bool result = date_today < date_birthday;
			Assert::AreEqual(true, result, L"It's in the future.");
		}

		TEST_METHOD(future_not_before_now)
		{
			Datum future{ 2401, 1, 1 };
			Datum now{ 2022, 5, 10 };
			Assert::IsFalse(future < now);
		}

		TEST_METHOD(same_date_not_before_each_other)
		{
			Datum t1{ 2022, 5, 10 };
			Assert::IsFalse(t1 < t1);
			Assert::IsFalse(t1 > t1);
		}

	};
}
