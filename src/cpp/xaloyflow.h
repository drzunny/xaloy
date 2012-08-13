#ifndef XALOYFLOW_H
#define XALOYFLOW_H

#include <stddef.h>
#include <vector>

/*	define the macro for using the xaloytester	*/
#define XALOY_TEST_MODULE(name)	 \
	class name:public XaloyCase	{ \
	private: \
		static int __init; \
	public:\
		virtual void run(); \
		name(); \
	};\
	static int Init##name()	{\
		name *xcase = new name();	\
		xcase->cname = #name; \
		G_XALOY.push((XaloyCase*)xcase);	\
		return 0;	\
	}\
	int name::__init = Init##name(); \
	name::name() { counter = 0; pass = 0; } \
	void name::run()

namespace xaloy
{	
	// a test case object
	class XaloyCase
	{
	public :
		virtual void run() {cname = NULL; counter = 0; pass = 0;}
		const char *cname;
		size_t counter;
		size_t pass;
	};
	
	// define the xaloyflow
	class XaloyFlow
	{
	public :
		int execute(bool ispager = false);
		void push(XaloyCase *xc);
		~XaloyFlow();
	private:
		std::vector<XaloyCase*> xlist;
	};
}

#endif
