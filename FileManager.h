#pragma once
#include <fstream>

using namespace std;

namespace Elections
{
	class elections;
	class FileManager
	{
	public:
		enum electinosType { NORMAL = 1, SIMPLE };

	public:
		static elections* load_elections(const char* filename);
		static bool save_elections(elections* e, const char* filename);
		static electinosType getType(const elections* e);
	};
}
