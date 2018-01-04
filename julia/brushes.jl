struct Entity
	to::Int
	be::Int
	done::Int
end

struct Brush
	# links in active/selected
	prev::Ptr{Brush}
	next::Ptr{Brush}
	
	# links in entity
	oprev::Ptr{Brush}
	onext::Ptr{Brush}
	
	owner::Ptr{Entity}
	
	
end


getActiveBrushes() = ccall(("getActiveBrushes", libradiant), Ptr{Brush}, ())