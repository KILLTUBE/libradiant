#include "../ccall/ccall.h"
#include "../imgui_docks/dock.h"

CCALL int add_dock(Dock *dock);
CCALL int imgui_radiant_default_docks();
CCALL Dock *getHoveredDock(ImVec2 screenpos);