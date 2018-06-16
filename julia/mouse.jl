type Mouse end
mouse = Mouse()

function pos(mouse::Mouse)
	left = ccall( (:pos_left_mouse, libradiant), Int, ())
	top = ccall( (:pos_top_mouse, libradiant), Int, ())
	return Vec2(left, top)
end

pos!(mouse::Mouse, pos::Vec2) = ccall( (:SetCursorPos, "user32.dll"), Bool, (Int, Int), pos.x, pos.y)

if false
	mousepos = pos(mouse)
	pos!(mouse, mousepos + Vec2(12,34)) # 12 left, 34 down
end