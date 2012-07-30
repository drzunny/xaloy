#include "xaloyflow.h"
#include <stdlib.h>
#include <stdio.h>
using namespace xaloy;

typedef std::vector<xtestflow*>::iterator FlowIterator;

struct xtestflow	{
	const char *xtest_name;
	XaloyFlow *xtest_case;
};

int XaloyFlow::execute()	{
	int result = 0;
	for(FlowIterator iter = this->_flowList.begin(); iter != this->_flowList.end(); iter++)	{
		printf("case '%s':\n", (*iter)->xtest_name);
		(*iter)->xtest_case->run();		
	}
	return result;
}
void XaloyFlow::push(const char *name, XaloyFlow *test)	{
	xtestflow *flow = (xtestflow*)malloc(sizeof(xtestflow));
	flow->xtest_name = name;
	flow->xtest_case = test;
	this->_flowList.push_back(flow);
}

XaloyFlow::~XaloyFlow()	{
	if(this->_flowList.size() > 0)	{
		for(FlowIterator iter = this->_flowList.begin(); iter != this->_flowList.end(); iter++)	{
			delete (*iter)->xtest_case;
			free((*iter));			
		}
	}		
}