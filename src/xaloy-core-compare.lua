--[[
		file	: xaloy-core-compare.lua
		author	: drzunny
		updated	: 2012-07-08
--]]

local xcompare = {}
-- declare the epsilon for compare
local __ep = 0.00005

---------- declare the helper functions ----------
local cmp_helpers = {}
local check_parameters
local tb_getlength

---------- define the xcompare's API ----------
xcompare.EQ = function(v1, v2)
	local valid, t1, t2 = check_parameters(v1, v2)
	if not valid then
		return false
	end
	if cmp_helpers[t1 .. "_cmp"] ~= nil then
		return cmp_helpers[t1 .. "_cmp"](v1,v2) == 0
	else
		print("this datatype '" .. t1 .."' is not supported in xaloy")
		return false
	end
end

xcompare.NE = function(v1, v2)
	return not xcompare.EQ(v1, v2)
end

xcompare.LS = function(v1, v2)
	local valid, t1, t2 = check_parameters(v1, v2)
	if not valid then
		return false
	end
	if cmp_helpers[t1 .. "_cmp"] ~= nil then
		return cmp_helpers[t1 .. "_cmp"](v1,v2) < 0
	else
		print("this datatype '" .. t1 .."' is not supported in xaloy")
		return false
	end
end

xcompare.LE = function(v1, v2)
	return xcompare.LS(v1,v2) or xcompare.EQ(v1, v2)
end

xcompare.GT = function(v1, v2)
	local valid, t1, t2 = check_parameters(v1, v2)
	if not valid then
		return false
	end
	if cmp_helpers[t1 .. "_cmp"] ~= nil then
		return cmp_helpers[t1 .. "_cmp"](v1,v2) > 0
	else
		print("this datatype '" .. t1 .."' is not supported in xaloy")
		return false
	end
end

xcompare.GE = function(v1, v2)
	return xcompare.GT(v1,v2) or xcompare.EQ(v1, v2)
end

---------- implement the helpers ----------
check_parameters = function(v1, v2)
	local t1 = type(v1)
	local t2 = type(v2)
	if t1 ~= t2 then
		return false, t1, t2
	elseif t1 ~= "number" and t1 ~= "string" and t1 ~= "table" then
		return false, t1, t2
	else
		return true, t1, t2
	end	
end

tb_getlength = function(t)
	local len = 0
	for i,_ in pairs(t) do
		len = len + 1
	end
	return len
end

cmp_helpers.number_cmp = function(v1, v2)
	if math.abs(v1 - v2) <= __ep then
		return 0
	end
	return (v1 - v2 > 0 and 1) or -1
end

cmp_helpers.string_cmp = function(v1, v2)
	if v1 == v2 then
		return 0
	end
	local len1 = string.len(v1)
	local len2 = string.len(v2)
	if len1 ~= len2 then
		return (len1 > len2 and 1) or -1
	end
	for i = 1, len1 do
		if string.byte(v1, i) ~= string.byte(v2, i) then
			return (string.byte(v1, i) > string.byte(v2, i) and 1) or -1
		end
	end
	return 0
end

cmp_helpers.table_cmp = function(v1, v2)
	local len1 = tb_getlength(v1)
	local len2 = tb_getlength(v2)	
	if len1 ~= len2 then
		return (len1 > len2 and 1) or -1
	end
	for i, v in pairs(v1) do 
		if v2[i] == nil then
			return 2
		end
		--- get the same key and its value to compare
		if type(v1[i]) ~= type(v2[i]) then
			return 2
		end
		local t = type(v1[i])	
		if t ~= "string" and t ~= "number" and t ~= "table" then
			print("'".. t .."' is not supported to compare")
			return 2
		end
		local cmp_rs = cmp_helpers[t .. "_cmp"](v1, v2)
		if cmp_rs ~= 0 then
			return cmp_rs
		end			
	end	
	return 0
end

---------- return the xcompare module ----------
return xcompare