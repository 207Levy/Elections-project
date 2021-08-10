#pragma once
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	class district;
	class citizen
	{
	private:
		char* name;
		int ID;
		int birthYear;
		const district& dis;
		bool voted;
		bool isRep;
	public:
		citizen(const char* newName, int id, int birthYear, const district& dis);
		citizen(const citizen& person);
		~citizen() { delete[] name; }

		//getters
		const char* getName() const { return name; }
		const int getID() const { return ID; }
		const int getDistrictNum() const;
		bool isVoted() { return voted; }
		bool citizenIsRep() { return isRep; }

		//setters
		bool setVote() { return(voted = true); }
		bool setRep() { return(isRep = true); }

		friend ostream& operator<<(ostream& os, const citizen& c);

		//file
		void save(ofstream& file) const;
	};
}
