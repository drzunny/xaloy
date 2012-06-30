--[[
		file	: xaloy-core.lua
		author	: drzunny
		updated	: 2012-06-30
--]]

local xcore = {}

-- initalize the core modules
xcore.bind = require("xaloy-core-bind")
xcore.env = require("xaloy-core-env")
xcore.log = require("xaloy-core-log")

-- module's methods
xcore.parseObj = function(xdef)
end

xcore.parseFile = function(xdef)
end

xcore.createHTML = function(xcase, xresult)
end


-- xaloy's core methods
xcore.checkobj = function(xobj, mode)
	if type(xobj) ~= "table" then
		return false
	end
	if mode == "assert" then
		if xobj.result.ASSERT_RESULT ~= nil then
			xobj.result.ASSERT_RESULT = nil
		end
	elseif mode == "performance" then
		if xobj.result.PERFORMANCE_RESULT ~= nil then
			xobj.result.PERFORMANCE_RESULT = nil
		end
	end
	collectgarbage("collect")
	return true
end

xcore.assert = function(mode, xf, xcase, xresult)
end

xcore.performance = function(xf, cycle, lim_t, lim_s)
end

---------- return xaloy-core module ----------
return xcore