data = {
	s = "string",
	n = 123,
	t = {t1 = 1, t2 = "stirng", t3 = {1,2,3}, t4 = {t11 = 1, t22 = "string"}, "one", 2},
	1,
	"string",
	{1,2,3},
	{k = 1, v = "string"}
}

testdata = {
	f1 = {
		{success=true, msg="function_a execute successfuly"},
		{success=true, msg="function_b execute successfuly"},
		{success=true, msg="function_c execute successfuly"},
		{success=false, msg="function_d cannot finished on time"}
	},
	f2 = {
		{success=true, msg="function_a execute successfuly"},
		{success=false, msg="function_b IN CASE:1, 2, 5 are not meet the expect values"},
		{success=false, msg="function_c execute cost too much memory"},
		{success=true, msg="function_d execute successfuly"}
	},
	ptest = {
		{success=true, msg="function_a execute successfuly"},
		{success=true, msg="function_b execute successfuly"},
		{success=true, msg="function_c execute successfuly"}
	}
}