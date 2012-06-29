--[[   
		file	: xaloy.lua
		author	: drzunny
		updated	: 2012-06-29
--]]

-- declare "xaloy" as a global varible
xaloy = {}

-------------------- get xaloy's module --------------------
xaloy.core = require("xaloy-core")

-------------------- xaloy's API --------------------
xaloy.init = function()
	-- check xaloy's status
end

xaloy.create = function(name)
end

xaloy.build = function(xdef)
end

xaloy.assert = function(mode, m, cases, rs)
end

xaloy.performance = function(m, cases, cycle, lim_t, lim_s)
end

xaloy.release = function(xobj)
	xobj = nil
	local cnt = collectgarbage("count")	
	collectgarbage("collect")
	cnt = cnt - collectgarbage("count")
	print(string.format("release the xaloy test object, %d byte regain.", cnt));
end

-------------------- xaloy's google test framework extension --------------------
xaloy.gtest = require("xaloy-gtest")
