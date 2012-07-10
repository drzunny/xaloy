--[[
		file	: xaloy-core.lua
		author	: drzunny
		updated	: 2012-07-08
--]]

local xcmp = require("xaloy-core-compare")
local xlog = require("xaloy-core-log")
local xenv = require("xaloy-core-env")
local xcore = {}

-- to save the test result
xcore.result = {}

-- clear the results
xcore.clear = function()
	xcore.result = {}
	collectgarbage("collect")
end

xcore.assert = function(name, mode , actual, expect)
	local rs = xcore.expect(name, mode, actual, expect)
	if rs == false then
		error("In case:'".. name .."' assert fail")		
	end
end

xcore.expect = function(name, mode , actual, expect)
	mode = string.upper(mode)
	if type(name) ~= "string" or string.len(name) < 1 then
		error("parameter 'name' must be a string")
		return false
	end
	if xcmp[mode] == nil then
		error("The test mode:'" .. mode .."' is not exist")
		return false
	end
	local cmp_rs = xcmp[mode](actual, expect)
	-- chech the test case is exist in global result
	if xcore.result[name] == nil then
		xcore.result[name] = {}
	end
	if cmp_rs == true then
		test_msg = "Case '" .. name .. "' run successfuly"
		xlog.ok(test_msg)		
	else
		test_msg = "Case '" .. name .. "' has error"
		xlog.fail(test_msg)				
	end	
	table.insert(xcore.result[name], {success = cmp_rs, msg = test_msg })
	return cmp_rs
end

xcore.performance = function(name, f, cycle, ltime)
	local _, ticks = xenv.timer(f, cycle)
	local rs
	local _msg
	if type(ltime) == "number" and ltime > 0 then
		rs = xcmp.LE(ticks, ltime)
		if rs == true then
			_msg = string.format("Case :'%s' execute %d cycles cost: %f ms, less than %f ms", 
					name, cycle, 
					ticks/1000,  ltime)
			xlog.ok(_msg)
			return
		else
			_msg = string.format("Case :'%s' execute %d cycles cost: %f ms, slower than %f ms", 
					name, cycle, 
					ticks/1000,  ltime)
			xlog.fail(_msg)
		end		
	else
		rs = true
		_msg = string.format("Case :'%s' execute %d cycles cost: %f ms", name, cycle, ticks/1000)
		xlog.ok(_msg)
	end	
	if xcore.result[name] == nil then
		xcore.result[name] = {}
	end
	table.insert(xcore.result[name], {success = rs, msg = _msg })
end

xcore.html = function(name)
	if type(xcore.result) ~= "table" then
		error("cannot use a '" .. type(xcore.result) .. "' for creating the html")
		return
	end
	xlog.html(name, xcore.result)
end

---------- return the xcore module ----------
return xcore