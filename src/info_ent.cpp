#include <strings.h>
#include "info_ent.h"

void PrintVecString(VEC_STR i_vecData)
{
	cout << "PrintVecString++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	for (int l_nCount = 0; l_nCount < i_vecData.size(); ++l_nCount)
		cout << i_vecData[l_nCount].c_str() << " ";

	cout << endl;
	cout << "PrintVecString====================================================================" << endl;
}

void PrintStrVecString(VEC_STRVEC i_vecData)
{
	cout << "PrintStrVecString++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	for (int l_nLine = 0; l_nLine < i_vecData.size(); ++l_nLine)
	{
		for (int l_nColumn = 0; l_nColumn < i_vecData[l_nLine].size(); ++l_nColumn)
			cout << i_vecData[l_nLine][l_nColumn].c_str() << " ";

		cout << endl;
	}
	cout << "PrintStrVecString====================================================================" << endl;
}


void PrintTree(sTreeStruct m_sDecisionTree)
{
	I_PRINTF("%d, %d, %s, %s, %f", m_sDecisionTree.b_isLeaf, m_sDecisionTree.m_nSplitColumn, m_sDecisionTree.m_strLabel.c_str(), m_sDecisionTree.m_strSplitName.c_str(), m_sDecisionTree.m_fSplitNum);
	if (true == m_sDecisionTree.b_isLeaf)
		return;

	for (int l_nCount = 0; l_nCount < m_sDecisionTree.m_vecChildrenFeatures.size(); ++l_nCount)
	{
		I_PRINTF("%dth child start: %s", l_nCount, m_sDecisionTree.m_vecChildrenFeatures[l_nCount].c_str());
		PrintTree(m_sDecisionTree.m_vecChildren[l_nCount]);
		I_PRINTF("%dth child end: %s", l_nCount, m_sDecisionTree.m_vecChildrenFeatures[l_nCount].c_str());
	}
}

InfoEnt::InfoEnt()
{

}

InfoEnt::~InfoEnt()
{

}

int InfoEnt::PruneTree(sTreeStruct& io_sDecisionTree)
{
	return 0;
}

float InfoEnt::CalcStringInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum)
{
	float l_fEnt = 0.0;
	int l_nLine = 0;
	int l_nTypeIndex = i_sSampleData[0].size() - 1;
	
	MAP_STR_STRINT_MAP l_mapCalcContainer;
	l_mapCalcContainer.clear();

	MAP_STR_STRINT_MAP::iterator	l_iterFindName;
	MAP_STR_INT::iterator			l_iterFindTpye;
	int l_nTotalNum = 0;
	for (l_nLine = 0; l_nLine < i_sSampleData.size(); ++l_nLine)
	{
		if (0 == strcasecmp(i_sSampleData[l_nLine][i_nColumnNum].c_str(), "null"))
			continue;

		l_nTotalNum++;
		l_iterFindName = l_mapCalcContainer.find(i_sSampleData[l_nLine][i_nColumnNum].c_str());
		if (l_iterFindName == l_mapCalcContainer.end())
		{
			MAP_STR_INT l_mapTmp;
			l_mapTmp.insert(pair<string, int>(i_sSampleData[l_nLine][l_nTypeIndex], 1));
			l_mapCalcContainer.insert(pair<string, MAP_STR_INT>(i_sSampleData[l_nLine][i_nColumnNum], l_mapTmp));
			continue;
		}

		
		l_iterFindTpye = l_iterFindName->second.find(i_sSampleData[l_nLine][l_nTypeIndex]);
		if (l_iterFindTpye != l_iterFindName->second.end())
			l_iterFindTpye->second++;
		else
			l_iterFindName->second.insert(pair<string, int>(i_sSampleData[l_nLine][l_nTypeIndex], 1));
	}

	int l_nCurrFeatNum = 0;
	for (l_iterFindName = l_mapCalcContainer.begin(); l_iterFindName != l_mapCalcContainer.end(); ++l_iterFindName)
	{
		l_nCurrFeatNum = 0;
		for (l_iterFindTpye = l_iterFindName->second.begin(); l_iterFindTpye != l_iterFindName->second.end(); ++l_iterFindTpye)
			l_nCurrFeatNum += l_iterFindTpye->second;

		if (0 >= l_nCurrFeatNum)
			continue;

		for (l_iterFindTpye = l_iterFindName->second.begin(); l_iterFindTpye != l_iterFindName->second.end(); ++l_iterFindTpye)
		{
			float l_fProb = (float)l_iterFindTpye->second / (float)l_nCurrFeatNum;
			float l_fWeight = (float)l_nCurrFeatNum / (float)l_nTotalNum;
			l_fEnt -= (l_fProb * log2(l_fProb)) * l_fWeight;
			// D_PRINTF("%s, %s, %d, %d, %d", l_iterFindName->first.c_str(), l_iterFindTpye->first.c_str(), l_iterFindTpye->second, l_nCurrFeatNum, l_nTotalNum);
		}
	}	

	// D_PRINTF("feature name = %s, ent = %f", m_psConfig->m_vecFeaturesName[i_nColumnNum].c_str(), l_fEnt);

	return l_fEnt;
}

float InfoEnt::CalcNumInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum, float& i_fSplitNum)
{
	VEC_FLOAT l_vecNumList;
	l_vecNumList.clear();

	int l_nLine = 0;
	for (l_nLine = 0; l_nLine < i_sSampleData.size(); ++l_nLine)
		l_vecNumList.push_back(atof(i_sSampleData[l_nLine][i_nColumnNum].c_str()));

	if (0 >= l_vecNumList.size())
		return 0;

	Tools::GetToolsInstance().QSort(l_vecNumList, 0, l_vecNumList.size() - 1);

	VEC_FLOAT l_vecSplitList;
	l_vecSplitList.clear();

	int l_nCount = 0;
	for (l_nCount = 0; l_nCount < l_vecNumList.size() - 1; ++l_nCount)
		l_vecSplitList.push_back((l_vecNumList[l_nCount] + l_vecNumList[l_nCount + 1]) / 2.0);

	string l_strType1 = "greater";
	string l_strType2 = "less";
	string l_strCurrType = "";
	int l_nTotalNum = 0;
	MAP_STR_STRINT_MAP::iterator	l_iterFindName;
	MAP_STR_INT::iterator			l_iterFindTpye;
	int l_nTypeIndex = i_sSampleData[0].size() - 1;
	float l_fEnt = 0.0;
	float l_fMinEnt = 1;
	
	for (l_nCount = 0; l_nCount < l_vecSplitList.size(); ++l_nCount)
	{
		l_nTotalNum = 0;
		l_fEnt = 0.0;
		MAP_STR_STRINT_MAP l_mapCalcContainer;
		l_mapCalcContainer.clear();

		for (l_nLine = 0; l_nLine < i_sSampleData.size(); ++l_nLine)
		{
			if (0 == strcasecmp(i_sSampleData[l_nLine][i_nColumnNum].c_str(), "null"))
				continue;

			l_nTotalNum++;
			l_strCurrType = "";
			if (atof(i_sSampleData[l_nLine][i_nColumnNum].c_str()) > l_vecSplitList[l_nCount])
				l_strCurrType = l_strType1;
			else
				l_strCurrType = l_strType2;

			l_iterFindName = l_mapCalcContainer.find(l_strCurrType);
			if (l_iterFindName == l_mapCalcContainer.end())
			{
				MAP_STR_INT l_mapTmp;
				l_mapTmp.insert(pair<string, int>(i_sSampleData[l_nLine][l_nTypeIndex], 1));
				l_mapCalcContainer.insert(pair<string, MAP_STR_INT>(l_strCurrType, l_mapTmp));
				continue;
			}

			l_iterFindTpye = l_iterFindName->second.find(i_sSampleData[l_nLine][l_nTypeIndex]);
			if (l_iterFindTpye != l_iterFindName->second.end())
				l_iterFindTpye->second++;
			else
				l_iterFindName->second.insert(pair<string, int>(i_sSampleData[l_nLine][l_nTypeIndex], 1));
		}

		int l_nCurrFeatNum = 0;
		for (l_iterFindName = l_mapCalcContainer.begin(); l_iterFindName != l_mapCalcContainer.end(); ++l_iterFindName)
		{
			l_nCurrFeatNum = 0;
			for (l_iterFindTpye = l_iterFindName->second.begin(); l_iterFindTpye != l_iterFindName->second.end(); ++l_iterFindTpye)
				l_nCurrFeatNum += l_iterFindTpye->second;

			if (0 >= l_nCurrFeatNum)
				continue;

			for (l_iterFindTpye = l_iterFindName->second.begin(); l_iterFindTpye != l_iterFindName->second.end(); ++l_iterFindTpye)
			{
				float l_fProb = (float)l_iterFindTpye->second / (float)l_nCurrFeatNum;
				float l_fWeight = (float)l_nCurrFeatNum / (float)l_nTotalNum;
				l_fEnt -= (l_fProb * log2(l_fProb)) * l_fWeight;
			}
		}

		if (l_fMinEnt > l_fEnt)
		{
			l_fMinEnt = l_fEnt;
			i_fSplitNum = l_vecSplitList[l_nCount];
		}
	}


	// D_PRINTF("feature name = %s, ent = %f", m_psConfig->m_vecFeaturesName[i_nColumnNum].c_str(), l_fEnt);
	return l_fMinEnt;
}

float InfoEnt::CalcMultiInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum)
{
	return 0;
}

float InfoEnt::CalcTotalEnt(VEC_STRVEC& i_sSampleData)
{
	float l_fTotalEnt = 0.0;
	int l_nTypeIndex = i_sSampleData[0].size() - 1;

	MAP_STR_INT l_mapTotal;
	MAP_STR_INT::iterator l_itFindType;
	int l_nTotalNum = 0;
	
	int l_nLine = 0;
	for (l_nLine = 0; l_nLine < i_sSampleData.size(); ++l_nLine)
	{
		if (0 == strcasecmp(i_sSampleData[l_nLine][l_nTypeIndex].c_str(), "null"))
			continue;

		l_nTotalNum++;
		l_itFindType = l_mapTotal.find(i_sSampleData[l_nLine][l_nTypeIndex]);
		if (l_itFindType != l_mapTotal.end())
			l_itFindType->second++;
		else
			l_mapTotal.insert(pair<string, int>(i_sSampleData[l_nLine][l_nTypeIndex], 1));
	}

	for (l_itFindType = l_mapTotal.begin(); l_itFindType != l_mapTotal.end(); ++l_itFindType)
	{
		float l_fProb = (float)l_itFindType->second / (float)l_nTotalNum;
		l_fTotalEnt -= l_fProb * log2(l_fProb);
	}

	// D_PRINTF("current totan Ent(D) = [%f]", l_fTotalEnt);
	return l_fTotalEnt;
}

float InfoEnt::CalcInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum, const string& i_strType, float& i_fSplitNum)
{
	float l_fEnt = 0.0;
	
	if (0 == i_strType.compare(FEATURES_TYPE_STRING))
		l_fEnt = CalcStringInfoEnt(i_sSampleData, i_nColumnNum);
	else if (0 == i_strType.compare(FEATURES_TYPE_NUM))
		l_fEnt = CalcNumInfoEnt(i_sSampleData, i_nColumnNum, i_fSplitNum);
	else if (0 == i_strType.compare(FEATURES_TYPE_MILTI))
		l_fEnt = CalcMultiInfoEnt(i_sSampleData, i_nColumnNum);

	return l_fEnt;
}


int InfoEnt::ChooseSplitColumn(VEC_STRVEC& i_sSampleData, VEC_STR& i_vecFeatureType, VEC_STR i_vecFeatureName, float& i_fSplitNum)
{
	int l_nColumnNum	= 0;
	int l_nCurrBestColum	= -1;
	float l_fCurrMaxGain		= 0;
	
	float l_fTotalEnt = 0.0;
	l_fTotalEnt = CalcTotalEnt(i_sSampleData);
	float l_fSplitNum = 0.0;

	for (l_nColumnNum = 0; l_nColumnNum < i_sSampleData[0].size() - 1; ++l_nColumnNum)
	{
		float l_fCurrGain = 0.0;
		l_fCurrGain = CalcInfoEnt(i_sSampleData, l_nColumnNum, i_vecFeatureType[l_nColumnNum], l_fSplitNum);
		if (1 == l_fCurrGain)
			continue;

		l_fCurrGain = l_fTotalEnt - l_fCurrGain;
		// D_PRINTF("name = %s, gain = %f, current max gain = %f", i_vecFeatureName[l_nColumnNum].c_str(), l_fCurrGain, l_fCurrMaxGain);
		if (l_fCurrMaxGain < l_fCurrGain)
		{
			l_fCurrMaxGain = l_fCurrGain;
			l_nCurrBestColum = l_nColumnNum;

			if (FEATURES_TYPE_NUM == i_vecFeatureType[l_nColumnNum])
				i_fSplitNum = l_fSplitNum;
		}
	}

	
	return l_nCurrBestColum;
}

int InfoEnt::BuildDecisionTree(VEC_STRVEC i_sSampleData, VEC_STR i_vecFeatureType, VEC_STR i_vecFeatureName, sTreeStruct& o_sDecisionTree)
{
	// PrintStrVecString(i_sSampleData);

	if (0 >= i_sSampleData.size())
		return SUCCESS;
	else if (true == isHomogeneous(i_sSampleData))
	{
		int l_nTypeIndex = i_sSampleData[0].size() - 1;
		
		sTreeStruct l_sNode;
		o_sDecisionTree.b_isLeaf = true;
		o_sDecisionTree.m_strLabel = i_sSampleData[0][l_nTypeIndex];
	}
	else
	{
		string l_strSplitName = "";
		float l_fSplitNum = 0.0;
		int l_nBestColumn = ChooseSplitColumn(i_sSampleData, i_vecFeatureType, i_vecFeatureName, l_fSplitNum);
        // D_PRINTF("current best choosen : %s, %d", i_vecFeatureName[l_nBestColumn].c_str(), l_nBestColumn);

		VEC_STR l_vecNameList;
		l_vecNameList.clear();

		// D_PRINTF("current type = %s", i_vecFeatureType[l_nBestColumn].c_str());
		if (0 == i_vecFeatureType[l_nBestColumn].compare(FEATURES_TYPE_STRING))
			GetDistinctFeatureName(i_sSampleData, l_nBestColumn, l_vecNameList);
		else
		{
			l_vecNameList.push_back("greater");
			l_vecNameList.push_back("less");
		}
		
		o_sDecisionTree.b_isLeaf = false;
		o_sDecisionTree.m_nSplitColumn = l_nBestColumn;
		o_sDecisionTree.m_strSplitName = i_vecFeatureName[l_nBestColumn];
		o_sDecisionTree.m_fSplitNum = l_fSplitNum;
		

		VEC_STR l_vecCurrFeatType = i_vecFeatureType;
		VEC_STR l_vecCurrFeatName = i_vecFeatureName;
		
		l_vecCurrFeatType.erase(l_vecCurrFeatType.begin() + l_nBestColumn);
		l_vecCurrFeatName.erase(l_vecCurrFeatName.begin() + l_nBestColumn);

		for (int l_nCount = 0; l_nCount < l_vecNameList.size(); ++l_nCount)
		{
			o_sDecisionTree.m_vecChildrenFeatures.push_back(l_vecNameList[l_nCount]);

			VEC_STRVEC l_vecCurrSample;
			l_vecCurrSample.clear();

			D_PRINTF("current feature type = %s, column = %d", i_vecFeatureType[l_nBestColumn].c_str(), l_nBestColumn);
			if (0 == i_vecFeatureType[l_nBestColumn].compare(FEATURES_TYPE_STRING))
				GetSampleDataByName(i_sSampleData, l_nBestColumn, l_vecNameList[l_nCount], l_vecCurrSample);
			else
				GetSampleDataByNum(i_sSampleData, l_nBestColumn, l_vecNameList[l_nCount], l_fSplitNum, l_vecCurrSample);

			// D_PRINTF("current name = %s, split num = %f", l_vecNameList[l_nCount].c_str(), l_fSplitNum);
			sTreeStruct l_vecNewNode;
			BuildDecisionTree(l_vecCurrSample, l_vecCurrFeatType, l_vecCurrFeatName, l_vecNewNode);
			o_sDecisionTree.m_vecChildren.push_back(l_vecNewNode);
		}
	}

	return SUCCESS;
}

int InfoEnt::GetSampleDataByName(VEC_STRVEC i_vecAllSample, int i_nColumnNum, string& i_strFindName, VEC_STRVEC& o_vecSampleData)
{
	VEC_STRVEC::iterator l_itSearch;
	for (l_itSearch = i_vecAllSample.begin(); l_itSearch != i_vecAllSample.end();)
	{
		VEC_STR l_vecTmp = *l_itSearch;
		if (0 != l_vecTmp[i_nColumnNum].compare(i_strFindName.c_str()))
			++l_itSearch;
		else
		{
			l_vecTmp.erase(l_vecTmp.begin() + i_nColumnNum);
			o_vecSampleData.push_back(l_vecTmp);
			l_itSearch = i_vecAllSample.erase(l_itSearch);
		}
	}

	return 0;
}

int InfoEnt::GetSampleDataByNum(VEC_STRVEC i_vecAllSample, int i_nColumnNum, string& i_strFindName, float i_fSplitNum, VEC_STRVEC& o_vecSampleData)
{
	string l_strName1 = "greater";
	string l_strName2 = "less";
	
	string l_strCurrType = "";
	VEC_STRVEC::iterator l_itSearch;
	for (l_itSearch = i_vecAllSample.begin(); l_itSearch != i_vecAllSample.end();)
	{
		l_strCurrType = "";
		VEC_STR l_vecTmp = *l_itSearch;
		if (atof(l_vecTmp[i_nColumnNum].c_str()) > i_fSplitNum)
			l_strCurrType = l_strName1;
		else
			l_strCurrType = l_strName2;

		if (0 != l_strCurrType.compare(i_strFindName.c_str()))
			++l_itSearch;
		else
		{
			l_vecTmp.erase(l_vecTmp.begin() + i_nColumnNum);
			o_vecSampleData.push_back(l_vecTmp);
			l_itSearch = i_vecAllSample.erase(l_itSearch);
		}
	}
	
	return 0;
}

int InfoEnt::GetDistinctFeatureName(VEC_STRVEC& i_vecAllSample, int i_nColumnNum, VEC_STR& o_vecNameList)
{
	MAP_STR_INT l_mapNameList;
	l_mapNameList.clear();

	for (int l_nLine = 0; l_nLine < i_vecAllSample.size(); ++l_nLine)
	{
		if (l_mapNameList.find(i_vecAllSample[l_nLine][i_nColumnNum]) != l_mapNameList.end())
			continue;
		else
		{
			o_vecNameList.push_back(i_vecAllSample[l_nLine][i_nColumnNum]);
			l_mapNameList.insert(pair<string, int>(i_vecAllSample[l_nLine][i_nColumnNum], 1));
		}
	}

	// PrintVecString(o_vecNameList);

	return 0;
}


int InfoEnt::Train()
{
	if (0 != m_psConfig->CheckParam())
	{
		E_PRINTF("some of parameter is wrong in config file, please check!");
		return FAIL;
	}
	
	VEC_STRVEC l_sSampleAll;
	if (SUCCESS != LoadSampleFile(l_sSampleAll))
	{
		E_PRINTF("Failed to load sample file!");
		return FAIL;
	}

	int l_nRet = SUCCESS;
	l_nRet = BuildDecisionTree(l_sSampleAll, m_psConfig->m_vecFeaturesType, m_psConfig->m_vecFeaturesName, m_sDecisionTree);
	if (SUCCESS != l_nRet)
	{
		E_PRINTF("build decision tree by info_ent failed!");
		return FAIL;
	}

	PrintTree(m_sDecisionTree);

	return SUCCESS;
}


void InfoEnt::run()
{
	return;
}

