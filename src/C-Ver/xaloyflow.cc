#include "xaloyflow.h"
#include <stdlib.h>
#include <stdio.h>
using namespace xaloy;

typedef std::vector<xtestflow*>::iterator FlowIterator;

int XaloyFlow::execute()	{
	int result = 0;
	for(FlowIterator iter = this->_flowList.begin(); iter != this->_flowList.end(); iter++)	{
		printf("case '%s':\n", (*iter)->xtest_name);
		(*iter)->xtest_case->run();		
	}
	return result;
}
void XaloyFlow::push(xcase_block *block)	{
	if(block == NULL)
		return;	
	this->_flowList.push_back(block);
}

XaloyFlow::~XaloyFlow()	{
	if(this->_flowList.size() > 0)	{
		for(FlowIterator iter = this->_flowList.begin(); iter != this->_flowList.end(); iter++)	{
			delete (*iter)->xtest_case;
			free((*iter));			
		}
	}		
}