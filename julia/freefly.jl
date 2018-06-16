
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
	oldmousepos = pos(mouse)
	while rightMousePressed()
		#log(console, "dddwasd: ", keyPressed('W'), keyPressed('S'), keyPressed('A'), keyPressed('D'))
		speed = cameraMoveSpeed
		if shiftButtonPressed()
			speed *= 10
		end
		if controlButtonPressed()
			speed /= 5
		end
		newDir = getNewDir(camera) * speed
		pos!(camera, pos(camera) + newDir)
		camangles = angles(camera)
		deltaMousePos = pos(mouse) - oldmousepos
		#log(console, "deltaMousePos:", deltaMousePos)
		deltaMousePos *= 1/5.333 # 1920 / 360 = 5.333
		angles!(camera, angles(camera) + Vec3( -deltaMousePos.y, -deltaMousePos.x, 0)) 
		pos!(mouse, oldmousepos) # reset mouse pos
		threadwait(0.01)
	end
end

# 
# includes()

function startFreeFlyCamera()::Void

	Thread( thread_freeFlyCamera )


	nothing
end