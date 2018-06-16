camera_pointer_forward() = ccall( (:camera_forward, libradiant), Ptr{Vec3}, ())
camera_pointer_right()   = ccall( (:camera_right  , libradiant), Ptr{Vec3}, ())
camera_pointer_up()      = ccall( (:camera_up     , libradiant), Ptr{Vec3}, ())
camera_pointer_angles()  = ccall( (:camera_angles , libradiant), Ptr{Vec3}, ())
camera_pointer_pos()     = ccall( (:camera_origin , libradiant), Ptr{Vec3}, ())

type Camera end
camera = Camera()

forward( camera::Camera                  ) = unsafe_load(   camera_pointer_forward()          )
right(   camera::Camera                  ) = unsafe_load(   camera_pointer_right()            )
up(      camera::Camera                  ) = unsafe_load(   camera_pointer_up()               )
angles(  camera::Camera                  ) = unsafe_load(   camera_pointer_angles()           )
pos(     camera::Camera                  ) = unsafe_load(   camera_pointer_pos()              )

forward!(camera::Camera, newValue::Vec3  ) = unsafe_store!( camera_pointer_forward(), newValue)
right!(  camera::Camera, newValue::Vec3  ) = unsafe_store!( camera_pointer_right()  , newValue)
angles!( camera::Camera, newValue::Vec3  ) = unsafe_store!( camera_pointer_angles() , newValue)
pos!(    camera::Camera, newValue::Vec3  ) = unsafe_store!( camera_pointer_pos()    , newValue)

# kinda artificial ones
backward(camera) = forward(camera) * -1.0
left(    camera) = right(  camera) * -1.0
down(    camera) = up(     camera) * -1.0


if false
	pos!(camera, pos(camera) + forward(camera))
end
