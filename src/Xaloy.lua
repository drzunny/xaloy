local xbuild = require("xaloy-build")
local xparse = require("xaloy-parse")
local xio = require("xaloy-io")
local xtest = require("xaloy-testing")
local xhelper = require("xaloy-helper")

-- initalize the xaloy
xaloy = {}

---	create a x-test object
--- [n: test name]
xaloy.create = function(name)
	if xhelper == nil then
		print("xaloy has not initalized\n")
		return
	end
	if xhelper.check_hasempty(name) then
		print("cannot use a empty test name\n")
		return
	end
	if name ~= '' then
		local x = {}
		x.name = name
		return x
	end
end

---	compile the generate test code created by xdef file and library as lua extension.
--- [xobj: x-test object,  xdef: xdef file's path, ltype: library type, lpath: library path]
xaloy.build = function(xobj, xdef, ltype, lpath)
	if  not xhelper.check_xobject(xobj) then
		print("invalid xaloy test object\n")
		return
	end
	if xbuild == nil then
		print("cannot open xaloy-build module\n")
		return
	end	
	local gen_code = xbuild.generate(xdef, ltype, lpath)
	-- create a test cpp code		
	xio.writefile(gen_code);
	
	-- compile the generate code in a shared library
	local rs = xbuild.compile(filename, "shared");
	if not rs.success then
		print(rs.msg)		
	end
	xobj.cases = xparse.parse(xobj)
end

--- test by assert
--- [xobj: x-test object]
xaloy.assert = function(xobj, hidden_output)
	xobj.assert_result = {}
	if not xhelper.check_xobject(xobj) then
		print("invalid xaloy test object\n")
		return
	end
	for i,v in ipairs(xobj.cases) do
		xobj.assert_result[i] = xtest.assert_test(v);
	end
	if not hidden_output then
		xio.present(xobj.assert_result, nil)
	end
end

--- run a performance test
--- [xobj: x-test object]
xaloy.performance = function(xobj,hidden_output)	
	if not xhelper.check_xobject(xobj) then
		print("invalid xaloy test object\n")
		return
	end
	xobj.per_result = {}
	for i,v in ipairs(xobj.cases) do
		xobj.per_result[i] = xtest.performance_test(v);
	end
	if not hidden_output then
		xio.present(nil, xobj.per_result)
	end
end

---	run assert and performance test
--- [xobj: x-test object]
xaloy.test = function(xobj)
	if not xhelper.check_xobject(xobj) then
		print("invalid xaloy test object\n")
		return
	end
	xaloy.assert(xobj, true)
	xaloy.performance(xobj, true);
	xio.present(xobj.assert_result, xobj.performance_result)
end

--- release the x-object
--- [xobj: x-test object]
xaloy.drop = function(xobj)
	local cnt = collectgarbage("count")
	xobj = nil	
	collectgarbage("collect")
	cnt = cnt - collectgarbage("count")
	print(string.format("xaloy test object has been release.(release memory: %d)", cnt))
end


---------------		gtest extendsion module		------------------
xaloy.gtest = {}
xaloy.gtest.build = function(xobj, xdef, ltype, lpath)
	if xobj == nil or type(xobj) ~= "table" then
		print("invalid xaloy test object\n")
		return
	end
	if xbuild == nil then
		print("cannot open xaloy-build module\n")
		return
	end	
	local gtest_code = xbuild.gtest_generate(xdef, ltype, lpath)
	local code_file = string.format("gtest_%s.cc", xobj.name)
	xio.writefile(code_file, gtest_code)
	local rs = xbuild.compile(code_file, "shared")
	if rs.success then
		xobj.g_cases = xparse.gtest_parse(xobj)		--- load file according the testname
	else
		xobj.g_cases = nil
		print("cannot compile as a gtest module\n");
	end
end

xaloy.gtest.assert = function(xobj, hidden_output)
	if not xhelper.check_xobject(xobj) then
		print("invalid xaloy test object\n")
		return
	end
	xobj.g_assert_result = {}
	for i,v in ipairs(xobj.g_cases) do
		xobj.g_assert_result[i] = xtest.g_assert_test(v);
	end
	if not hidden_output then
		xio.g_present(xobj.g_assert_result, nil)
	end
end

xaloy.gtest.performance = function(xobj, hidden_output)
	if not xhelper.check_xobject(xobj) then
		print("invalid xaloy test object\n")
		return
	end
	xobj.g_per_result = {}
	for i,v in ipairs(xobj.g_cases) do
		xobj.g_per_result[i] = xtest.g_performance_test(v);
	end
	if not hidden_output then
		xio.g_present(nil, xobj.g_per_result)
	end
end

xaloy.gtest.test = function(xobj)
	if not xhelper.check_xobject(xobj) then
		print("invalid xaloy test object\n")
		return
	end
	xaloy.gtest.assert(xobj, true)
	xaloy.gtest.performance(xobj, true);
	xio.g_present(xobj.g_assert_result, xobj.g_per_result)
end

-------- return the xaloy object -------------
return xaloy