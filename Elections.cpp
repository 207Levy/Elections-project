#include "Elections.h"
#include "NormalElections.h"
#include "SimpleElections.h"
#include <typeinfo>

namespace Elections
{
	elections::elections(int d, int m, int y) : ParPySize(5), ParLogSize(0), DisLogSize(0), DisPySize(1), Date(d, m, y)
	{
		districts = new district * [ParPySize];
		parties = new party * [ParPySize];
	}

	elections::~elections()
	{
		for (int i = 0; i < ParLogSize; ++i)
		{
			delete (parties[i]);
		}
		delete[] parties;

		for (int i = 0; i < DisLogSize; ++i)
		{
			delete (districts[i]);
		}
		delete[] districts;
	}

	bool elections::add_Party(const char* name, citizen* prime)
	{
		party* p1 = new party(name, *prime, ParLogSize, DisLogSize);
		parties[ParLogSize] = p1;
		ParLogSize++;

		if (ParLogSize == ParPySize)
		{
			ParPySize *= 2;
			party** newArr = new party * [ParPySize];
			for (int i = 0; i < ParPySize; i++)
			{
				newArr[i] = parties[i];
			}
			delete[] parties;
			this->parties = newArr;
		}

		party* par = parties[ParLogSize - 1];
		for (int i = 0; i < DisLogSize; ++i)
		{
			par->updateNumOfReps(i, districts[i]->getRepNum());
			districts[i]->getRes()->setParty(par);
		}
		return true;
	}

	void elections::printParties()
	{
		for (int i = 0; i < ParLogSize; i++)
		{
			cout << *(parties[i]);
			parties[i]->printReps();
			cout << endl;
		}
	}

	void elections::printDistricts()
	{
		for (int i = 0; i < DisLogSize; i++)
			cout << *(districts[i]) << endl;
	}

	bool elections::add_Elector(citizen* newRep, int partyNum, int districtNum)
	{
		if (newRep == nullptr)
		{
			cout << "There is no such citizen with this ID" << endl;
			return false;
		}
		else if (newRep->citizenIsRep())
		{
			cout << "This citizen is already a representative" << endl;
			return false;
		}
		else
		{
			parties[partyNum]->getRepsPTR()[districtNum].repList->addCitizen(newRep);
			parties[partyNum]->getRepsPTR()[districtNum].currReps++;
			newRep->setRep();
			return true;
		}
	}

	bool elections::vote(citizen& voter, int partyNum)
	{
		voter.setVote();
		int disNum = voter.getDistrictNum();
		districts[disNum]->getRes()->addVoter(partyNum); //add vote to results array

		return true;
	}

	bool elections::preResults()
	{
		//check if the electors lists are full
		for (int p = 0; p < ParLogSize; ++p)
		{
			for (int d = 0; d < parties[p]->getRepsSize(); ++d)
			{
				if (parties[p]->getRepsPTR()[d].currReps < parties[p]->getRepsPTR()[d].numberOfReps)
				{
					cout << "Electors List for party " << p << " to district " << d << " is not full." << endl;
					return false;
				}
			}
		}
		if (ParLogSize == 0)
			return false;
		if (DisLogSize == 0)
			return false;
		//else - we can calculates the results
		setPre();
		setRepsToParties();
		if (typeid(*this) == typeid(Normal_Elections))
			dynamic_cast<Normal_Elections*>(this)->setWinToDistricts();
		return true;
						
	}

	void elections::setPre()
	{
		for (int i = 0; i < DisLogSize; ++i)
		{
			districts[i]->getRes()->setPercentage();
		}
	}

	bool elections::setRepsToParties()
	{
		for (int i = 0; i < DisLogSize; i++)
		{
			districts[i]->getRes()->setNumReps(districts[i]->getRepNum()); //sents the repsNum to res in order to calculates the number of reps after votes
		}
		for (int p = 0; p < ParLogSize; ++p)
		{
			for (int d = 0; d < DisLogSize; ++d)
			{
				int repsNum = districts[d]->getRes()->getRepsNum(p);
				districts[d]->getRes()->getDisResults()[p].repsList->MakeEmpty();

				for (int r = 0; r < repsNum; ++r)
				{
					citizen* rep = parties[p]->getRepsPTR()[d].repList->getCitizen(r);
					districts[d]->getRes()->addRepToList(p, rep);
				}
			}
		}
		return true;
	}

	void elections::showResults()
	{
		cout << "RESULTS FOR " << Date << "ELECTIONS:" << endl << endl;
		if (typeid(*this) == typeid(Normal_Elections))
		{
			cout << "DISTRICTS RESULTS:" << endl << endl;
			for (int i = 0; i < DisLogSize; ++i)
			{
				cout << districts[i]->getName();
				if (districts[i]->getType() == UNION)
					cout << " (Union) ";

				else
				{
					districts[i]->getRes()->Sort(ParLogSize);
					cout << " (Diveded) ";
				}
				cout << "district results: " << endl;
				cout << *(districts[i]->getRes());
			}
		}
		else
		{
			cout << endl << "FINAL RESULTS:   " << endl << endl;
			districts[0]->getRes()->Sort(ParLogSize);
			cout << *(districts[0]->getRes());
		}
	}

	void elections::Readparty(ifstream& file)
	{
		int nameSize, srl, repsize;
		file.read(rcastc(&nameSize), sizeof(int)); //number of bytes for name
		char* name = new char[nameSize + 1];
		file.read(rcastc(name), nameSize);	//party name
		name[nameSize] = '\0';
		file.read(rcastc(&srl), sizeof(int)); //party serial number 

		int primeID;
		file.read(rcastc(&primeID), sizeof(int));
		citizen* PrimeCandidate = Citizens().searchByID(primeID);
		file.read(rcastc(&repsize), sizeof(int)); //districts number (to array)


		add_Party(name, PrimeCandidate);

		for (int i = 0; i < repsize; i++) //for any district
		{
			file.read(rcastc(&(parties[srl]->reps[i].numberOfReps)), sizeof(int));
			parties[srl]->reps[i].currReps = parties[srl]->reps[i].numberOfReps;

			for (int j = 0; j < parties[srl]->reps[i].numberOfReps; j++)
			{
				int repID;
				file.read(rcastc(&repID), sizeof(int));
				citizen* p = Citizens().searchByID(repID);
				parties[srl]->reps[i].repList->addCitizen(p);
			}
		}
	}

	void elections::readCitizen(ifstream& file)
	{
		int namelen, brth, id, disnum;
		char* name;
		file.read(rcastc(&namelen), sizeof(int));
		name = new char[namelen + 1];
		file.read(name, namelen);
		name[namelen] = '\0';
		file.read(rcastc(&brth), sizeof(int));
		file.read(rcastc(&id), sizeof(int));
		file.read(rcastc(&disnum), sizeof(int));

		addCitizenToList(name, id, brth, disnum);
		citizen* p = Citizens().searchByID(id);

		int isVote;
		int is_Rep;
		file.read(rcastc(&isVote), sizeof(int));
		file.read(rcastc(&is_Rep), sizeof(int));

		if (isVote)
			p->setVote();
		if (is_Rep)
			p->setRep();
	}

	void elections::readElections(ifstream& file) //to check: after any read - if the file is over
	{
		int districtType, TotalPar, TotalCitizens, number_of_districts;

		if (typeid(*this) == typeid(Normal_Elections))
		{
			dynamic_cast<Normal_Elections*>(this)->readDistricts(file);
		}
		
		file.read(rcastc(&TotalCitizens), sizeof(int));
		if (!file.eof())
		{
			for (int i = 0; i < TotalCitizens; i++)
				readCitizen(file);
		}
	
		file.read(rcastc(&TotalPar), sizeof(int));
		for (int i = 0; i < TotalPar; i++)
		{
			Readparty(file);
		}

		if (!file.eof()) //load votes per district
		{
			file.read(rcastc(&number_of_districts), sizeof(int));
			for (int i = 0; i < number_of_districts; i++)
			{
				districts[i]->getRes()->load(file);
			}
		}
	}
}
