--[[
		file	: xaloy-core-bind.lua
		author	: drzunny
		updated	: 2012-06-30		
--]]

local xbind = {}

---------- helper functions ----------
local getlibname
local createfile
local tmp_generation
local tmp_case

---------- xaloy-core-bind's API ----------
xbind.build = function(lib)
	local lib = ''
	local lname = ''
	local path = ''
	lib, path, lname = getlibname(lib)
end

xbind.load = function(xdef)
	return dofile(xdef)
end

---------- helper implement ----------
createfile = function(path, content)
end

getlibname = function(lib)
end

tmp_generation = [[
	require("%s")
	local testcase = {
		%s
	}
	
	return testcase
]]

tmp_case = [[
	{f = %s, case = {}, result = {}, cycle = 100, lim_t = nil, lim_s = nil, finished =false, success = false},
]]

---------- xaloy-core-bind return ----------
return xbind
