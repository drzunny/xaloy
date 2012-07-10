--[[
		file	: xaloy.lua
		author	: drzunny
		updated	: 2012-07-08
--]]

local xcore = require("xaloy-core")
local xtest = require("xaloy-test")

--	declare a global xaloy class
xaloy = {}
xaloy.prototype = {
	name = "", f = function() end, case = {}, 
	expect = {}, cycle = 0, ltime = 0,
	success = false,
	expect = function() end,
	assert = function() end,
	performance = function() end,
	expect_eq_str = function() end,
	assert_eq_str = function() end
}

-- set xaloy's metatable
xaloy.__metadata =  {}
xaloy.__metadata.__index = xaloy.prototype

-- create a test object
xaloy.new = function(name, case)
	local _xobj = {}
	setmetatable(_xobj, xaloy.__metadata)
	return _xobj
end

-- normal test function
xaloy.expect = function(name, mode, expect, actual)
	xcore.expect(name, mode ,actual, expect)
end

xaloy.assert = function(name, mode, expect, actual)
	xcore.assert(name, mode ,actual, expect)
end

xaloy.performance = function(name, f, cycle, ltime)
	xcore.performance(name, f, cycle, ltime)
end

xaloy.printHTML = function(name)
	xcore.html(name)
end
