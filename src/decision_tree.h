#include <iostream>
#include "LogWrite.h"
using namespace std;

#define DEFAULT_CONFIG_FILE	"./conf/decision_tree.conf"

typedef struct _sConfig{
	string m_strSamplePath;
	string m_strInPath;
	string m_strOutPath;
	string m_strBakPath;
	string m_strLogPath;
	vector<string> m_vecFeaturesType;
	vector<string> m_vecExpectType;
}sConfig;

class DecisionTree{

public:
	DecisionTree();
	DecisionTree(string& i_strConfig);
	virtual ~DecisionTree();

public:
	int Init();
    
public:
    virtual void run() = 0;

public:
	inline void SetConfig(string& i_strConfig){m_strConfig = i_strConfig;};
	string void GetConfig(){return m_strConfig;};

private:
	string m_strConfig;


};
