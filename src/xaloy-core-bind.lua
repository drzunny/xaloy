--[[
		file	: xaloy-core-bind.lua
		author	: drzunny
		updated	: 2012-06-30		
--]]

local xbind = {}

---------- helper functions' for validating ----------
local check_empty
local check_case_expect
local check_case
local check_expect

---------- xaloy-core-bind's API ----------
xbind.parseObject = function(xdobj)
	-- check the xdef object(table)
	local xcase = {}	
	if xdobj ~= nil then
		-- check table's key
		for i, v in ipairs(xdobj) do
			local check_rs
			local check_msg
			check_rs, check_msg = check_empty(i,v)
			if check_rs == false then
				print(check_msg)
				xcase = nil
				collectgarbage("collect")
				return nil
			else
				check_rs, check_msg = check_case_expect(v.case, v.expect) 
				if check_rs ~= true then
					print(check_msg)
					xcase = nil
					collectgarbage("collect")
					return nil
				end
				xcase[i] = {
					f = v.f, mode = v.mode, case = v.case, expect = v.expect, 
					cycle = v.cycle, ltime = v.ltime, lspace = v.lspace, 
					finished = false, success = false, result = {}
				}
			end			
		end
		return xcase
	else
		print("cannot parse a empty xdef object ")
		return nil
	end
end

xbind.parseFile = function(xdef)
	local f = io.open(xdef)
	if f == nil then
		print("xdef file is not exist")
	end
	xdef = dofile(xdef)		
	return xbind.parseObject(xdef)
end

---------- helper functions implements ----------
check_empty = function(i, xcase)
	if xcase.f == nil or xcase.case == nil or xcase.expect == nil then
		local msg = 'index:' .. i .. '\n'
		msg = msg .. 'one of the require key was nil'
		return false, msg
	end
	return true
end

check_case_expect = function(case,expect)
	if #case ~= #expect then		
		return false, "The number between test cases and expected value is inconsistent"
	end
	for i, v in ipairs(case) do
		if type(v) ~= "table" then
			return false, "case element's type must be table"
		end		
	end
end

---------- xaloy-core-bind return ----------
return xbind
