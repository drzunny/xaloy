local xbuild = require("xaloy-build")
local xparse = require("xaloy-parse")
local xresult = require("xaloy-html")
local xtest = require("xaloy-testing")

-- initalize the xaloy
local xaloy = {}

---	create a x-test object
--- [n: test name]
xaloy.create = function(n)
	if n ~= '' then
		local x = {}
		x.name = n
		return x
	end
end

---	compile the generate test code created by xdef file and library as lua extension.
--- [xobj: x-test object,  xdef: xdef file's path, ltype: library type, lpath: library path]
xaloy.build = function(xobj, xdef, ltype, lpath)
	if xobj == nil or type(xobj) ~= "table" then
		print("invalid xaloy test object\n")
		return
	end
	if xbuild == nil then
		print("cannot open xaloy-build module\n")
		return
	end	
	local gen_code = xbuild.generate(xdef, ltype, lpath)
	-- create a test cpp code	
	local filename = xobj.name .. '_test_module.cc'
	xresult.writefile(filename, gen_code);
	
	-- compile the generate code in a shared library
	local build_ret = xbuild.compile(filename, "shared");
	if build_ret.success then
		xobj.cases = xparse.parse('lib'..xobj.name..'_test.xlib');		
	else
		print(build_ret.msg);
	end
end

--- test by assert
--- [xobj: x-test object]
xaloy.assert = function(xobj)
	xobj.asrt_test_result = {}
	for i,v in ipairs(xobj.cases) do
		xobj.asrt_test_result[i] = xtest.assert_test(v);
	end
end

--- run a performance test
--- [xobj: x-test object]
xaloy.performance = function(xobj)
	xobj.perf_test_result = {}
	for i,v in ipairs(xobj.cases) do
		xobj.perf_test_result[i] = xtest.performance_test(v);
	end
end

---	run assert and performance test
--- [xobj: x-test object]
xaloy.test = function(xobj)
	if xobj == nil or type(xobj) ~= "table" then
		print("invalid xaloy test object\n")
		return
	end
	xaloy.assert(xobj)
	xaloy.performance(xobj);
end

--- release the x-object
--- [xobj: x-test object]
xaloy.drop = function(xobj)
	local cnt = collectgarbage("count")
	xobj = nil	
	collectgarbage("collect")
	cnt = cnt - collectgarbage("count")
	print("xaloy test object release.(release memory: %d)", cnt)
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
	xresult.writefile(code_file, gtest_code)
	local build_ret = xbuild.compile(code_file, "shared")
	if build_ret.success then
		xobj.g_cases = xparse.gtest_parse("lib_gtest_"..xobj.name.."test.glib")		
	else
		xobj.g_cases = nil
		print("cannot compile as a gtest module\n");
	end
end

xaloy.gtest.assert = function(xobj)
end

xaloy.gtest.performance = function(xobj)
end

xaloy.gtest.test = function(xobj)
end

-------- return the xaloy object -------------
return xaloy