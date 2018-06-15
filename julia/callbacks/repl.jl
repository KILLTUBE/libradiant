# this file can be generated via:
# source = generateCallback("player_damage", Int32, Arg[Arg(Ptr{Int64}, "targ", Entity), Arg(Ptr{Int64}, "inflictor", Entity), Arg(Ptr{Int64}, "attacker", Entity), Arg(Ptr{Float32}, "dir", Vec3), Arg(Ptr{Float32}, "point", Vec3), Arg(Int32, "damage", nothing), Arg(Int32, "dflags", nothing), Arg(Int32, "mod", nothing)])
# file_put_contents("julia/callbacks/player_damage.jl", source)

#=
int (*callback_player_damage)(int *targ, int *inflictor, int *attacker, float *dir, float *point, int damage, int dflags, int mod) = NULL;
CCALL void set_callback_player_damage(int (*cb)(int *targ, int *inflictor, int *attacker, float *dir, float *point, int damage, int dflags, int mod)) {
        callback_player_damage = cb;
}

        // cb returns 1 == handled, return...
        // cb returns 0 == handled, but still do the normal C stuff
        if (callback_player_damage && callback_player_damage((int *)targ, (int *)inflictor, (int *)attacker, (float *)dir, (float *)point, (int)damage, (int)dflags, (int)mod)) {
                return 0;
        }
=#

function callback_repl(selection_from::Int, selection_to::Int, text::String)::Int
	#log(console, "repl $selection_from $selection_to $text")
	#log(console, "repl $selection_from $selection_to ")
	if selection_to < selection_from
		selection_to, selection_from = (selection_from, selection_to)
	end
	selectedCode = text[selection_from+1 : selection_to]
	if selection_from == selection_to
		selectedCode = text # execute everything then
	end
	#log(console, "Selected code: $selectedCode")
	eval_and_prettyprint(selectedCode)
	zero(Int)
end

function wrapper_callback_repl(selection_from::Int, selection_to::Int, text::Cstring)::Int
        ret = zero(Int)
        # whatever happens, make sure we return to C what it expects
        try
                # for some reason cfunction returns always the first compiled one, so make sure we call the latest function here
                ret = Int( Base.invokelatest(callback_repl, selection_from, selection_to, unsafe_string(text)) )
        catch ex
                #log(console, ex)
        end
        return ret
end

c_callback_repl = cfunction(wrapper_callback_repl, Int, (Int, Int, Cstring))

ccall(("set_callback_repl_node", libradiant), Void, (Ptr{Int64}, ), c_callback_repl)
