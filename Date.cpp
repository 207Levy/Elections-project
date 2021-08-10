#include "Date.h"
#include <fstream>
#include "Elections.h"

namespace Elections
{

	date::date(int d, int m, int y): day(d), month(m), year(y)
	{
		if (month < 1 || month >12)
			throw invalid_argument("invalid month.");
		if((month %2 == 1 && day > 31) || (month % 2 == 0 && day > 30) || (month == 2 && day > 28) || (day < 1))
			throw invalid_argument("invalid day.");
	}


	void date::save(ofstream& file) const 
	{
		file.write(rcastcc(&(this->day)), sizeof(int));
		file.write(rcastcc(&(this->month)), sizeof(int));
		file.write(rcastcc(&(this->year)), sizeof(int));
	}
	
	ostream& operator<<(ostream& os, const date& d) 
	{ 
		os << d.day << "." << d.month << "." << d.year << " "; return os; 
	}
}