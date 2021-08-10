#include   <iostream>
#include "results.h"
#include "UnionResults.h"
using namespace std;
namespace Elections
{

	results::results() : citizensNumber(0), votersNumber(0), DisResults(nullptr), pySize(5), logSize(0)
	{
		DisResults = new partyRes[pySize];
		for (int i = 0; i < pySize; ++i)
		{
			DisResults[i].party = nullptr;
			DisResults[i].numberOfVotes = 0;
			DisResults[i].repsList = new citizensList();
		}
	}

	results::~results()
	{
		delete[] DisResults;
	}

	bool results::setParty(party* p)
	{
		int serial = p->getSerialNum();
		DisResults[serial].party = p;
		logSize++;
		if (pySize == logSize)
		{
			pySize *= 2;
			partyRes* newArr = new partyRes[pySize];
			for (int i = 0; i < pySize; i++)
			{
				newArr[i].numberOfReps = DisResults[i].numberOfReps;
				newArr[i].numberOfVotes = DisResults[i].numberOfVotes;
				newArr[i].party = DisResults[i].party;
				newArr[i].preVoters = DisResults[i].preVoters;
				newArr[i].repsList = DisResults[i].repsList;
			}
			delete[] DisResults;
			this->DisResults = newArr;
		}
		return true;
	}
	void results::addVoter(int partyNum)
	{
		if (partyNum > logSize)
			throw invalid_argument("error, no such party");
		DisResults[partyNum].numberOfVotes++;
		votersNumber++;
	}

	bool results::setPercentage() //set voters percentages for any party in the district
	{
		for (int i = 0; i < logSize; i++)
		{
			DisResults[i].preVoters = (static_cast<float>(DisResults[i].numberOfVotes / static_cast<float>(votersNumber)) * 100);
		}
		return true;
	}

	float results::getPercentage() const //total percentage for the district
	{
		float res = (static_cast<float>(votersNumber) / static_cast<float>(citizensNumber)) * 100;
		return res;
	}

	int results::getRepsNum(int partyNum)
	{
		if (partyNum > logSize)
			throw invalid_argument("error, no such party");
		return (DisResults[partyNum].numberOfReps);
	}

	void results::setNumReps(int repsNum)
	{
		int i;
		for (i = 0; i < logSize; ++i)
		{
			float TempNumOfReps = ((DisResults[i].preVoters) * repsNum) / 100;
			int numOfReps = static_cast<int>(TempNumOfReps);
			if ((TempNumOfReps - numOfReps) >= 0.5)
				numOfReps += 1; //if the number after point is big - add 1 to repsNum

			DisResults[i].numberOfReps = numOfReps;
		}
	}

	void results::addRepToList(int partyNum, citizen* rep)
	{
		if (partyNum > logSize)
			throw invalid_argument("error, no such party");
		DisResults[partyNum].repsList->addCitizen(rep);
	}

	ostream& operator<<(ostream& os, const results& res)
	{
		os << "precentage of voters: " << res.getPercentage() << "%" << endl << endl;
		res.toOs(os);

		for (int i = 0; i < res.logSize; ++i)
		{
			os << "party number : " << i << endl << endl
				<< "Representatives list:" << endl << *(res.DisResults[i].repsList)
				<< "number of voters: " << res.DisResults[i].numberOfVotes << endl
				<< "precentage of voters: " << res.DisResults[i].preVoters << "%" << endl << endl;
		}

		return os;
	}

	void results::Sort(int size)
	{

		int max = 0;
		for (int i = 0; i < size - 1; i++)
		{
			if (DisResults[i].numberOfReps < DisResults[i + 1].numberOfReps)
			{
				partyRes temp = DisResults[i];
				DisResults[i] = DisResults[i + 1];
				DisResults[i + 1] = temp;
			}
		}
	}

	void results::toOs(ostream& os) const
	{
		os << "Candidates by electors: " << endl;
		for (int i = 0; i < logSize; ++i)
		{
			os << "Candidate: " << DisResults[i].party->getPrimeCandidate() << endl
				<< "Number of Representatives: " << DisResults[i].numberOfReps << endl << endl;
		}
	}

	void results::save(ofstream& file) const
	{
		file.write(rcastcc(&votersNumber), sizeof(int)); //number of voters in the district
		file.write(rcastcc(&logSize), sizeof(int)); //number of parties 
		for (int i = 0; i < logSize; i++) //for any party
		{
			file.write(rcastcc(&(DisResults[i].numberOfVotes)), sizeof(int)); //number of citizens votes to this party
		}
	}

	void results::load(ifstream& file)
	{
		int partiesSize, serial;
		file.read(rcastc(&votersNumber), sizeof(int));	//number of voters in the district

		file.read(rcastc(&partiesSize), sizeof(int)); //number of parties 
		for (int i = 0; i < partiesSize; i++) //for any party
		{
			file.read(rcastc(&(DisResults[i].numberOfVotes)), sizeof(int));
		}
	}
}