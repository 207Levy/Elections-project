#pragma once


namespace Elections
{

	const char* menu[] = { "Add District", "Add Citizen", "Add Party", "Add Candidate", "Show districts", "Show citizens",
								"Show Parties", "Vote", "Show Elections Results", "Exit", "Save elections to file",
								"Load elections from file" };

	const char* firstMenu[] = { "Create New Elections Round", "Load Elections Round", "Exit" };

	class Menu
	{
	public:
		enum eMenu {
			Add_District = 1, Add_Citizen, Add_Party, Add_Candidate, Show_Districts,
			Show_Citizens, Show_Parties, Vote, Show_Results, Exit, Save, Load
		};

		enum eFirstMenu {
			New = 1, load, Exit_Program
		};

	public:
		static void showMenu();
		static void showFirst_Menu();
	};


	void Menu::showMenu()
	{
		cout << "please chose an option from the menu:" << endl;
		cout << eMenu::Add_District << "\t to: " << menu[eMenu::Add_District - 1] << endl
			<< eMenu::Add_Citizen << "\t to: " << menu[eMenu::Add_Citizen - 1] << endl
			<< eMenu::Add_Party << "\t to: " << menu[eMenu::Add_Party - 1] << endl
			<< eMenu::Add_Candidate << "\t to: " << menu[eMenu::Add_Candidate - 1] << endl
			<< eMenu::Show_Districts << "\t to: " << menu[eMenu::Show_Districts - 1] << endl
			<< eMenu::Show_Citizens << "\t to: " << menu[eMenu::Show_Citizens - 1] << endl
			<< eMenu::Show_Parties << "\t to: " << menu[eMenu::Show_Parties - 1] << endl
			<< eMenu::Vote << "\t to: " << menu[eMenu::Vote - 1] << endl
			<< eMenu::Show_Results << "\t to: " << menu[eMenu::Show_Results - 1] << endl
			<< eMenu::Exit << "\t to: " << menu[eMenu::Exit - 1] << endl
			<< eMenu::Save << "\t to: " << menu[eMenu::Save - 1] << endl
			<< eMenu::Load << "\t to: " << menu[eMenu::Load - 1] << endl;
	}
	void Menu:: showFirst_Menu()
	{
		cout << "please chose an option from the menu:" << endl;
		cout << eFirstMenu::New << "\t to: " << firstMenu[eFirstMenu::New - 1] << endl
			<< eFirstMenu::load << "\t to: " << firstMenu[eFirstMenu::load - 1] << endl
			<< eFirstMenu::Exit_Program << "\t to: " << firstMenu[eFirstMenu::Exit_Program - 1] << endl;
	}
}
