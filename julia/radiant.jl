const libradiant = "C:\\msys64\\mingw64\\bin\\libradiant.dll";

juliasources = "C:/GtkRadiant/julia/"

include(juliasources * "PointerHackery.jl/pointerhackery.jl")
include(juliasources * "brushes.jl")
include(juliasources * "gtk.jl")

startRadiant() = ccall(("startRadiant", libradiant), Int32, ())

# start it up...
startRadiant()

# without blocking REPL and in the same thread, so we can mess around with GTK "from inside"
gtk_start_timer()