#pragma once
#include <iostream>
#include "citizensList.h"
#include <fstream>

using namespace std;
namespace Elections
{
	class citizensList;
	class party
	{
	private:
		friend class elections;
		struct repToDistrict
		{
			int currReps = 0;
			int numberOfReps;
			citizensList* repList; // list of the party representatives to this district
		};
		int serial;
		char* partyName;
		const citizen& PrimeCandidate; //pointer to citizen candidates to be the Prime Minister
		repToDistrict* reps; // array of the party representatives, any cell is a different district
		int repsSize; //array logSize
	public:
		party(const char* name, const citizen& prime, int serial, int numOfDistricts);
		party(const party& p) = delete;
		~party();

		//getters
		const char* getPartyName() const { return partyName; }
		const int getSerialNum() const { return serial; }
		const citizen& getPrimeCandidate() const { return PrimeCandidate; }
		repToDistrict* getRepsPTR() const { return reps; }
		int getRepsSize() const { return repsSize; }

		bool updateNumOfReps(int disNum, int repsNum); //when we add a new party
		bool updateDistrictToParty(int disNum, int repsNum); //when we add a new district
		void printReps();
		friend ostream& operator<<(ostream& os, const party& p);

		//file
		void save(ofstream& out_file) const;
	};
}

