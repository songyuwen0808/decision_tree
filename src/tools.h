#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include "LogWrite.h"
using namespace std;

/* 特征类型 */
#define FEATURES_TYPE_STRING	"string"
#define FEATURES_TYPE_NUM	   "num"

/* 返回值类型 */
#define SUCCESS 0
#define FAIL	-1


typedef struct _sConfig{
	/* 最优划分属性方法 */
	int	m_nCalcType;
	/* 剪枝类型 */
	int	m_nPruneType;
	/* 样本数据路径 */
	string m_strSamplePath;
	/* 输入数据路径 */
	string m_strInPath;
	/* 输出数据路径 */
	string m_strOutPath;
	/* 输入数据备份路径 */
	string m_strBakPath;
	/* log路径 */
	string m_strLogPath;
	/* 特种各字段数据类型, 具体参照"FEATURES_TYPE_"开头的宏定义 */
	vector<string> m_vecFeaturesType;
	/* 期望的输出结果 */
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

