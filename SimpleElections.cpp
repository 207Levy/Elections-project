#include <iostream>
#include "SimpleElections.h"
#include "citizensList.h"
#include <string.h>

namespace Elections
{
	Simple_Elections::Simple_Elections(int d, int m, int y, int repsNum) : elections(d,m,y)
	{
		delete[] districts; //delete array with pySize=5 that elections ctor creates
		districts = new district * [1]; //creates an array contains 1 place
		DisLogSize = 1;
		DisPySize = 1;
		districts[0] = new district(" ", 0, DIVIDED, repsNum);
		districts[0]->citizensDis = this->Citizens();
	}

	bool Simple_Elections::addParty(const char* name, int primeID)
	{
		citizen* prime = citizens.searchByID(primeID);
		return (elections::add_Party(name, prime));
	}

	bool Simple_Elections::addRep(int ID, int partyNum)
	{
		citizen* newRep = citizens.searchByID(ID);
		return (elections::add_Elector(newRep, partyNum));
	}

	bool Simple_Elections::addCitizenToList(const char* newName, int id, int birthYear, int DisNum)
	{
		citizen* c1 = citizens.addCitizen(newName, id, birthYear, *districts[0]);
		districts[0]->getRes()->updateCitizensNum();

		return true;
	}
}

