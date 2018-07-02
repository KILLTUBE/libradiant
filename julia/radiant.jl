const libradiant = "C:\\msys64\\mingw64\\bin\\libradiant.dll";

juliasources = "C:/DATA/GtkRadiant/julia/"

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