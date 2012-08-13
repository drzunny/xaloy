#include "xaloyflow.h"
#include "xaloyprinter.h"
#include <stdlib.h>
#include <stdio.h>
using namespace xaloy;
using namespace std;

int XaloyFlow::execute(bool ispager)	{
	int result = 0;
	size_t sz = xlist.size();
	for(size_t i = 0; i < sz; i++)	{
		print_color_text(COLOR_BLUE, "========== CASE: '");
		print_color_text(COLOR_BLUE, xlist[i]->cname);
		print_color_text(COLOR_BLUE, "' start ==========\n\n");		
		xlist[i]->run();
		if(xlist[i]->counter == 0)	{
			print_color_text(COLOR_YELLOW, "\n\n[MESSAGE] ");
			printf("No test event happened\n");
		}			
		else	{
			print_color_text(COLOR_YELLOW, "\n\nThe result of '");
			print_color_text(COLOR_YELLOW,  xlist[i]->cname);
			print_color_text(COLOR_YELLOW, "':\n");
			if(xlist[i]->pass != xlist[i]->counter)	{
				print_color_text(COLOR_RED, "[FAIL]    ");
			}
			else	{
				print_color_text(COLOR_GREEN, "[SUCCESS] ");
			}
			printf("pass %d, total %d\n\n", xlist[i]->pass, xlist[i]->counter);
		}
		// if ispager is true
		if(ispager)	{
			printf("press any key to continue\n");
			getchar();			
		}
	}
	return result;
}
void XaloyFlow::push(XaloyCase *xc)	{
	if(xc == NULL)
		return;
	xlist.push_back(xc);
}

XaloyFlow::~XaloyFlow()	{
	size_t sz = xlist.size();
	if(sz > 0)	{
		for(int i = 0; i < sz; i++)
			delete xlist[i];
		xlist.clear();
	}		
}
