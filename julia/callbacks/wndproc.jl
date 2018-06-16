# this file can be generated via:
# source = generateCallback("wndproc", Int32, Arg[Arg(Ptr{Int64}, "targ", Entity), Arg(Ptr{Int64}, "inflictor", Entity), Arg(Ptr{Int64}, "attacker", Entity), Arg(Ptr{Float32}, "dir", Vec3), Arg(Ptr{Float32}, "point", Vec3), Arg(Int32, "damage", nothing), Arg(Int32, "dflags", nothing), Arg(Int32, "mod", nothing)])
# file_put_contents("julia/callbacks/wndproc.jl", source)

#=
int (*callback_wndproc)(unsigned int msg, unsigned int wParam, int lParam) = NULL;
CCALL void set_callback_wndproc(int (*cb)(unsigned int msg, unsigned int wParam, int lParam)) {
        callback_wndproc = cb;
}

        // cb returns 1 == handled, return...
        // cb returns 0 == handled, but still do the normal C stuff
        if (callback_wndproc && callback_wndproc(msg, wParam, lParam)) {
                return 0;
        }
=#

# according to https://stackoverflow.com/questions/6339793/wparam-and-lparam-parameters
# | OS             | WPARAM          | LPARAM        |
# |----------------|-----------------|---------------|
# | 16-bit Windows | 16-bit unsigned | 32-bit signed |
# | 32-bit Windows | 32-bit unsigned | 32-bit signed |
# | 64-bit Windows | 64-bit unsigned | 64-bit signed |
# 
# So I guess "UInt" and "Int" does the job for Julia wrapper, since:
# 32bit: sizeof(UInt) == 4
# 64bit: sizeof(UInt) == 8

# see here for list: https://wiki.winehq.org/List_Of_Windows_Messages
const WM_SETCURSOR = UInt(32)
const WM_RBUTTONDOWN = UInt(516)
const WM_PARENTNOTIFY = UInt(528)

function callback_wndproc(msg::UInt, wParam::UInt, lParam::Int)::Int
        #log(console, "repl $selection_from $selection_to $text")

		# im not exactly happy about this, but gtk seems to block all events when moving the mouse
		# but i need the events for runthreads(), so stuff like camera movement can be implemented via coroutines
		# once gtk is gone, just make it properly without such mainloop-in-wndproc hack
		Base.invokelatest(mainloop)
		
		if msg == WM_SETCURSOR
			#log(console, "WM_SETCURSOR")
			return 0
		end
		if msg == WM_RBUTTONDOWN
			#log(console, "WM_RBUTTONDOWN")
			return 0
		end
		if msg == WM_PARENTNOTIFY
			wLow = wParam & 0xffff
			#log(console, "WM_PARENTNOTIFY wLow=$wLow")
			
			if wLow == WM_RBUTTONDOWN
				#log(console, "WM_RBUTTONDOWN")
				startFreeFlyCamera()
			end
			
			return 0
		end

        ##log(console, "wndproc $msg $wParam $lParam")
		# selection_from and selection_to is currently hardcoded to 2 and 4, was just for testing
		#eval_and_prettyprint(text)
        zero(Int)
end

function wrapper_callback_wndproc(msg::UInt, wParam::UInt, lParam::Int)::Int
        ret = zero(Int)
        # whatever happens, make sure we return to C what it expects
        try
                # for some reason cfunction returns always the first compiled one, so make sure we call the latest function here
                ret = Int( Base.invokelatest(callback_wndproc, msg, wParam, lParam) )
        catch ex
                #log(console, ex)
        end
        return ret
end

c_callback_wndproc = cfunction(wrapper_callback_wndproc, Int, (UInt, UInt, Int))

ccall(("set_callback_wndproc", libradiant), Void, (Ptr{Int64}, ), c_callback_wndproc)