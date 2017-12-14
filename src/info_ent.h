#ifndef __INFO_ENT_H__
#define __INFO_ENT_H__

#include "decision_tree.h"

class InfoEnt : public DecisionTree
{

public:
    InfoEnt();
    ~InfoEnt();

public:
	virtual void run();
	virtual int Train();

private:
	int BuildDecisionTree();
};

#endif
