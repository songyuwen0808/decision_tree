#include "tools.h"


/*
nSection:
for param like url, it may contains character "=" or something else
so add this parameter, when "i_nSection != -1", split the string into "i_nSection" parts
*/
void Tools::SplitString(const string& i_strSrcString, const string& i_strDelim, vector<string>& o_vecResult, int i_nSection)
{
	size_t l_nLast = 0;
	size_t index = i_strSrcString.find_first_of(i_strDelim, l_nLast);
	
	while ((index != string::npos) && (i_nSection != 1))
	{
		o_vecResult.push_back(i_strSrcString.substr(l_nLast, index - l_nLast));
		l_nLast = index + 1;
		index = i_strSrcString.find_first_of(i_strDelim, l_nLast);
		i_nSection--;
	}
	
	if (index - l_nLast > 0)
		o_vecResult.push_back(i_strSrcString.substr(l_nLast, index - l_nLast));

	return;
}

void Tools::DelCharacter(string& io_strSrc, const string& i_strCharacter)
{
	int l_nPos = io_strSrc.find(i_strCharacter);
	int l_nLen = i_strCharacter.length();
	
	while (-1 < l_nPos)
	{
		io_strSrc.erase(l_nPos, l_nLen);
		l_nPos = io_strSrc.find(i_strCharacter);
	}
}

int Tools::LoadConfig(string& i_strFilePath, sConfig& o_sConfig)
{
	if (0 >= i_strFilePath.length())
	{
		E_PRINTF("config file path is error!");
		return FAIL;
	}

	ifstream l_objConfigFile(i_strFilePath.c_str());
	if (!l_objConfigFile.is_open())
	{
		E_PRINTF("Failed to open config file, please make sure config file path is correct!current path = %s", i_strFilePath.c_str());
		return FAIL;
	}
	
	string		  l_strContent		= "";
	string		  l_strDelCharacter   = " ";
	string		  l_strDelim		  = "=";
	string		  l_strDataDelim	  = ",";
	vector<string>  l_vecSplitContent;
	l_vecSplitContent.clear();
	while(getline(l_objConfigFile, l_strContent))
	{
		if (!l_strContent.compare(0, 1, "#"))
			continue;
		
		l_vecSplitContent.clear();
		DelCharacter(l_strContent, l_strDelCharacter);
		SplitString(l_strContent, l_strDelim, l_vecSplitContent, 2);
		
		if (2 != l_vecSplitContent.size())
			continue;
		
		if (!l_vecSplitContent[0].compare("sample_path"))
			o_sConfig.m_strSamplePath = l_vecSplitContent[1];
		else if (!l_vecSplitContent[0].compare("input_path"))
			o_sConfig.m_strInPath = l_vecSplitContent[1];
		else if (!l_vecSplitContent[0].compare("output_path"))
			o_sConfig.m_strOutPath = l_vecSplitContent[1];
		else if (!l_vecSplitContent[0].compare("bak_path"))
			o_sConfig.m_strBakPath = l_vecSplitContent[1];
		else if (!l_vecSplitContent[0].compare("calc_type"))
			o_sConfig.m_nCalcType = atoi(l_vecSplitContent[1].c_str());
		else if (!l_vecSplitContent[0].compare("prune_type"))
			o_sConfig.m_nPruneType = atoi(l_vecSplitContent[1].c_str());
		else if (!l_vecSplitContent[0].compare("features_type"))
			SplitString(l_vecSplitContent[1], l_strDataDelim, o_sConfig.m_vecFeaturesType);
		else if (!l_vecSplitContent[0].compare("features_name"))
			SplitString(l_vecSplitContent[1], l_strDataDelim, o_sConfig.m_vecFeaturesName);
		else if (!l_vecSplitContent[0].compare("log_path"))
			LogWrite::Instance().SetLogPath(l_vecSplitContent[1].c_str());
		else if (!l_vecSplitContent[0].compare("is_debug"))
			LogWrite::Instance().SetDebug(atoi(l_vecSplitContent[1].c_str()));
		else if (!l_vecSplitContent[0].compare("is_to_file"))
			LogWrite::Instance().SetToFile(atoi(l_vecSplitContent[1].c_str()));
		else if (!l_vecSplitContent[0].compare("is_to_screen"))
			LogWrite::Instance().SetToScreen(atoi(l_vecSplitContent[1].c_str()));
		else if (!l_vecSplitContent[0].compare("pre_fix"))
			LogWrite::Instance().SetNeedPreFix(l_vecSplitContent[1].c_str());
	}
    
    if (o_sConfig.m_vecFeaturesType.size() > o_sConfig.m_vecFeaturesName.size())
    {
        for(int l_nCount = o_sConfig.m_vecFeaturesName.size(); l_nCount < o_sConfig.m_vecFeaturesType.size(); ++l_nCount)
        {
            char l_szTmp[FEATURE_NAME_MAX_LEN + 1] = "0";
            snprintf(l_szTmp, FEATURE_NAME_MAX_LEN, "%dth_feature", l_nCount + 1);
            o_sConfig.m_vecFeaturesName.push_back(string(l_szTmp));
        }
    }
	
	return SUCCESS;
}

