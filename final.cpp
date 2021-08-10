#include <iostream>
#include"Elections.h"
#include "final.h"

namespace Elections
{
	bool Final::updateNumOfElects(int n)
	{
		if (n < 0)
			throw invalid_argument("number of elctors is negative in district.");
		numOfElects += n;
		return true;
	}

	bool Final::updateTotalVotes(int n)
	{
		if (n < 0)
			throw invalid_argument("number of voters is negative in district.");
		totalVotes += n;
		return true;
	}
	bool Final::setParty(party* p)

	{
		par = p;
		return true;
	}

	ostream& operator<<(ostream& os, const Final& res)
	{
		party* p = res.par;
		if (p == nullptr)
			throw invalid_argument("res.par returns null");
		os << p->getPartyName() << endl << "Prime candidate: " << p->getPrimeCandidate() <<
			"Total representatives: " <<
			res.numOfElects << endl << "Total votes: " << res.totalVotes << endl; ;

		return os;
	}

	void Final::operator=(const Final& other)
	{
		par = other.par;
		numOfElects = other.numOfElects;
		totalVotes = other.totalVotes;

		delete other.par;
	}

}