leftMousePressed()     = ccall( (:leftMousePressed    , libradiant), Bool, ())
rightMousePressed()    = ccall( (:rightMousePressed   , libradiant), Bool, ())
middleMousePressed()   = ccall( (:middleMousePressed  , libradiant), Bool, ())
shiftButtonPressed()   = ccall( (:shiftButtonPressed  , libradiant), Bool, ())
altButtonPressed()     = ccall( (:altButtonPressed    , libradiant), Bool, ())
controlButtonPressed() = ccall( (:controlButtonPressed, libradiant), Bool, ())

keyPressed(key) = ccall( (:keyPressed, libradiant), Bool, (Int,), key)