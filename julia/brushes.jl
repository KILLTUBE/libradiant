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


getActiveBrushes() = ccall(("getActiveBrushes", libradiant), Ptr{Brush}, ())