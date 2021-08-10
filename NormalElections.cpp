#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "NormalElections.h"
#include "citizensList.h"
#include <string.h>
#include <typeinfo>
#include "UnionResults.h"


namespace Elections
{
	Normal_Elections::Normal_Elections(int d, int m, int y) : elections(d, m, y), finalResults(nullptr) {}

	Normal_Elections::~Normal_Elections()
	{
		delete[] finalResults;
	}

	bool Normal_Elections::addDistrict(char* Name, int repnum, int type)
	{
		district* d1 = new district(Name, DisLogSize, type, repnum);
		districts[DisLogSize] = d1;
		DisLogSize++;

		if (DisLogSize == DisPySize)
		{
			DisPySize *= 2;
			district** newArr = new district * [DisPySize];
			for (int i = 0; i < DisPySize; i++)
			{
				newArr[i] = districts[i];
			}
			delete[] districts;
			this->districts = newArr;
		}
		for (int i = 0; i < ParLogSize; ++i)
		{
			parties[i]->updateDistrictToParty(DisLogSize - 1, districts[DisLogSize - 1]->getRepNum());
		}
		return true;
	}

	bool Normal_Elections::addParty(const char* name, int primeID)
	{
		citizen* prime = citizens.searchByID(primeID);
		return(elections::add_Party(name, prime));
	}

	bool Normal_Elections::addRep(int ID, int partyNum, int districtNum)
	{
		citizen* newRep = citizens.searchByID(ID);
		return (add_Elector(newRep, partyNum, districtNum));
	}

	bool Normal_Elections::addCitizenToList(const char* newName, int id, int birthYear, int DisNum)
	{
		district* dis = districts[DisNum];
		citizen* c1 = citizens.addCitizen(newName, id, birthYear, *dis);
		districts[DisNum]->citizensDis.addCitizen(c1);
		districts[DisNum]->getRes()->updateCitizensNum();

		return true;
	}

	void Normal_Elections::setWinToDistricts()
	{
		for (int i = 0; i < DisLogSize; ++i)
		{
			results* disRes = districts[i]->getRes();
			if (districts[i]->getType() == UNION)
			{
				Union_Results* disURes = dynamic_cast<Union_Results*>(disRes);
				disURes->setWinParty();
			}
		}
	}

	void Normal_Elections::makeFinalResults()
	{
		if (finalResults != nullptr) //if we need to make a new one
		{
			delete[] finalResults;
			finalResults = nullptr;
		}

		int numOfPar = ParLogSize;
		Final* res = new Final[numOfPar];
		for (int i = 0; i < numOfPar; i++)
		{
			res[i].setParty(parties[i]);
			for (int j = 0; j < DisLogSize; j++)
			{
				results* DisRes = districts[j]->getRes();
				int n = DisRes->getDisResults()[i].numberOfVotes;
				res[i].updateTotalVotes(n);
				if (districts[j]->getType() == DIVIDED)
				{
					int numOfelects = DisRes->getDisResults()[i].numberOfReps;
					res[i].updateNumOfElects(numOfelects);
				}
				else if (parties[i] == dynamic_cast<Union_Results*>(DisRes)->getWinParty());
				{
					int numOfelects = districts[j]->getRepNum();
					res[i].updateNumOfElects(numOfelects);
				}
			}
		}

		SortFinalResults(res, numOfPar);
		setFinal(res);
	}
	
	void Normal_Elections::SortFinalResults(Final* res, int size)
	{
		int max = 0;
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size - i - 1; i++)
			{
				if (res[j].getNumOfElects() < res[j + 1].getNumOfElects())
				{
					Final temp = res[j];
					res[j] = res[j + 1];
					res[j + 1] = temp;
				}
			}
		}
	}

	void Normal_Elections::showFinalResult()
	{
		int numOfPar = ParLogSize;
		Final* res = finalResults;
		cout << endl << "FINAL RESULTS:   " << endl << endl;
		for (int i = 0; i < numOfPar; i++)
		{
			cout << res[i] << endl << endl;
		}
	}

	bool Normal_Elections::setFinal(Final* res)
	{
		finalResults = res;
		return true;
	}

	void Normal_Elections::save(ofstream& file) const
	{
		file.write(rcastcc(&DisLogSize), sizeof(int)); //number of districts
		for (int i = 0; i < DisLogSize; i++)
		{
			districts[i]->save(file);
		}
	}

	void Normal_Elections::readDistricts(ifstream& file)//read any district from file
	{
		file.read(rcastc(&DisLogSize), sizeof(int)); //number of districts
		
		for (int i = 0; i < DisLogSize; i++)
			districts[i] = new district(file);
	}
}

