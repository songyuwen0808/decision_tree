#include "info_ent.h"



InfoEnt::InfoEnt()
{

}

InfoEnt::~InfoEnt()
{

}

int InfoEnt::BuildDecisionTree()
{
	return SUCCESS;
}

int InfoEnt::Train()
{
	if (0 != m_psConfig->CheckParam())
    {
        E_PRINTF("some of parameter is wrong in config file, please check!");
        return FAIL;
    }
    
    SAMPLE l_sSampleAll;
	if (SUCCESS != LoadSampleFile(l_sSampleAll))
	{
		E_PRINTF("Failed to load sample file!");
		return FAIL;
	}

	for (int l_nSampleNum = 0; l_nSampleNum < l_sSampleAll.size(); ++l_nSampleNum)
	{
		for (int l_nFeaturesNum = 0; l_nFeaturesNum < l_sSampleAll[l_nSampleNum].size(); ++l_nFeaturesNum)
			cout << l_sSampleAll[l_nSampleNum][l_nFeaturesNum].c_str() << " ";

		cout << endl;
	}

	return SUCCESS;
}


void InfoEnt::run()
{
	return;
}

