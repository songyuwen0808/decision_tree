#include <iostream>
#include <vector>
#include <>
using namespace std;



class Tools{

public:
	Tools(){};
	~Tools(){};

public:
	static Tools& GetToolsInstance()
	{
		static Tools g_objTools;
		return g_objTools;
	}

public:
	void SplitString(const string& strSrcString, const string& strDelim, vector<std::string>& vecResult, int nSection = -1);
	void del_character(string& src, string& character);
};

