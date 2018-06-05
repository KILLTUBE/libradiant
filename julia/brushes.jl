
# just to fix a julia bug, it cant redine samish types which contain pointers to itself for some reason
if !isdefined(:Face)

	struct Face
		next::Ptr{Face}
		prev::Ptr{Face}
		original::Ptr{Face}
		
		# ...
		to::Int
		be::Int
		done::Int
	end

	struct PatchMesh
		# ...
		to::Int
		be::Int
		done::Int

	end

	struct Entity
		prev::Ptr{Entity}
		next::Ptr{Entity}
		
		# ...
		to::Int
		be::Int
		done::Int
	end

	struct EPair
		next::Ptr{EPair}
		key::Ptr{Cchar}
		value::Ptr{Cchar}
	end

	struct Brush
		# links in active/selected
		prev::Ptr{Brush}
		next::Ptr{Brush}
		
		# links in entity
		oprev::Ptr{Brush}
		onext::Ptr{Brush}
		
		owner::Ptr{Entity}
		
		mins::Vec3
		maxs::Vec3
		
		brush_faces::Ptr{Face}
		
		bModelFailed::UInt8
		# curve brush extensions
		# all are derived from brush_faces
		patchBrush::UInt8
		hiddenBrush::UInt8
		
		
		pPatch::Ptr{PatchMesh}
		pUndoOwner::Ptr{Entity}
		
		undoId::Int32
		redoId::Int32
		ownerId::Int32 # entityId of the owner entity for undo
		
		# TTimo: this is not legal, we are not supposed to put UI toolkit dependant stuff in the interfaces
		# NOTE: the grouping stuff never worked, there is embryonary code everywhere though
		numberId::Int32
		itemOwner::Ptr{Void} # GtkCTreeNode* ?

		# brush primitive only
		epairs::Ptr{EPair}
	end
	
end

getActiveBrushes() = ccall(("getActiveBrushes", libradiant), Ptr{Brush}, ())
getSelectedBrushes() = ccall(("getSelectedBrushes", libradiant), Ptr{Brush}, ())
getFilteredBrushes() = ccall(("getFilteredBrushes", libradiant), Ptr{Brush}, ())

brush_create(min::Vec3, max::Vec3)::Void = ccall( (:ffi_brush_create, libradiant), Void, (Vec3, Vec3), min, max)

if false
	for i in 0:10
		for j in 0:20
			min = Vec3(i * 8, j * 8, 0)
			max = min + Vec3(8,8,8)
			brush_create(min, max)
		end
	end
end

function next(brush::Ptr{Brush})
	return brush[:next]
end

function prev(brush::Ptr{Brush})
	return brush[:prev]
end


# iterator implementation for brush lists

type BrushIterator
	current::Ptr{Brush}
end

function Base.start( brush::Ptr{Brush} )
	#log(console, "Base.start for ", brush)
	return BrushIterator(next(brush))
end

function Base.done( brush::Ptr{Brush}, it::BrushIterator)
	#log(console, "done")
	return brush == it.current
end

function Base.next(brush::Ptr{Brush},  it::BrushIterator)
	#log(console, "next>", brush)
	new_i = next( it.current )
	new_it = BrushIterator( new_i )
	return (new_i, new_it)
end

if false
	it = start( getActiveBrushes() )
	I = getActiveBrushes()
	next(next(I))
	 (i, it) = Base.next(it, I)
	done(I, it)
	next( getActiveBrushes() )

	for brush in getActiveBrushes()
		log(console, "loop", typeof(brush), brush)
	end
end

#####



