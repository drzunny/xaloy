--[[   
		file	: xaloy.lua
		author	: drzunny
		updated	: 2012-06-29
--]]

-- declare "xaloy" as a global varible
xaloy = {}

-------------------- get xaloy's core module --------------------
xaloy.core = require("xaloy-core")

-------------------- xaloy's API --------------------
xaloy.create = function(name)
	local xobject = {}
	xobject.name = name
	xobject.xcase = {}	
	xobject.result = {}
	xobject.success = false
	xobject.finished = false
	return xobject
end

xaloy.bind= function(xobj, xdef)
	if type(xdef) == "table" then
		xobj.xcase = xaloy.core.parseObject(xdef)
	elseif type(xdef) == "string" then
		xobj.xcase = xaloy.core.parseFile(xdef)
	end	
end

xaloy.assert = function(xobj)
	local idx = 1
	-- check object type
	if not xaloy.core.checkobj(xobj, "assert") then
		return
	end
	xobj.result.ASSERT_RESULT = {}
	for i, v in ipairs(xobj.xcase) do
		xobj.result.ASSERT_RESULT[idx] = xaloy.core.assert(v.name, v.mode, v.f, v.case, v.expect)
	end	
end

xaloy.performance = function(xobj, tmpcase)
	-- check object type
	if not xaloy.core.checkobj(xobj, "performance") then
		return
	end
	xobj.result.PERFORMANCE_RESULT = {}
	for i, v in ipairs(xobj.xcase) do
		xobj.result.PERFORMANCE_RESULT[i] = xaloy.core.performance(v.name, v.f, tmpcase, v.cycle, v.ltime, v.lspace)
	end	
end

xaloy.printHTML = function(xobj)
	if xobj.finished ~= true then
		print("cannot create the HTML file because the xaloy test object is unfinished")
	else
		xaloy.core.createHTML(xobj.result)
	end	
end

xaloy.releaseObj = function(xobj)
	xobj = nil
	local cnt = collectgarbage("count")	
	collectgarbage("collect")
	cnt = cnt - collectgarbage("count")
	print(string.format("release the xaloy test object, %d byte regain.", cnt));
end

-------------------- xaloy's google test framework extension --------------------
--xaloy.gtest = require("xaloy-gtest")
