type Mouse end
mouse = Mouse()

function pos(mouse::Mouse)
	left = ccall( (:pos_left_mouse, libradiant), Int, ())
	top = ccall( (:pos_top_mouse, libradiant), Int, ())
	return Vec2(left, top)
end

if false
	mousepos = pos(mouse)
end