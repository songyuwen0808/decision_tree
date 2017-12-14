#include <unistd.h>
#include <dirent.h>
#include "decision_tree.h"

int DecisionTree::LoadSampleFile(SAMPLE& o_sSampleData)
{
	vector<string> l_vecFileList;
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

			FEATURE l_vecFeatures;
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

