XDEF example:
--------------------------------------------------------
	require("module")	-- use "require" if you want to test the extern library(created by c/c++ or Lua)
	return {
		{f = f1, mode = "EQ" case = {{"table", "table"},...}, expect = {number, "or string", "or table"}, cycle = 0, time = 0, space = 0},
		....
	}
	
	in this example, "f", "case", "result" are required.
	
	f		= the function you want to test
	mode	= the assert mode("EQ" = equal, "LS" = less, "LE" = less equal, "GT" = greater, "GE" = greater equal, "NE" = not equal)
	case	= test cases(parameters) of your function
	expect	= the result we expect, the elements cannot be table
	cycle	= how many cycles are needed in the performance test
	time	= the time limit of the performance test
	space	= the space limit of the performance test
	