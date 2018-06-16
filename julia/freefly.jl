
function thread_freeFlyCamera()
	while rightMousePressed()
		#log(console, "dddwasd: ", keyPressed('W'), keyPressed('S'), keyPressed('A'), keyPressed('D'))

		if keyPressed('W')
			pos!(camera, pos(camera) + forward(camera))
		end
		if keyPressed('S')
			pos!(camera, pos(camera) + backward(camera))
		end

		threadwait(0.01)
	end
end

# cameraMoveSpeed
# includes()

function startFreeFlyCamera()::Void

	Thread( thread_freeFlyCamera )


	nothing
end