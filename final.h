#pragma once
#include<iostream>
#include"Elections.h"

namespace Elections
{
	class Final //keep the results by parties
	{
	private:
		party* par;
		int numOfElects = 0;
		int totalVotes = 0;
	public:
		Final() : par(nullptr) {}
		~Final() = default;

		bool updateNumOfElects(int n);
		int getNumOfElects() { return numOfElects; }
		bool updateTotalVotes(int n);
		int getTotalVotes() { return totalVotes; }
		bool setParty(party* p);
		party* getParty() { return par; }

		void Sort(int size); //sorts the parties by number of electors - high to low 
		friend ostream& operator<<(ostream& os, const Final& c);
		void operator=(const Final& other);
	};
}

