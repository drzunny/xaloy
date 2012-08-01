--[[
		file	: xaloy-core-env.lua
		author	: drzunny
		updated	: 2012-06-30
--]]
local xenv = {}

--------------- xaloy-core-env's API ---------------
xenv.checkfile = function(path)
	local f = io.open(path)
	return f ~= nil
end

xenv.getdate = function()
	local _date = {}
	_date.year = os.date("%Y")
	_date.month = os.date("%m")
	_date.day = os.date("%d")
	_date.hour = os.date("%H")
	_date.min = os.date("%M")
	_date.sec = os.date("%S")
	_date.fdate = string.format("%s%s%s", _date.year, _date.month, _date.day)
	_date.dstr = string.format("%s%s%s%s%s%s", _date.year, _date.month, _date.day, _date.hour, _date.min, _date.sec)
	_date.logstr = string.format(
			"%s-%s-%s %s:%s:%s", 
			_date.year, _date.month, _date.day,
			_date.hour, _date.min, _date.sec
	)
	return _date	
end

xenv.searchcmd = function(cmd)
	local envpath = os.getenv("path")
	local idx = 1
	local pos = 0
	
	while string.find(envpath, ";", idx) ~= nil do
		pos = string.find(envpath, ";", idx)
		local tsrc = string.sub(envpath, idx, pos - 1)
		if xenv.checkfile(tsrc, cmd) == 1 then
			return true
		else
			idx = pos + 1
		end
	end	
	return false
end

xenv.timer = function(callback, cycle)
	local tick = os.clock()
	callback()
	tick = os.clock() - tick
	if type(cycle) == "number" and cycle > 0 then
		local calc = os.clock()
		for i = 1, cycle do
			callback()
		end
		calc = os.clock() - calc
		return tick, calc
	end
	return tick
end

xenv.init_envdic = function(name)
	os.execute("mkdir "..name)
end

--------- return xaloy's env module ----------
return xenv