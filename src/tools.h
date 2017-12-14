#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include "LogWrite.h"
using namespace std;

/* features type */
#define FEATURES_TYPE_STRING    "string"
#define FEATURES_TYPE_NUM       "num"
#define FEATURES_TYPE_MILTI     "multi"

/* return type */
#define SUCCESS 0
#define FAIL	-1

#define FEATURE_NAME_MAX_LEN    64


typedef struct _sConfig{
	int	m_nCalcType;
	int	m_nPruneType;
	string m_strSamplePath;
	string m_strInPath;
	string m_strOutPath;
	string m_strBakPath;
	vector<string> m_vecFeaturesType;
	vector<string> m_vecFeaturesName;

	_sConfig()
	{
		m_nCalcType = 0;
		m_nPruneType = 0;
		m_strSamplePath = "";
		m_strInPath = "";
		m_strOutPath = "";
		m_strBakPath = "";
		m_vecFeaturesType.clear();
		m_vecFeaturesName.clear();
	};
    
    int CheckParam()
    {
        return !(m_strSamplePath.length() * m_strInPath.length() * m_strOutPath.length() * m_strBakPath.length() * m_vecFeaturesType.size() * m_vecFeaturesName.size());
    };
}sConfig;


class Tools{

public:
	Tools(){};
	~Tools(){};

public:
	static Tools& GetToolsInstance()
	{
		static Tools g_objTools;
		return g_objTools;
	};

public:
	void SplitString(const string& strSrcString, const string& strDelim, vector<std::string>& vecResult, int nSection = -1);
	void DelCharacter(string& io_strSrc, const string& i_strCharacter);
	int LoadConfig(string& i_strFilePath, sConfig& o_sConfig);
};

#endif
