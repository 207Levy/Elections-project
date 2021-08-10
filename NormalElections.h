#pragma once
#include "district.h"
#include "party.h"
#include "citizensList.h"
#include "Elections.h"
#include "final.h"

namespace Elections
{
	class citizensList;
	class Normal_Elections : public elections
	{
		friend class citizensList;
	private:
		Final* finalResults; //array of results. any cell is a party
		
	public:
		Normal_Elections(int d, int m, int y);
		Normal_Elections(const Normal_Elections& e) = delete;
		~Normal_Elections();

		//getter
		Final* getFinalArr() const { return finalResults; }
	
		bool addDistrict(char* Name, int repnum, int type);
		virtual bool addParty(const char* name, int primeID) override;
		bool addRep(int ID, int partyNum, int districtNum);
		virtual bool addCitizenToList(const char* newName, int id, int birthYear, int DisNum = 0) override;

		void setWinToDistricts(); //set party win only to uniun districts
		void makeFinalResults();
		bool setFinal(Final* res); //Calculats the final results
		void showFinalResult();
		void SortFinalResults(Final* res, int size);

		//file
		void save(ofstream& file) const;
		void readDistricts(ifstream& file); //read any district from file
	};
}

