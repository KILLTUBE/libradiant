
# somewhat like collect(10:20), but doesnt require a length() method, used like tovector(getActiveBrushes())
function tovector(iterator::T) where T
	list = Vector{T}()
	for i in iterator
		push!(list, i)
	end
	return list
end