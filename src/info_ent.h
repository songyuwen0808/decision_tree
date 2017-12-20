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
	int BuildDecisionTree(VEC_STRVEC i_sSampleData, VEC_STR i_vecFeatureType, VEC_STR i_vecFeatureName, sTreeStruct& o_sDecisionTree);
	float CalcInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum, const string& i_strType, float& i_fSplitNum);
	
	float CalcStringInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum);
	float CalcNumInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum, float& i_fSplitNum);
	float CalcMultiInfoEnt(VEC_STRVEC& i_sSampleData, int i_nColumnNum);
	float CalcTotalEnt(VEC_STRVEC& i_sSampleData);
	
	int ChooseSplitColumn(VEC_STRVEC& i_sSampleData, VEC_STR& i_vecFeatureType, VEC_STR i_vecFeatureName, float& i_fSplitNum);
	int PruneTree(sTreeStruct& io_sDecisionTree);
	
	int GetSampleDataByName(VEC_STRVEC i_vecAllSample, int i_nColumnNum, string& i_strFindName, VEC_STRVEC& o_vecSampleData);
	int GetSampleDataByNum(VEC_STRVEC i_vecAllSample, int i_nColumnNum, string& i_strFindName, float i_fSplitNum, VEC_STRVEC& o_vecSampleData);
	int GetDistinctFeatureName(VEC_STRVEC& i_vecAllSample, int i_nColumnNum, VEC_STR& o_vecNameList);
};

#endif
