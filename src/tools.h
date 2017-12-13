#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include "LogWrite.h"
using namespace std;

/* �������� */
#define FEATURES_TYPE_STRING	"string"
#define FEATURES_TYPE_NUM	   "num"

/* ����ֵ���� */
#define SUCCESS 0
#define FAIL	-1


typedef struct _sConfig{
	/* ���Ż������Է��� */
	int	m_nCalcType;
	/* ��֦���� */
	int	m_nPruneType;
	/* ��������·�� */
	string m_strSamplePath;
	/* ��������·�� */
	string m_strInPath;
	/* �������·�� */
	string m_strOutPath;
	/* �������ݱ���·�� */
	string m_strBakPath;
	/* log·�� */
	string m_strLogPath;
	/* ���ָ��ֶ���������, �������"FEATURES_TYPE_"��ͷ�ĺ궨�� */
	vector<string> m_vecFeaturesType;
	/* ������������ */
	vector<string> m_vecExpectType;

	_sConfig()
	{
		m_nCalcType = 0;
		m_nPruneType = 0;
		m_strSamplePath = "";
		m_strInPath = "";
		m_strOutPath = "";
		m_strBakPath = "";
		m_strLogPath = "";
		m_vecFeaturesType.clear();
		m_vecExpectType.clear();
	}
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
	}

public:
	void SplitString(const string& strSrcString, const string& strDelim, vector<std::string>& vecResult, int nSection = -1);
	void DelCharacter(string& io_strSrc, const string& i_strCharacter);
	int LoadConfig(string& i_strFilePath, sConfig& o_sConfig);
};

