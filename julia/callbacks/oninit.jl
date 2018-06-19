# this file can be generated via:
# source = generateCallback("player_damage", Int32, Arg[Arg(Ptr{Int64}, "targ", Entity), Arg(Ptr{Int64}, "inflictor", Entity), Arg(Ptr{Int64}, "attacker", Entity), Arg(Ptr{Float32}, "dir", Vec3), Arg(Ptr{Float32}, "point", Vec3), Arg(Int32, "damage", nothing), Arg(Int32, "dflags", nothing), Arg(Int32, "mod", nothing)])
# file_put_contents("julia/callbacks/player_damage.jl", source)

#=
int (*callback_oninit)() = NULL;
CCALL void set_callback_oninit(int (*cb)()) {
	callback_oninit = cb;
}

	if (callback_oninit)
		callback_oninit()
=#

function callback_oninit()::Int
        log(console, "oninit...")
		setupDocks()
		#textures()
		load_shaders()
		
        zero(Int)
end

function wrapper_callback_oninit()::Int
        ret = zero(Int)
        # whatever happens, make sure we return to C what it expects
        try
                # for some reason cfunction returns always the first compiled one, so make sure we call the latest function here
                ret = Int( Base.invokelatest(callback_oninit) )
        catch ex
                #log(console, ex)
        end
        return ret
end

c_callback_oninit = cfunction(wrapper_callback_oninit, Int, ())

ccall(("set_callback_oninit", libradiant), Void, (Ptr{Int64}, ), c_callback_oninit)
