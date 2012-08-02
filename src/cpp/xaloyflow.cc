#include "xaloyflow.h"
#include "xaloyprinter.h"
#include <stdlib.h>
#include <stdio.h>
using namespace xaloy;

struct xtestflow	{
	const char *xtest_name;
	XaloyFlow *xtest_case;
};

typedef std::vector<xtestflow*>::iterator FlowIterator;

XaloyFlow* XaloyFlow::Global = new XaloyFlow();

int XaloyFlow::execute()	{
	int result = 0;
	for(FlowIterator iter = this->_flowList.begin(); iter != this->_flowList.end(); iter++)	{
		print_color_text(COLOR_BLUE, "========== CASE: '");
		print_color_text(COLOR_BLUE, (*iter)->xtest_name);
		print_color_text(COLOR_BLUE, "' start ==========\n");
		(*iter)->xtest_case->run();		
	}
	return result;
}
void XaloyFlow::push(const char *name , XaloyFlow *xcase)	{
	xtestflow *flow = (xtestflow*)malloc(sizeof(xtestflow));
	flow->xtest_name = name;
	flow->xtest_case = xcase;
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