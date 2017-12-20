#include <unistd.h>
#include <dirent.h>
#include "decision_tree.h"

int DecisionTree::LoadSampleFile(VEC_STRVEC& o_sSampleData)
{
	VEC_STR l_vecFileList;
	l_vecFileList.clear();

	DIR* l_psDirectory = NULL;
	l_psDirectory = opendir(m_psConfig->m_strSamplePath.c_str());
	if (NULL == l_psDirectory)
	{
		E_PRINTF("open directory failed!sample file path = %s", m_psConfig->m_strSamplePath.c_str());
		return SUCCESS;
	}

	struct dirent* l_psDirent = NULL;
	while(NULL != (l_psDirent = readdir(l_psDirectory)))
	{
		/*
		.			: current dir
		..			: parent dir
		d_type = 8	: file
		d_type = 10	: link file
		d_type = 4	: dir
		*/
		if ((0 == strcmp(l_psDirent->d_name, ".")) || (0 == strcmp(l_psDirent->d_name, "..")))
			continue;
		else if (8 != l_psDirent->d_type)
			continue;

		string l_strFilePath = m_psConfig->m_strSamplePath + string("/") + string(l_psDirent->d_name);
		ifstream l_objSampleFile(l_strFilePath.c_str());
		if (!l_objSampleFile.is_open())
			continue;

		string	l_strContent		= "";
		string	l_strDelCharacter   = " ";
		string	l_strDelim			= "=";
		string	l_strDataDelim		= ",";
		
		while(getline(l_objSampleFile, l_strContent))
		{
			if (!l_strContent.compare(0, 1, "#"))
				continue;

			VEC_STR l_vecFeatures;
			l_vecFeatures.clear();
			
			Tools::GetToolsInstance().DelCharacter(l_strContent, l_strDelCharacter);
			Tools::GetToolsInstance().SplitString(l_strContent, l_strDataDelim, l_vecFeatures);
			if (m_psConfig->m_vecFeaturesType.size() != (l_vecFeatures.size() - 1))
				continue;

			o_sSampleData.push_back(l_vecFeatures);
		}
			
		
	}

	closedir(l_psDirectory);

	return SUCCESS;
}

bool DecisionTree::isHomogeneous(VEC_STRVEC& i_sSampleData)
{
	if (0 >= i_sSampleData.size())
		return true;

	int l_nTypeIndex	= i_sSampleData[0].size() - 1;

	if (0 > l_nTypeIndex)
		return true;
	
	string l_nTypeName	= i_sSampleData[0][l_nTypeIndex];

	int l_nCount = 0;
	for(l_nCount = 1; l_nCount < i_sSampleData.size(); ++l_nCount)
	{
		// D_PRINTF("sample type = %s, first type name = %s", i_sSampleData[l_nCount][l_nTypeIndex].c_str(), l_nTypeName.c_str());
		if (0 != i_sSampleData[l_nCount][l_nTypeIndex].compare(l_nTypeName.c_str()))
			return false;
	}


	return true;
}

