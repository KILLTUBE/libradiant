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
	include(juliasources * "functional.jl")
	nothing
end

try
	includes()
catch ex
	log(console, ex)
end

startRadiant() = ccall(("startRadiant", libradiant), Int32, ())

# start it up...
startRadiant()

# without blocking REPL and in the same thread, so we can mess around with GTK "from inside"
gtk_start_timer()