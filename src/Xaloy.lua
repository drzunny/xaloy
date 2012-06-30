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
xaloy.init = function()
	-- check xaloy's status
end

xaloy.create = function(name)
	local xobject = {}
	xobject.name = name
	xobject.case = {}
	xobject.result = {}
	xobject.success = false
	xobject.finished = false
	return xobject
end

xaloy.bind= function(xobj, xdef)
	--if type(xdef) == "table" then
	--	xobj = xaloy.core.parseObject(xdef)
	--elseif type(xdef) == "string" then
	--	xobj = xaloy.core.parseFile(xdef)
	--end
	-- 检查后缀名，如果是library则先build后load
end

xaloy.assert = function(xobj)
	local idx = 1
	-- check object type
	if not xaloy.core.checkobj(xobj, "assert") then
		return
	end
	xobj.result.ASSERT_RESULT = {}
	for i, v in ipairs(xobj.case) do
		xobj.result.ASSERT_RESULT[idx] = xaloy.core.assert(v.mode, v.f, v.cases, v.rs)
	end	
end

xaloy.performance = function(xobj)
	local idx = 1
	-- check object type
	if not xaloy.core.checkobj(xobj, "performance")
		return
	end
	xobj.result.PERFORMANCE_RESULT = {}
	for i, v in ipairs(xobj.case) do
		xobj.result.PERFORMANCE_RESULT[idx] = xaloy.core.performance(v.f, v.cycle, v.lim_t, v.lim_s)
	end	
end

xaloy.printHTML = function(xobj)
	if xobj.finished ~= true then
		print("cannot create the HTML file because the xaloy test object is unfinished")
	else
		xaloy.core.createHTML(xobj.case, xobj.result)
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
xaloy.gtest = require("xaloy-gtest")
