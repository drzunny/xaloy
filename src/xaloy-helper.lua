local helper = {}

-- check xaloy test object is valid
helper.check_xobject = function(xobj)
	if type(xobj) ~= "table" then
		return false
	else
		return true
	end
end

-- check empty string
helper.check_hasempty = function(...)
	for i, v in ipairs({...}) do
		if v==nil then
			return true
		end
		local str = string.gsub(v, "^%s*(%S*)", "%1")
		str = string.gsub(str, "(%S*)%s*$", "%1")		
		if string.len(str) == 0 then
			return true
		end
	end
	return false
end


--------------- helper finish  ---------------
return helper