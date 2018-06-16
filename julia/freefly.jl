
function getNewDir(camera::Camera)::Vec3
	newDir = Vec3()
	if keyPressed('W') newDir += forward(camera)  end
	if keyPressed('S') newDir += backward(camera) end
	if keyPressed('A') newDir += left(camera)     end
	if keyPressed('D') newDir += right(camera)    end
	if keyPressed('E') newDir += Vec3(0,0,1)      end
	if keyPressed('Q') newDir += Vec3(0,0,-1)     end
	if iszero(newDir)
		return newDir
	end
	return normalize( newDir )
end

function thread_freeFlyCamera()
	while rightMousePressed()
		#log(console, "dddwasd: ", keyPressed('W'), keyPressed('S'), keyPressed('A'), keyPressed('D'))
		newDir = getNewDir(camera) * cameraMoveSpeed
		pos!(camera, pos(camera) + newDir)
		threadwait(0.01)
	end
end

# 
# includes()

function startFreeFlyCamera()::Void

	Thread( thread_freeFlyCamera )


	nothing
end