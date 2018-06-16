
function thread_freeFlyCamera()

	log(console, "rightMousePressed: ", rightMousePressed())

	while rightMousePressed()
		
	
		log(console, "dddwasd: ", keyPressed('W'), keyPressed('S'), keyPressed('A'), keyPressed('D'))
		threadwait(0.01)
	end
end

function startFreeFlyCamera()::Void

	Thread( thread_freeFlyCamera )


	nothing
end