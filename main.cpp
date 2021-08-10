#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "NormalElections.h"
#include "SimpleElections.h"
#include <cstring>
#include "menu.h"

using namespace std;
using namespace Elections;

const int MAX_SIZE = 150;

void addDistrictMenu(elections* e)
{
	char name[MAX_SIZE];
	int type, Repnum;
	cout << "please enter District name:" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "please enter the type of the district (union = 1, diveded=2) and the number of representatives:" << endl;
	cin >> type >> Repnum;
	if (Repnum < 0)
	{
		cout << "wrong input!" << endl;
	}
	else
	{
		dynamic_cast<Normal_Elections*>(e)->addDistrict(name, Repnum, type);
		cout << "District added successfully" << endl;
	}
}

void addCitizenMenu(elections* e)
{
	char name[MAX_SIZE];
	int id, year, district = 0;
	cout << "Please enter name:" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Please enter id, year of birth and district number:" << endl;
	cin >> id >> year >> district;
	if (e->Citizens().searchByID(id) != nullptr)
	{
		cout << "This citizen is already exist" << endl;
	}
	else if (typeid(*e) == typeid(Normal_Elections))
	{
		if (district >= e->getDisLogSize() || district < 0)
		{
			cout << "There is no such district" << endl;
		}
		else
		{
			e->addCitizenToList(name, id, year, district);
			cout << "Citizen added successfully" << endl;
		}
	}
	else //Simple elections
	{
		e->addCitizenToList(name, id, year);
		cout << "Citizen added successfully" << endl;
	}
}

void addPartyMenu(elections* e)
{
	char name[MAX_SIZE];
	int id;
	cout << "Please enter the party name:" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Please enter the prime minister candidate ID:" << endl;
	cin >> id;
	if (e->Citizens().searchByID(id) == nullptr)
	{
		cout << "There is no such citizen for your prime minister cohise" << endl;
	}
	else
	{
		e->addParty(name, id);
		cout << "party added successfully" << endl;
	}
}

void addRepMenu(elections* e)
{
	int id, districtNum, partyNum;
	cout << "Please enter representative ID, the number of party and the number of district:" << endl;
	cin >> id >> partyNum >> districtNum;;
	if (typeid(*e) == typeid(Simple_Elections))
		districtNum = 0;

	else if (e->getDisLogSize() < districtNum + 1 || districtNum < 0)
	{
		cout << "There is no such district" << endl;
	}

	if (e->getParLogSize() < partyNum + 1 || partyNum < 0)
	{
		cout << "There is no such party" << endl;
	}
	else if (e->getParties()[partyNum]->getRepsPTR()[districtNum].currReps == e->getParties()[partyNum]->getRepsPTR()[districtNum].numberOfReps)
	{
		cout << "The representatives list is full" << endl;
	}
	else
	{
		if (typeid(*e) == typeid(Normal_Elections))
			dynamic_cast<Normal_Elections*>(e)->addRep(id, partyNum, districtNum);
		else
			dynamic_cast<Simple_Elections*>(e)->addRep(id, partyNum);
		cout << "The representative added successfully" << endl;
	}
}

void voteMenu(elections* e)
{
	int id, partyNum;
	citizen* voter;
	cout << "Please write your ID and the number of the party you're voting for:" << endl;
	cin >> id >> partyNum;

	voter = e->Citizens().searchByID(id);

	if (voter == nullptr)
	{
		cout << "There is no such citizen with this ID" << endl;
	}
	else if (voter->isVoted())
	{
		cout << "You already voted!" << endl;
	}
	else if (partyNum >= e->getParLogSize() || partyNum < 0)
	{
		cout << "There is no such party" << endl;
	}
	else
	{
		e->vote(*voter, partyNum);
		cout << "Your vote has been picked up!" << endl;
	}
}

void showResultsMenu(elections* e)
{
	if (e->preResults())
	{
		if (typeid(e) == typeid(Normal_Elections))
		{
			dynamic_cast<Normal_Elections*>(e)->makeFinalResults();
		}

		e->showResults(); //results by district
		if (typeid(e) == typeid(Normal_Elections))
		{
			dynamic_cast<Normal_Elections*>(e)->showFinalResult();
		}
	}
	
}

elections* LoadElectionsMenu()
{
	char name[MAX_SIZE];
	cout << "please write the name of the file" << endl;
	cin >> name;
	elections* e = FileManager::load_elections(name);
	if (e != nullptr)
		cout << "the file loaded successfully!" << endl;
	return e;
}

void SaveElectionMenu(elections* e)
{
	char name[MAX_SIZE];
	cout << "please write the name of the file" << endl;
	cin >> name;
	FileManager::save_elections(e, name);
	cout << "the file saved successfully!" << endl;

}


void chooseFromMenu(int op, elections** e)
{
	switch (op)
	{
	case(1):
		if (typeid(**e) == typeid(Simple_Elections))
			cout << "adding district in simple elections is not allowed!" << endl;
		else
			addDistrictMenu(*e);
		break;
	case(2):
		addCitizenMenu(*e);
		break;
	case(3):
		addPartyMenu(*e);
		break;
	case(4):
		addRepMenu(*e);
		break;
	case(5):
		(*e)->printDistricts();
		break;
	case(6):
		cout << (*e)->Citizens() << endl;
		break;
	case(7):
		(*e)->printParties();
		break;
	case(8):
		voteMenu(*e);
		break;
	case(9):
		showResultsMenu(*e);
		break;
	case(10):
		break;
	case(11):
		SaveElectionMenu(*e);
		break;
	case(12):
		delete (*e);
		(*e) = LoadElectionsMenu();
		break;
	default:
		cout << "wrong input!" << endl << "please try again.." << endl;
		break;
	}
	system("pause");
	system("CLS");
}

void chooseFromFirstMenu(int op, elections** e)
{
	int d, m, y, repsNum;
	while (op < 1 || op > 3)
	{
		cout << "wrong input! please try again:" << endl;
		cin >> op;
	}
	if (op == 1)
	{
		int type;
		cout << "please enter 1 for simple elections or 2 for normal" << endl;
		cin >> type;
		cout << "please enter electios date(day(1-31) -> month(1-12) -> year): " << endl;
		cin >> d >> m >> y;
		if (type == 1)
		{
			cout << "please enter the number of representitives" << endl;
			cin >> repsNum;
			*e = new Simple_Elections(d, m, y, repsNum);

		}
		else
			*e = new Normal_Elections(d, m, y);
	}
	else if (op == 2)
	{
		*e = LoadElectionsMenu();
	}
	
	else if (op == 3)
		std::exit(1);
}

int main()
{
	int op = 0;
	bool flag = true;
	elections* e = nullptr;
	
	while (flag)
	{
		try {
			Menu::showFirst_Menu();
			cin >> op;
			chooseFromFirstMenu(op, &e);
			flag = false;
		}
		catch (std::exception& ex) {
			system("CLS");
			cout << "Error: " << ex.what() << endl;
			cout << "Please try again" << endl;
			flag = true;
		}


	}
	
	
	system("CLS");

	cout << "WELCOME TO ELECTIONS " << e->getDate() << endl;
	
	while (op != 10)
	{
		try {
			Menu::showMenu();
			cin >> op;
			system("CLS");
			chooseFromMenu(op, &e);
		} 
		catch (std::exception& ex) {
			cout << "Error: " << ex.what() << endl;
			cout << "Please try again" << endl;
		}
	}

	cout << "The elections ended... goodBye." << endl;
	system("pause");
}