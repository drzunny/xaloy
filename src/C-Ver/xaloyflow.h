#ifndef XALOYFLOW_H
#define XALOYFLOW_H

#include <vector>
struct xtestflow;

/*	define the macro for using the xaloytester	*/
#define XALOY_TEST_MODULE(name, statement)	\
	static int (name)##Init();	\
	class (name):public xaloy::XaloyFlow	{	\
	private:	\
		static int __init = (name)##Init();	\
	public:	\
		virtual void run()	{	\
			(statement)	\
		}		\
	};	\
	static int \
	(name)##Init()	{	\
		(name) *xcase = new (name)();	\
		GLOBAL_TEST.push(#name, xcase);	\
		return 0;	\
	}	\

namespace xaloy
{
	class XaloyFlow
	{
	public:
		virtual void run() {}
		int execute();
		void push(const char *name, XaloyFlow *test);
		~XaloyFlow();
	private:
		std::vector<xtestflow*> _flowList;	
	};
	
	// define a global variant for this test framework
	const XaloyFlow GLOBAL_TEST;
}

#endif