--[[
		file	: xaloy-core-bind.lua
		author	: drzunny
		updated	: 2012-06-30		
--]]

local xbind = {}

---------- xaloy-core-bind's API ----------
xbind.parseLIB = function(lib)
	local _pLib  = require(lib)
	
end

xbind.parseFile = function(xdef)
	return dofile(xdef)
end

---------- xaloy-core-bind return ----------
return xbind
