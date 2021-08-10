#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "citizen.h"
#include "district.h"

namespace Elections
{
	citizen::citizen(const char* newName, int id, int birthYear, const district& dis) : ID(id), birthYear(birthYear),
		dis(const_cast<district&>(dis)), voted(false), isRep(false)
	{
		name = new char[strlen(newName) + 1];
		strcpy(name, newName);
		if ((/*/electionsYear*/-birthYear<18)) // if person is not 18+ 
			throw  invalid_argument("Invalid , person is under 18.");
		if (id / 100000000 == 0 || id / 100000000 > 9)
			throw  invalid_argument("Invalid , person's id is not 9 figures.");
		
	}

	citizen::citizen(const citizen& person) : name(new char[strlen(person.name) + 1]), ID(person.ID), birthYear(person.birthYear),
		dis(const_cast<district&>(dis)), voted(person.voted)
	{
		strcpy(name, person.name);
	}

	const int citizen::getDistrictNum() const
	{
		return (dis.getSerial());
	}

	ostream& operator<<(ostream& os, const citizen& person)
	{
		os << person.getName() << ", ID: " << person.ID << ", year of birth: " << person.birthYear << ", district number: "
			<< person.getDistrictNum() << endl;
		return os;
	}

	void citizen::save(ofstream& file) const
	{
		int nameSize = strlen(name);
		file.write(rcastcc(&nameSize), sizeof(int)); //number of bytes for name
		file.write(rcastcc(name), nameSize);	//citizen's name
		file.write(rcastcc(&birthYear), sizeof(int));
		file.write(rcastcc(&ID), sizeof(int)); 
		
		int districtNum = dis.getSerial();
		file.write(rcastcc(&districtNum), sizeof(int)); 

		int isVote = static_cast<int>(voted);
		int is_Rep = static_cast<int>(isRep);
		file.write(rcastcc(&isVote), sizeof(int));
		file.write(rcastcc(&is_Rep), sizeof(int));
	}
}