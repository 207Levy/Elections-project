#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "district.h"
#include "results.h"
#include "UnionResults.h"

using namespace std;
namespace Elections
{
	district::district(const char* Name, int serial, int type, int repnum) : serial(serial), type(type),
		repNum(repnum)
	{
		
		if (type == UNION)
			res = new Union_Results();
		else
			res = new results();
		name = new char[strlen(Name) + 1];
		strcpy(name, Name);

		if (serial < 0)
		{
			delete res;
			throw invalid_argument("invalid serial number.");
		}
		if (type != UNION && type != DIVIDED)
		{
			delete res;
			throw invalid_argument("invalid District type.");
		}

	}

	district::district(ifstream& file)
	{
		int nameSize;
		file.read(rcastc(&nameSize), sizeof(int)); //number of bytes for name
		name = new char[nameSize + 1];
		file.read(rcastc(name), nameSize);	//district name
		name[nameSize] = '\0';
		file.read(rcastc(&serial), sizeof(int)); //district serial number 
		file.read(rcastc(&type), sizeof(int)); //district type (1=union, 2=diveded)
		file.read(rcastc(&repNum), sizeof(int)); //reps number
		if (type == UNION)
			res = new Union_Results();
		else
			res = new results();
		if (serial < 0)
		{
			delete res;
			throw invalid_argument("invalid serial number.");
		}
		if (type != UNION && type != DIVIDED)
		{
			delete res;
			throw invalid_argument("invalid District type.");
		}
		


	}

	district::~district() 
	{ 
		delete[] name; 
		delete res;
	}

	ostream& operator<<(ostream& os, const district& d)
	{
		os << "District's serial number: " << d.getSerial() << ", District's name: " << d.getName() <<
			"district type: ";
		if (d.getType() == UNION)
			os << "Union , ";
		else
			os << "Divided , ";
		os << "District's representative number:" << d.getRepNum() << endl;

		return os;
	}

	void district::save(ofstream& file)const
	{
		int nameSize = strlen(name);
		file.write(rcastcc(&nameSize), sizeof(int)); //number of bytes for name
		file.write(rcastcc(name), nameSize);	//district name
		file.write(rcastcc(&serial), sizeof(int)); //district serial number 
		file.write(rcastcc(&type), sizeof(int)); //district type (1=union, 2=diveded)
		file.write(rcastcc(&repNum), sizeof(int)); //reps number
	}
}