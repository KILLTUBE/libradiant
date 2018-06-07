hash(entity::AbstractEntity)::UInt64 = hash(entity.id)

type EntityString
	entity::AbstractEntity
	string::String
end
hash(this::EntityString)::UInt64 = xor(hash(this.entity), hash(this.string))
(==)(a::EntityString, b::EntityString)::Bool = hash(a) == hash(b)

if false
	hash(player1) == hash( Player(1) )
	hash( EntityString(Player(1), "hurr") )
end

type Thread
	task::Task
	reviveAt::Int32
	dead::Bool
	func::Function
	args::Tuple
	wait::Bool
	waitWhat::String
	waitEntity::AbstractEntity
	notifyArguments::Tuple
	endons::Set{EntityString}
	function Thread(func, args...)
		# dont call func directly, instead wrap it inside another function, which will yield back to maintask, once the func is done
		# also catch its errors and print it
		wrapperfunc = function()
			try
				func(args...)
			catch e
				log(console, "Thread failed: ", e)
			end
			yieldto(maintask, nothing)
		end
		thread = new( Task(wrapperfunc), Int32(0), false, func, args, false, "", level, (), Set{EntityString}() )
		push!(threads, thread)
		thread
	end
end

maintask = current_task()
starttime = time()
gametime() = Int32(round( (time() - starttime) * 1000 ))
current_thread = nothing
function runthreads()
	global maintask = current_task()
	global current_thread

	#for thread in threads
	i = 1
	while i <= length(threads)
		thread = threads[i]
		
		executeThread = false;
		
		if istaskdone( thread.task ) || thread.dead
			#print("task is done or marked dead, deleting it...\n")
			splice!(threads, i) # remove this thread while iterating over the threads... todo: make some linked list which allows this without duplicating arrays all time
			continue
		else
			i += 1
		end
		
		# always start a thread if it didnt run yet
		if ! istaskstarted( thread.task )
			executeThread = true
		end
		
		if thread.reviveAt <= gametime()
			executeThread = true
		end

		# waiting for a notify
		if thread.wait
			continue
		end

		if executeThread
			current_thread = thread
			ret = yieldto( thread.task )
			
			# 
			if ret === nothing
				thread.dead = true
				continue
			end
			
			# its either nothing or a Float32 atm
			waitseconds = ret			
			#print("waitseconds: " * string(waitseconds) * "\n")
			
			thread.reviveAt = Int32(round( gametime() + waitseconds * 1000 ))
			#print("thread.reviveAt: " * string(thread.reviveAt) * " now: " * string(gametime()) * "\n")
		else
			#timeleft = thread.reviveAt - gametime()
			#print("skip thread, executing in " * string(timeleft) * " milliseconds\n")
		end

	end
end

if !isdefined(:level)
	level = Thread2Entity(1022)
end

threads = Thread[]

killthreads() = global threads = Thread[]

threadwait(seconds) = yieldto(maintask, Float32(seconds))

# Thread( () -> TeddyShop("meh") )