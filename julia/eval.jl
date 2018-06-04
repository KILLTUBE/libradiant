function Core.eval(code::AbstractString)
	#return eval(parse(code)) # shitty substitute for linux, because jl_parse_eval_all isnt available for some reason
	bstr = String(code)
	ret = nothing
	try
		ret = ccall(:jl_parse_eval_all, Any, (Cstring, Cstring, Csize_t), "hurr.jl", bstr, sizeof(bstr))
	catch ex
		#print("Got error: " * string(ex.error.msg) * "\n")
		return ex
	end
	return ret	
end