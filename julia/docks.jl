findDock(name) = ccall( (:findDock, libradiant), Ptr{Int}, (Cstring,), name)
dockTab(   from, to) = ccall( (:dockTab   , libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockLeft(  from, to) = ccall( (:dockLeft  , libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockRight( from, to) = ccall( (:dockRight , libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockTop(   from, to) = ccall( (:dockTop   , libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockBottom(from, to) = ccall( (:dockBottom, libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)

function setupDocks()

	all = findDock("All")
	tex = findDock("Textures")
	con = findDock("Console")
	node = findDock("Node")
	xy = findDock("XY")
	z = findDock("Z")
	cam = findDock("Cam")

	dockTop(all, C_NULL)

	dockTop(xy, all)
	dockRight(cam, xy)
	dockLeft(z, xy)
	
	dockTab(con, all)
	dockRight(node, all)
	
	dockTab(tex, node)
end