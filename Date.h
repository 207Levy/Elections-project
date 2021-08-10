#pragma once
#include <iostream>

using namespace std;

namespace Elections
{
	class date
	{
	private:
		int day;
		int month;
		int year;
	public:
		date() : day(0), month(0), year(0) {}
		date(int d, int m, int y);
		date(const date& other) : day(other.day), month(other.month), year(other.year) {}
		~date() {}
		
		//getters
		int getDay() const{ return day; }
		int getMonth() const{ return month; }
		int getYear() const{ return year; }

		friend ostream& operator<<(ostream& os, const date& d);

		//file
		void save(ofstream& file) const;
	};
}
