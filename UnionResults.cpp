#include "UnionResults.h"
namespace Elections
{
	bool Union_Results::setWinParty()
	{
		int max = DisResults[0].numberOfReps;
		party* win = DisResults[0].party;
		for (int i = 1; i < logSize; ++i)
		{
			if (max < DisResults[i].numberOfReps)
			{
				max = DisResults[i].numberOfReps;
				win = DisResults[i].party;
			}
		}
		winParty = win;
		return true;
	}
	
	void Union_Results::toOs(ostream& os) const
	{
		os << "The winner Candidate in the district: " << getWinParty()->getPrimeCandidate() << endl;
	}
}