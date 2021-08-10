#pragma once
#include "district.h"
#include "party.h"
#include "citizensList.h"
#include <typeinfo>
#include "FileManager.h"
#include "Date.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	class citizensList;

	class elections
	{
	protected:
		date Date;
		party** parties; //array of pointers to all the parties
		district** districts; //array of pointers to all the districts
		int ParPySize, ParLogSize, DisPySize, DisLogSize;
		citizensList citizens; //voters book
	public:
		elections(int d, int m, int y);
		elections(const elections& e) = delete;
		virtual ~elections();

		//getters
		int getParLogSize() const { return ParLogSize; }
		party** getParties() const { return parties; }
		const date& getDate() const { return Date; }
		int getDisLogSize() const { return DisLogSize; }
		district** getDistricts() const { return districts; }
		virtual citizensList& Citizens() { return citizens; }

		bool add_Party(const char* name, citizen* prime);
		virtual bool addParty(const char* name, int id) = 0; //abstract
		bool add_Elector(citizen* newRep, int partyNum, int districtNum = 0);
		virtual bool addCitizenToList(const char* newName, int id, int birthYear, int DisNum = 0) = 0; //abstract

		void printParties();
		void printDistricts();

		bool vote(citizen&, int partyNum);
		
		bool preResults(); //Calculats the results to any district
		void setPre(); //set percentages to any party in all the districts
		bool setRepsToParties();
		void showResults(); //districts results

		//file
		void readCitizen(ifstream& file);
		void Readparty(ifstream& file);
		void readElections(ifstream& file);
	};
}


