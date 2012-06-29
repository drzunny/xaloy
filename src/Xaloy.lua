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
end

xaloy.create = function(name)
end

xaloy.build = function()
end

xaloy.assert = function(mode, m, cases, rs)
end

xaloy.performance = function(m, cases, cycle, lim_t, lim_s)
end

xaloy.release = function()
end

-------------------- xaloy's google test framework extension --------------------
xaloy.gtest = require("xaloy-gtest")
