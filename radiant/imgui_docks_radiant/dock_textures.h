#pragma once

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockTextures : public Dock {
public:
	DockTextures();
	virtual const char *label();
	virtual void imgui();
};
