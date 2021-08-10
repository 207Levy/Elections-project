
#include <iostream>
#include "citizen.h"
#include "citizensList.h"

namespace Elections {

	citizen* citizensList::addCitizen(const char* newName, int id, int birthYear, district& dis)
	{
		citizen* p1 = new citizen(newName, id, birthYear, dis);
		addCitizen(p1);
		n += 1;
		return p1;
	}

	bool citizensList::addCitizen(citizen* person)
	{
		listNode* newNode = new listNode();
		newNode->voter = person;
		newNode->next = nullptr;

		listNode* curr = first;

		if (curr == nullptr) //if its the first one
		{
			first = newNode;
			first->next = nullptr;
			return true;
		}
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr->next = newNode;
		curr->next->next = nullptr;
		return true;
	}

	citizensList::~citizensList()
	{
		listNode* curr = first;
		if (first != nullptr)
		{
			listNode* next = curr->next;
			while (curr != nullptr)
			{

				delete curr;
				curr = next;
				if (next != nullptr)
					next = next->next;
			}
		}
	
		first = nullptr;
	}

	citizensList::citizensList(const citizensList& list) : first(list.first), n(list.n) {}

	citizen* citizensList::searchByID(int ID) const
	{
		listNode* curr = first;

		while (curr != nullptr)
		{
			if (curr->voter->getID() == ID)
			{
				return curr->voter;
			}
			else
				curr = curr->next;
		}
		//if we did not find this ID-
		return nullptr;
	}

	ostream& operator<<(ostream& os, const citizensList& list)
	{
		listNode* curr = list.first;
		if (curr == nullptr)
			os << "There are no citizens." << endl;
		else
		{
			while (curr != nullptr)
			{
				os << *(curr->voter);
				curr = curr->next;
			}
		}
		return os;
	}

	citizen* citizensList::getCitizen(int i)
	{
		listNode* curr = first;
		for (int ind = 0; ind < i; ++ind)
		{
			curr = curr->next;
		}
		return curr->voter;
	}

	void citizensList::operator=(const citizensList& list)
	{
		first = list.first;
		n = list.n;
	}


	void citizensList::MakeEmpty()
	{
		n = 0;
		first = nullptr;
	}
}