#include "decision_tree.h"

int main(int argc, char* argv[])
{
	DecisionTree* l_objDecisionTree = new DecisionTree();
	if (argc > 1)
	{
		l_objDecisionTree->SetConfig(string(argv[1]));
	}

	
	
    
    return 0;
}