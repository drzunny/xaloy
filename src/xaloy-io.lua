local xhelper = require("xaloy-helper")

local xaloy_io= {}

xaloy_io.writefile = function(file, data, mode)
	if xhelper.check_hasempty(file, data) then
		print("filename or data cannot be empty\n")
		return
	end
	local f = xhelper.get_writer(file, mode)
	if f ~= nil then
		f:write(data)
		f:close()
	end
end

xaloy_io.present = function(xcases)
end

xaloy_io.g_present = function(xcases)
end

xaloy_io.createhtml = function(xcases, path)
end

xaloy_io.g_createhtml = function(xcases, path)
end

-------------  return xaloy io module  --------------
return xaloy_io;