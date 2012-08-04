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

int XaloyFlow::execute(bool ispager)	{
	int result = 0;
	XaloyFlow *tar = NULL;
	for(FlowIterator iter = this->_flowList.begin(); iter != this->_flowList.end(); iter++)	{
		print_color_text(COLOR_BLUE, "========== CASE: '");
		print_color_text(COLOR_BLUE, (*iter)->xtest_name);
		print_color_text(COLOR_BLUE, "' start ==========\n\n");		
		tar = (*iter)->xtest_case;
		tar->run();
		if(tar->_counter == 0)	{
			print_color_text(COLOR_YELLOW, "\n\n[MESSAGE] ");
			printf("No test event happened\n");
		}			
		else	{
			print_color_text(COLOR_YELLOW, "\n\nThe result of '");
			print_color_text(COLOR_YELLOW,  (*iter)->xtest_name);
			print_color_text(COLOR_YELLOW, "':\n");
			if(tar->_pass != tar->_counter)	{
				print_color_text(COLOR_RED, "[FAIL]    ");
			}
			else	{
				print_color_text(COLOR_GREEN, "[SUCCESS] ");
			}
			printf("pass %d, total %d\n\n", tar->_pass, tar->_counter);
		}
		// if ispager is true
		if(ispager)	{
			printf("press any key to continue\n");
			getchar();			
		}
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
