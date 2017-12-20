#ifndef __DECISION_TREE_H__
#define __DECISION_TREE_H__

#include <iostream>
#include <math.h>
#include "tools.h"
#include "LogWrite.h"
using namespace std;

#define DEFAULT_CONFIG_FILE	"./conf/decision_tree.conf"


typedef struct _sTreeStruct{
	string					m_strSplitName;
	string					m_strLabel;
	int						m_nSplitColumn;
	float					m_fSplitNum;
	bool					b_isLeaf;
	VEC_STR					m_vecChildrenFeatures;
	vector<_sTreeStruct>	m_vecChildren;

	_sTreeStruct()
	{
		m_strSplitName = "";
		m_strLabel = "";
		b_isLeaf = false;
		m_vecChildrenFeatures.clear();
		m_vecChildren.clear();
		m_nSplitColumn = -1;
		m_fSplitNum = 0.0;
	}
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
	int LoadSampleFile(VEC_STRVEC& o_sSampleData);
	bool isHomogeneous(VEC_STRVEC& i_sSampleData);

protected:
	VEC_STRVEC		m_objSample;
	sConfig*	m_psConfig;
	sTreeStruct m_sDecisionTree;

};

#endif
