#include "xaloyflow.h"
#include "xaloyprinter.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace xaloy;

struct xtestflow	{
	const char *xtest_name;
	XaloyFlow *xtest_case;
};

static std::vector<xtestflow>
GLOBAL_FLOWLIST;

typedef std::vector<xtestflow>::iterator FlowIterator;

XaloyFlow* XaloyFlow::Global = new XaloyFlow();

int XaloyFlow::execute(bool ispager)	{
	int result = 0;
	XaloyFlow *tar = NULL;
	for(FlowIterator iter = GLOBAL_FLOWLIST.begin(); iter != GLOBAL_FLOWLIST.end(); iter++)	{
		print_color_text(COLOR_BLUE, "========== CASE: '");
		print_color_text(COLOR_BLUE, (*iter).xtest_name);
		print_color_text(COLOR_BLUE, "' start ==========\n\n");		
		tar = (*iter).xtest_case;
		tar->run();
		if(tar->_counter == 0)	{
			print_color_text(COLOR_YELLOW, "\n\n[MESSAGE] ");
			printf("No test event happened\n");
		}			
		else	{
			print_color_text(COLOR_YELLOW, "\n\nThe result of '");
			print_color_text(COLOR_YELLOW,  (*iter).xtest_name);
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
	xtestflow flow;
	flow.xtest_name = name;
	flow.xtest_case = xcase;
	GLOBAL_FLOWLIST.push_back(flow);
}

XaloyFlow::~XaloyFlow()	{
	if(GLOBAL_FLOWLIST.size() > 0)	{
		GLOBAL_FLOWLIST.clear();
	}		
}
