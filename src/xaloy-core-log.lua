--[[		file	: xaloy-core-log.lua		author	: drzunny		updated	: 2012-06-30--]]require("xtools")local xlog = {}-------------- helper functions' declaration --------------local printdata-------------- xaloy log module api --------------xlog.debug = function(obj)	xtools.debug("this object is:")	if type(obj) == "string" or type(obj) == "number" then		print(obj)	else		printdata(obj)	endendxlog.error = function(msg, ...)	xtools.error(string.format(msg, ...))	xtools.writelog("[ERROR]"..string.format(msg, ...))endxlog.ok = function(msg, ...)	xtools.ok(string.format(msg, ...))	xtools.writelog("[OK]"..string.format(msg, ...))endxlog.message = function()	xtools.message(string.format(msg, ...))		xtools.writelog("[MESSAGE]"..string.format(msg, ...))endxlog.log = function(msg, ...)	xtools.printline(string.format(msg, ...))	xtools.writelog(string.format(msg, ...))endxlog.html = function(xobj)end-------------- helper functions' implementations --------------printdata = function(data, prefix)	if prefix == nil then		prefix = ''	end		-- print object	for i, v in pairs(data) do						if type(v) == "string" or type(v) == "number" then			print(string.format("%s'%s' = %s", prefix, tostring(i), tostring(v))		else			print(prefix.."'"..i.."' elements:")			printdata(v, prefix..'\t')		end	endend--------- return xaloy's log module ----------return xlog