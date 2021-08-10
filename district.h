#pragma once
#include "citizensList.h"
#include "results.h"
#include <fstream>

#define UNION 1
#define DIVIDED 2

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	class district
	{
	private:
		char* name;
		int serial;
		int type; //UNION / DIVIDED
		int repNum; //number of Representatives for this district
		int Percentage = 0; //votes Percentage
		results* res; //district's results
	public:
		citizensList citizensDis; //list of the citizens that allowed to vote in this district

		district(const char* Name, int serial, int type, int repnum);
		district(const district& dis) = delete;
		district(ifstream& file);
		~district();

		//getters
		const char* getName() const { return name; }
		const int getSerial() const { return serial; }
		int getType() const { return type; }
		const int getRepNum() const { return repNum; }
		results* getRes() { return res; }

		//setters
		bool setPercentage() { Percentage = res->getPercentage(); return true; }

		friend ostream& operator<<(ostream& os, const district& d);

		//file
		void save(ofstream& file)const;
	};

}

