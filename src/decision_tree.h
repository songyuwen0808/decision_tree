#include <iostream>
#include "tools.h"
#include "LogWrite.h"
using namespace std;

#define DEFAULT_CONFIG_FILE	"./conf/decision_tree.conf"

class DecisionTree{

public:
	DecisionTree();
	DecisionTree(string& i_strConfig);
	virtual ~DecisionTree();

public:
	int Init();
	
public:
	virtual void run(){};

public:
	inline void SetConfig(string& i_strConfig){m_strConfig = i_strConfig;};

private:
	string m_strConfig;


};
