leftMousePressed()   = ccall( (:leftMousePressed  , libradiant), Bool, ())
rightMousePressed()  = ccall( (:rightMousePressed , libradiant), Bool, ())
middleMousePressed() = ccall( (:middleMousePressed, libradiant), Bool, ())
keyPressed(key) = ccall( (:keyPressed, libradiant), Bool, (Int,), key)