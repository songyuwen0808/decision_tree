#ifndef __DECISION_TREE_H__
#define __DECISION_TREE_H__

#include <iostream>
#include "tools.h"
#include "LogWrite.h"
using namespace std;

#define DEFAULT_CONFIG_FILE	"./conf/decision_tree.conf"

typedef vector<string> FEATURE;
typedef vector<FEATURE> SAMPLE;

typedef struct _sTreeStruct{
	string					m_strSplitName;
	string					m_strLabel;
	bool					b_isLeaf;
	vector<string>			m_vecChildrenFeatures;
	vector<_sTreeStruct>	m_vecChildren;
}sTreeStruct;

class DecisionTree{

public:
	DecisionTree(){};
	virtual ~DecisionTree(){};

public:
    inline void SetConfig(sConfig& i_sConfig){m_psConfig = &i_sConfig;};
	
public:
	virtual void run() = 0;
	virtual int Train() = 0;

protected:
	int LoadSampleFile(SAMPLE& o_sSampleData);

protected:
	SAMPLE		m_objSample;
	sConfig*	m_psConfig;

};

#endif
