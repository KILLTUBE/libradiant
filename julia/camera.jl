camera_pointer_forward() = ccall( (:camera_forward, libradiant), Ptr{Vec3}, ())
camera_pointer_pos()     = ccall( (:camera_origin , libradiant), Ptr{Vec3}, ())

type Camera end
camera = Camera()

function forward(camera::Camera)
	unsafe_load( camera_pointer_forward() )
end

function forward!(camera::Camera, newForward::Vec3)
	unsafe_store!( camera_pointer_forward(), newForward )
end

function pos(camera::Camera)
	unsafe_load( camera_pointer_pos() )
end

function pos!(camera::Camera, newPos::Vec3)
	unsafe_store!( camera_pointer_pos(), newPos )
end

if false
	pos!(camera, pos(camera) + forward(camera))
end
