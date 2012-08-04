#ifndef XALOYFLOW_H
#define XALOYFLOW_H

#include <vector>
struct xtestflow;

#define GLOBAL_TEST xaloy::XaloyFlow::Global

/*	define the macro for using the xaloytester	*/
#define XALOY_TEST_MODULE(name)	 \
	class name:public XaloyFlow	{ \
	private: \
		static int __init; \
	public:\
		virtual void run(); \
	};\
	static int Init##name()	{\
		name *xcase = new name();	\
		GLOBAL_TEST->push(#name, (XaloyFlow*)xcase);	\
		return 0;	\
	}\
	int name::__init = Init##name(); \
	void name::run()

namespace xaloy
{	
	// define the xaloyflow
	class XaloyFlow
	{
	public:
		virtual void run() {}
		int execute(bool ispager = false);
		void push(const char *name, XaloyFlow *xcase);
		~XaloyFlow();
		static XaloyFlow *Global;
	protected:
		int _counter; 
		int _pass; 
	private:
		std::vector<xtestflow*> _flowList;		
	};
}

#endif
