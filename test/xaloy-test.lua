--[[
		file	: xaloy-test.lua
		author	: drzunny
		updated	: 2012-07-08
--]]

local xtest = {}
local xcompare = require("xaloy-core-compare")
local xlog = require("xaloy-core-log")
local xenv = require("xaloy-core-env")

---------	helper functions ---------
local check_xobj
local expectTest

---------	xaloy-test's API functions ----------
xtest.assert = function(xobj)
	expectTest(xobj, true)
end

xtest.expect = function(xobj)
	expectTest(xobj, false)
end

xtest.performance = function(xobj,pre_run_case)
	local isValid, checkMsg = check_xobj(xobj)
	if not isValid then
		print(checkMsg)
		return false
	end
	--- use pre_run_case to pre-run the function for testing the functions can be return success in pre_run_case
	local pcase_suc = xobj.f(unpack(pre_run_case))
	if not pcase_suc then
		xlog.fail("the function cannot run successfully in pre_run_case")
		return false
	end
	local _, ticks = xenv.timer(function() xobj.f(unpack(pre_run_case)) end, cycle)
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
	if xobj.result[xobj.name] == nil then
		xobj.result[xobj.name] = {}
	end
	table.insert(xobj.result[xobj.name], {success = rs, msg = _msg })
end

xtest.printHTML = function(xobj)
	if type(xobj.result) ~= "table" then
		error("cannot use a '" .. type(xobj.result) .. "' for creating the html")
		return
	end
	xlog.html(name, xobj.result)
end

----------	helper function's implement	----------
function check_xobj(xobj)
end

function expectTest(xobj, isAssert)
	local isValid, checkMsg = check_xobj(xobj)
	if not isValid then
		print(checkMsg)
		return false
	end
	local allSuccess = true
	for i, v in ipairs(xobj.case) do
		local rs = xcompare[xobj.mode](xobj.f(unpack(v)), xobj.expect[i])
		if rs == false then
			local fail_msg = "Test:" .. xobj.name .."fail in the ".. xobj.mode .. "Test"
			xlog.error(fail_msg)
			if isAssert == true then
				assert(xcompare[xobj.mode](xobj.f(unpack(v)), xobj.expect[i]))
			else
				if xobj.result[xobj.name] == nil then
					xobj.result[xobj.name] = {}
				end
				table.insert(xobj.result[xobj.name], {success = false, msg = fail_msg})
			end
			break
		end
	end
	xlog.ok("Test '".. xobj.name .. "' run successfully")
	if xobj.result[xobj.name] == nil then
		xobj.result[xobj.name] = {}
	end
	table.insert(xobj.result[xobj.name], {success = false, msg = "Test '".. xobj.name .. "' run successfully"})
	return true
end

---------- return the xtest module ----------
return xtest