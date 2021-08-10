#pragma once
#include <iostream>
#include "citizen.h"

namespace Elections
{
	struct listNode
	{
		citizen* voter;
		listNode* next = nullptr;
	};

	class citizensList
	{
		friend class elections;
	private:
		listNode* first;
		int n; //number of listNodes
	public:
		citizensList() : first(nullptr), n(0) {}
		citizensList(const citizensList& list);
		~citizensList();

		//getter
		citizen* getCitizen(int i);
		listNode* getFirst() const{ return first; }
		int getN()const { return n; }

		citizen* addCitizen(const char* newName, int id, int birthYear, district& dis);
		bool addCitizen(citizen* person);
		citizen* searchByID(int ID) const;

		friend ostream& operator<<(ostream& os, const citizensList& list);
		void operator=(const citizensList& list);
		void MakeEmpty();

	};
}
