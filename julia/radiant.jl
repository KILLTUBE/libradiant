const libradiant = "C:\\msys64\\mingw64\\bin\\libradiant.dll";

juliasources = "C:/GtkRadiant/julia/"

include(juliasources * "console.jl")

function includes()::Void
	include(juliasources * "PointerHackery.jl/pointerhackery.jl")
	include(juliasources * "math.jl")
	include(juliasources * "brushes.jl")
	include(juliasources * "gtk.jl")
	include(juliasources * "eval.jl")
	include(juliasources * "eval_and_prettyprint.jl")
	include(juliasources * "callbacks/repl.jl")
	include(juliasources * "callbacks/oninit.jl")
	include(juliasources * "callbacks/wndproc.jl")
	include(juliasources * "functional.jl")
	include(juliasources * "entity.jl")
	include(juliasources * "threads.jl")
	include(juliasources * "docks.jl")
	include(juliasources * "mainloop.jl")
	include(juliasources * "camera.jl")
	include(juliasources * "imgui.jl")
	include(juliasources * "freefly.jl")
	include(juliasources * "preferences.jl")
	include(juliasources * "mouse.jl")
	include(juliasources * "shader.jl")
	include(juliasources * "fs.jl")
	nothing
end

function textures()
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "blood")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "common")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "concrete")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "custom")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "env")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "japan")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "kungtile")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "liquids")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "mymap")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "other")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "radiant")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "tools")
	ccall( (:Texture_ShowDirectory_by_path, libradiant), Void, (Cstring,), "window")
end

try
	includes()
	
	#Timer(function(timer)
	#	Base.invokelatest(mainloop)
	#end, 0, 1 / 20)
	
catch ex
	log(console, ex)
end

startRadiant() = ccall(("startRadiant", libradiant), Int32, ())

# start it up...
startRadiant()

# without blocking REPL and in the same thread, so we can mess around with GTK "from inside"
gtk_start_timer()