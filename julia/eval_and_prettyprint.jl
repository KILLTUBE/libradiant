local ans

function eval_and_prettyprint(code::AbstractString)
	try
		ans = eval(code)
		log(console, ans)
	catch ex
		log(console, ex)
	end
	
	try
		usageCountDidChange(TextureBrowserView(0))
	end
end