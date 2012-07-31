#ifndef XALOYFLOW_H
#define XALOYFLOW_H

#include <vector>
struct xtestflow;

/*	define the macro for using the xaloytester	*/
#define XALOY_TEST_MODULE(name)	\
	static int (name)##Init();	\
	class (name)##:public xaloy::XaloyFlow	{	\
	private:	\
		static int __init = (name)##Init();	\
	public:	\
		virtual void run();	\
	};	\
	static int (name)##Init()	{	\
		(name) *xcase = new (name)##();	\
		xcase_block *block = (xcase_block*)malloc(sizeof(xcase_block));	\
		block->name = (#name);	\
		block->xcase = (XaloyFlow*)xcase;	\
		GLOBAL_TEST.push(block);	\
		return 0;	\
	}	\
	void (name)##::run()	\

namespace xaloy
{
	// predeclare the xaloy case struct
	struct xcase_block;	
	
	// define the xaloyflow
	class XaloyFlow
	{
	public:
		virtual void run() {}
		int execute();
		void push(xcase_block *block);
		~XaloyFlow();
	private:
		std::vector<xtestflow*> _flowList;	
	};
	
	// define the xaloy test case
	struct xcase_block	{
		const char *name;
		XaloyFlow *xcase;
	};
	
	// define a global variant for this test framework
	const XaloyFlow GLOBAL_TEST;
}

#endif