--[[
		file	: xaloy-core-log.lua
		author	: drzunny
		updated	: 2012-07-08
--]]
require("xtools")
local xlog = {}

---------- helper function's declarations ----------
local debugger = {}
local check_result = function(rs)
	if type(rs) ~= "table" then
		print("test result must a table")
		return false
	end
	if #rs > 0 then
		for key,val in pairs(rs) do
			for i,v in ipairs(val) do
				if (v.success ~= true and v.success ~= false) or (type(v.msg) ~= "string" or string.len(v.msg) > 0)
				then
					print("error result data format")
					return false
				end
			end
		end
		return true
	else
		print("cannot use a empty result table")
		return false
	end
end
local output_html = [[
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>The Test Result of '{#testname}'</title>	
	<style>
		body{padding:10px;background-color:gray}
		.wrap{width:890px;margin-left: auto;margin-right: auto;background-color: white;padding:20px;box-shadow:0px 0px 20px white}
		h1{text-align: center; font-weight: bold; border-bottom: 1px solid gray;padding-bottom: 20px}
		dt{font-size:30px; font-weight: bold;margin-top:10px; margin-bottom: 10px}	
		span.s_icon{font-size:30px;color:green}
		span.f_icon{font-size:30px;color:red}
	</style>
</head>
<body>
	<div class="wrap">
		<h1>The Test Result of "{#testname}"</h1>
		<dl>
			{#content}
		</dl>
	</div>
</body>
</html>
]]

---------- xaloy's log module API define here ---------
xlog.write = function(text, no_time)
	local xenv = require("xaloy-core-env")
	local datetime = xenv.getdate()
	xenv = nil
	local path = _LOG_PATH_ .. datetime.fdate .. ".txt"
	local f = io.open(path, "a")
	if f == nil then
		collectgarbage("collect")
		os.execute("mkdir ".. _LOG_PATH_)
		os.execute("mkdir " .. _HTML_PATH_)
		f = io.open(path, "a")
	end	
	if no_time ~= true then
		f:write(datetime.logstr .. '  |  ')
	end
	f:write(text .. '\n')
	f:close()
end

xlog.debug = function(obj)
	debug("The object's value is:")
	local suc, msg = debugger.debug_data(obj)
	if suc ~= true then
		message("cannot debug this object:" .. msg)
		return
	end
	print(msg)
	msg = "[DEBUG]      | The object's value is:\n" .. msg	
	xlog.write(msg, true)	
end

xlog.fail = function(msg ,...)
	fail(string.format(msg, ...))
	xlog.write("[ERROR]    "..string.format(msg, ...))
end

xlog.ok = function(msg, ...)
	ok(string.format(msg, ...))
	xlog.write("[OK]       "..string.format(msg, ...))
end

xlog.message = function(msg, ...)
	message(string.format(msg, ...))	
	xlog.write("[MESSAGE]  "..string.format(msg, ...))
end

xlog.log = function(msg, ...)
	xprint(string.format(msg, ...))
	xlog.write(string.format(msg, ...))
end

xlog.html = function(name, result)
	local success, msg, html = debugger.gethtml(name,result)
	if success == true then
		if type(html) ~= "string" or string.len(html) < 1 then
			print("read html text fail");
			xlog.message("read html text fail");
			return
		end
		local path = _HTML_PATH_ .. name .. ".html"
		local f = io.open(path, "w")
		if f == nil then
			collectgarbage("collect")
			os.execute("mkdir ".. _LOG_PATH_)
			os.execute("mkdir " .. _HTML_PATH_)
			f = io.open(path, "w")
		end	
		f:write(html)
		f:close()
	else
		print(msg)
		xlog.message("cannot create the HTML file:" .. msg);
	end
end

---------- the implement of helper functions ----------
debugger.debug_data = function(obj)
	local t = type(obj)
	local dbg_rs
	if t == "nil" then
		return false, "cannot debug a nil object"
	end
	if t == "string" or t == "number" then
		return true, tostring(obj)
	elseif t == "table" then
		dbg_rs = debugger.debug_table(obj)
		return dbg_rs.success, dbg_rs.message
	else
		return false, string.format("this type '%s' is not supported in xaloy", t)
	end
end

debugger.debug_table = function(data, prefix)
	if prefix == nil then
		prefix = ''
	end	
	local val_str
	local dmsg  = ''
	-- print object
	for i, v in pairs(data) do				
		if type(v) == "number" then
			val_str = string.format("%s[%s] = %s", prefix, tostring(i), tostring(v))
			dmsg = dmsg .. val_str .. '\n'
		elseif type(v) == "string" then
			val_str = string.format("%s[%s] = \"%s\"", prefix, tostring(i), tostring(v))
			dmsg = dmsg .. val_str .. '\n'
		elseif type(v) == "table" then
			local rs = debugger.debug_table(v, prefix..'\t')
			if rs.success ~= true then
				return rs
			end
			dmsg = dmsg .. prefix .."["..i.."] elements:\n" .. rs.message
		else
			return {success = false, message = "in key:" .. i .. "  this type is not supported now"}
		end
	end
	return {success = true, message = dmsg}
end

debugger.gethtml = function(name,result)
	if name == nil or string.len(name) < 1 or not check_result(result) then		
		return false, "cannot use a empty test name or result"
	end
	local html = output_html
	local rs_str = ''
	--- set title of this test
	html = string.gsub(html, "{#testname}", name)
	--- write the result 
	for key, val in pairs(result) do
		rs_str = rs_str .. string.format("<dt>%s</dt>", key)
		for i,v in ipairs(val) do
			rs_str = rs_str .. string.format("<dd><span class='%s_icon'>●</span>　　'%s/dd>", (v.success and "s") or "f", v.msg)
		end
	end
	
	html = string.gsub(html, "{#content}", rs_str)	
	return true, "", html	
end

---------- return xlog module ----------
return xlog