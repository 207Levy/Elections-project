#pragma once
#include "results.h"

using namespace std;

namespace Elections
{
	class Union_Results : public results
	{
	private:
		party* winParty;
	public:
		Union_Results() : results() ,winParty(nullptr) {}
		Union_Results(const Union_Results& r) = delete;
		virtual ~Union_Results() {}

		party* getWinParty() const { return winParty; }
		bool setWinParty();

		virtual void toOs(ostream& os) const;
	};
}
