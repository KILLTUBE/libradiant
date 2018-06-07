julia_log(text) = ccall( ("imgui_log", libradiant), Int, (Cstring,), text)

abstract type AbstractConsole end
type Console <: AbstractConsole end
console = Console()

function log(this::AbstractConsole, msgs...)::Void
	for msg in msgs
		toprint = string(msg)
		julia_log(toprint)
		julia_log(" ")
		print(toprint, " ")
	end
	julia_log("\n")
	print("\n")
	nothing
end

# like log(), but prints a stack trace aswell
function error(this::AbstractConsole, msgs...)::Void
	for msg in msgs
		toprint = string(msg)
		julia_log(toprint)
		julia_log(" ")
		print(toprint, " ")
	end

	julia_log("\n")
	print("\n")


	julia_log("Stack Trace:\n")
	print("Stack Trace:\n")

	for func in stacktrace()
		log(console, func)
	end

	julia_log("\n")
	print("\n")
	nothing
end





if false
	log(console, "Spawned:", player1)
end
