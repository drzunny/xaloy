#ifndef XALOYFLOW_H
#define XALOYFLOW_H

#include <vector>
struct xtestflow;

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