findDock(name) = ccall( (:findDock, libradiant), Ptr{Int}, (Cstring,), name)
dockTop(from, to) = ccall( (:dockTop, libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockTab(from, to) = ccall( (:dockTab, libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockRight(from, to) = ccall( (:dockRight, libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)

function setupDocks()

	all = findDock("All")
	tex = findDock("Textures")
	con = findDock("Console")
	node = findDock("Node")
	xy = findDock("XY")
	z = findDock("Z")
	cam = findDock("Cam")

	dockTop(all, C_NULL)

	dockTab(con, all)
	dockRight(node, all)
	dockRight(xy, all)
	dockRight(z, all)
	dockRight(cam, all)
	dockTab(tex, node)
end