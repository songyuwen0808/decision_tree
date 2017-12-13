#include "decision_tree.h"

int main(int argc, char* argv[])
{
	DecisionTree* l_objDecisionTree = new DecisionTree();
	string l_strConfigFile = string(DEFAULT_CONFIG_FILE);
	if (argc > 1)
		l_strConfigFile = string(argv[1]);

	sConfig l_sConfig;
	Tools::GetToolsInstance().LoadConfig(l_strConfigFile, l_sConfig);
	for(int l_nCount = 0; l_nCount < l_sConfig.m_vecExpectType.size(); l_nCount++)
        D_PRINTF("ExpectType[%d] = %s", l_nCount, l_sConfig.m_vecExpectType[l_nCount].c_str());
	
	return 0;
}
