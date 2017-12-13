#include "tools.h"


/*
nSection����˵����
���ڽ���url�����ַ���ʱ����Ϊurl�п��ܳ���"="���ַ������¶Բ�Ӧ�ò�ֵ��ַ������в��
������Ӵ˲������Բ�ִ�����������
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


