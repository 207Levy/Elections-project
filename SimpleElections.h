#pragma once
#include "district.h"
#include "party.h"
#include "citizensList.h"
#include "final.h"

namespace Elections
{
	class citizensList;
	class Simple_Elections : public elections
	{
	public:
		Simple_Elections(int d, int m, int y, int repsNum);
		Simple_Elections(const Simple_Elections& e) = delete;
		~Simple_Elections() {}

		virtual bool addParty(const char* name, int primeID) override;
		bool addRep(int ID, int partyNum);
		virtual bool addCitizenToList(const char* newName, int id, int birthYear, int DisNum = 0) override;
		virtual citizensList& Citizens() override { return citizens; }

	};
}

