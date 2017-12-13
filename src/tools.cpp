#include "tools.h"


/*
nSection参数说明：
对于解析url类似字符串时，因为url中可能出现"="等字符，导致对不应该拆分的字符串进行拆分
所以添加此参数，对拆分次数进行限制
*/
void Tools::SplitString(const string& i_strSrcString, const string& i_strDelim, vector<std::string>& o_vecResult, int i_nSection = -1)
{
	size_t l_nLast = 0;
	size_t index = i_strSrcString.find_first_of(i_strDelim, l_nLast);
	
	while ((index != std::string::npos) && (i_nSection != 1))
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


