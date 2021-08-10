#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "party.h"
#include "citizensList.h"

using namespace std;
namespace Elections
{
	party::party(const char* name, const citizen& prime, int serial, int numOfDistricts)
		: serial(serial), PrimeCandidate(prime), repsSize(numOfDistricts)
	{
		partyName = new char[strlen(name) + 1]; //set party name
		strcpy(partyName, name);
		if (numOfDistricts >= 0)
		{
			reps = new repToDistrict[numOfDistricts];
			for (int i = 0; i < numOfDistricts; ++i)
			{
				reps[i].repList = new citizensList();
				reps[i].numberOfReps = 0;
			}
		}
		else
			throw invalid_argument("invalid Rep Size.");

		
	}

	party::~party()
	{
		delete[] partyName;
		delete[] reps;
	}

	bool party::updateDistrictToParty(int disNum, int repsNum)
	{
		if (repsSize <= disNum)
		{
			repsSize = disNum + 1;
			repToDistrict* newArr = new repToDistrict[repsSize];
			for (int i = 0; i < repsSize; i++)
			{
				newArr[i] = reps[i];
			}
			delete[] reps;
			this->reps = newArr;

			updateNumOfReps(disNum, repsNum);
			reps[disNum].repList = new citizensList();
		}
		return true;
	}

	bool party::updateNumOfReps(int disNum, int repsNum)
	{
		if (disNum < 0)
			throw out_of_range("invalid range at updateNumOfReps. ");
		reps[disNum].numberOfReps = repsNum;
		return true;
	}

	ostream& operator<<(ostream& os, const party& p)
	{
		os << "Party's serial number: " << p.serial << ", Party's name " << p.partyName << endl
			<< "Party's prime minister candidate: " << p.PrimeCandidate << endl;
		return os;
	}

	void party::printReps()
	{
		cout << "REPRESENTATIVES LIST:" << endl;
		for (int i = 0; i < repsSize; ++i)
		{
			cout << "District number: " << i << endl;
			cout << "Representatives: " << endl << *(reps[i].repList) << endl;
		}
	}

	void party::save(ofstream& file) const
	{

		int nameSize = strlen(partyName);
		file.write(rcastcc(&nameSize), sizeof(int)); //number of bytes for name
		file.write(rcastcc(partyName), nameSize);	//party name
		file.write(rcastcc(&serial), sizeof(int)); //party serial number 

		int primeID = PrimeCandidate.getID();
		file.write(rcastcc(&primeID), sizeof(int));
		file.write(rcastcc(&repsSize), sizeof(int)); //districts number (to array)
		for (int i = 0; i < repsSize; i++) //for any district
		{
			file.write(rcastcc(&(reps[i].numberOfReps)), sizeof(int)); 
			listNode* curr = reps->repList->getFirst();
			while(curr != nullptr)
			{
				int repID = curr->voter->getID();
				file.write(rcastcc(&repID), sizeof(int));
				curr = curr->next;
			}
		}
	}
}