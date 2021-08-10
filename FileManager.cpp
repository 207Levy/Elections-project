#include "FileManager.h"
#include "Elections.h"
#include "NormalElections.h"
#include "SimpleElections.h"

namespace Elections
{
	elections* FileManager::load_elections(const char* filename)
	{
		elections* e;
		ifstream file;
		file.open(filename, ios::binary);

		if (!file) {
			cout << "Error with file" << endl;
			exit(-1);
		}

		int type, d, m, y;
		file.read(rcastc(&d), sizeof(int));
		file.read(rcastc(&m), sizeof(int));
		file.read(rcastc(&y), sizeof(int));
		file.read(rcastc(&type), sizeof(int));

		if (type == SIMPLE)
		{
			int repsNum;
			file.read(rcastc(&repsNum), sizeof(int));
			e = new Simple_Elections(d, m, y, repsNum);
		}
		else
			e = new Normal_Elections(d, m, y);

		if(!file.eof())
			e->readElections(file);

		file.close();
		return e;
	}

	bool FileManager::save_elections(elections* e, const char* filename)
	{
		ofstream file(filename, ios::binary | ios::trunc);
		if (!file) {
			cout << "Error with file" << endl;
			exit(-1);
		}
		int i, n;
		
		e->getDate().save(file); //save date

		int type = static_cast<int>(FileManager::getType(e)); 
		
		file.write(rcastcc(&type), sizeof(int)); //elections type

		if (type == SIMPLE)
		{
			n = e->getDistricts()[0]->getRepNum();
			file.write(rcastcc(&n), sizeof(int));
		}
		else
			dynamic_cast<Normal_Elections*>(e)->save(file);//save districts
		
		//save citizens
		n = e->Citizens().getN();
		file.write(rcastcc(&n), sizeof(int)); //number of citizens
		listNode* curr = e->Citizens().getFirst();
		while (curr != nullptr)
		{
			curr->voter->save(file);
			curr = curr->next;
		}

		//save parties
		int partiesNum = e->getParLogSize();
		file.write(rcastcc(&partiesNum), sizeof(int)); //number of parties
		for (i = 0; i < partiesNum; i++)
			e->getParties()[i]->save(file);

		//save votes per district
		int districtsNum = e->getDisLogSize();
		file.write(rcastcc(&districtsNum), sizeof(int));
		for (i = 0; i < districtsNum; i++)
			e->getDistricts()[i]->getRes()->save(file);
		
		file.close();
		return true;
	}

	FileManager::electinosType FileManager::getType(const elections* e)
	{
		if (typeid(*e) == typeid(Normal_Elections))
			return electinosType::NORMAL;
		else 
			return electinosType::SIMPLE;
	}
}