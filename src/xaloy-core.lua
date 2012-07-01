--[[
		file	: xaloy-core.lua
		author	: drzunny
		updated	: 2012-06-30
--]]

local xcore = {}
local op_reference = {EQ ="EQ", NE = "NE", LS = "LS", LE = "LE", GT = "GT", GE = "GE"}
-- initalize the core modules
xcore.env = require("xaloy-core-env")
xcore.bind = require("xaloy-core-bind")
xcore.log = require("xaloy-core-log")
xcore.cmp = require("xaloy-core-compare")

-- module's methods
xcore.parseObject = function(xdef)
	return xcore.bind.parseObject(xdef)
end

xcore.parseFile= function(xdef)
	return xcore.bind.parseFile(xdef)
end

xcore.createHTML = function(result)
	if xresult == nil then 
		xcore.log.message("cannot create the html file, because of the result is nil")
		return
	end
	xcore.log.html(result)
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

xcore.assert = function(name, mode, xf, case, expect)
	mode = string.upper(mode)
	local op = op_reference[mode]
	local idx = ''
	local msg
	if op == nil then
		xcore.log.message("undefined operation")
		return nil
	end	
	for i, v in ipairs(case) do		
		local cmp_rs = nil	
		cmp_rs = xcore.cmp[op](xf(unpack(v)), expect[i])	
		
		if cmp_rs ~= true then
			idx = idx .. i .. ","
		end		
	end
	
	if string.len(idx) > 0 then
		idx = string.sub(idx, 0, string.len(idx) - 1)
		msg = string.format("'" .. name .."' Assert Fail.    (MODE:%s, Fail Test case Index:%s)", mode, idx)
		xcore.log.error(msg)
		return {tname = name, success = false, message = msg}
	else
		msg = string.format("'" .. name .."' Assert Success. (MODE:%s)", mode)
		xcore.log.ok(msg)		
		return {tname = name, success = true, message = msg}
	end	
end

xcore.performance = function(name, xf, case, cycle, ltime, lspace)
	local msg
	if type(case) ~= "table" then
		msg = "case must be a table"
		xcore.log.error(msg)
		return {tname = name, success = false, message = msg}
	end
	local cost = xcore.env.timer(
		function()
			for i = 1, cycle do
				xf(unpack(case))
			end
		end
	)
	-- if no limits
	if ltime == nil and lspace == nil then
		msg = string.format("function:%s   cost time:%d", name, cost)
		xcore.log.ok(msg)
		return {tname = name, success = true, message = msg}		
	end
	
	if type(ltime) == "number" then
		if cost <= ltime then
			msg = string.format("function:%s   limit time:%d   cost time:%d, PASS", name, ltime, cost)
			xcore.log.ok(msg)
			return {tname = name, success = true, message = msg}	
		else
			msg = string.format("function:%s   limit time:%d   cost time:%d, FAIL", name, ltime, cost)
			xcore.log.error(msg)
			return {tname = name, success = false, message = msg}	
		end
	end	
end

---------- return xaloy-core module ----------
return xcore