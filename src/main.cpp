#include "decision_tree.h"
#include "info_ent.h"

#define CALC_TYPE_INFO_ENT	0


DecisionTree* CreateDesicionTreeObject(int i_nCalcType)
{
	switch(i_nCalcType)
	{
		case CALC_TYPE_INFO_ENT:
			return new InfoEnt();
		default:
			return NULL;
	}

	return NULL;
}



int main(int argc, char* argv[])
{
	string l_strConfigFile = string(DEFAULT_CONFIG_FILE);
	if (argc > 1)
		l_strConfigFile = string(argv[1]);

	sConfig l_sConfig;
	Tools::GetToolsInstance().LoadConfig(l_strConfigFile, l_sConfig);

	DecisionTree* l_objDecisionTree = CreateDesicionTreeObject(l_sConfig.m_nCalcType);
	if (NULL == l_objDecisionTree)
	{
		E_PRINTF("failed to create object by calc type, please check parameter calc_type in config file!");
		return FAIL;
	}
	
	l_objDecisionTree->SetConfig(l_sConfig);
	if (SUCCESS != l_objDecisionTree->Train())
	{
		E_PRINTF("train failed!");
		return FAIL;
	}
	l_objDecisionTree->run();
	
	return SUCCESS;
}
