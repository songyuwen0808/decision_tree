#include "decision_tree.h"


DecisionTree::DecisionTree()
{
	m_strConfig = string(DEFAULT_CONFIG_FILE);
}

DecisionTree::~DecisionTree()
{

}

DecisionTree::DecisionTree(string& i_strConfig)
{
	m_strConfig = i_strConfig;
}

int DecisionTree::Init()
{
	if (0 >= m_strConfig.length())
	{
		E_PRINTF("配置文件路径为空!");
        return 0;
	}

    I_PRINTF("开始解析配置文件， 配置文件 = %s", m_strConfig.c_str());
    
    
    
	return 0;
}


























