#pragma once

#include "../imgui_docks/dock.h"
#include <string>
#include "../imgui/imgui_dock.h"

class DockCam : public Dock {
public:
	DockCam();
	virtual const char *label();
	virtual void imgui();
	virtual void OnLeftMouseDown(ImVec2 posLeftTop);
	virtual void OnLeftMouseUp(ImVec2 posLeftTop);
	virtual void OnRightMouseDown(ImVec2 posLeftTop);
	virtual void OnRightMouseUp(ImVec2 posLeftTop);
	virtual void OnMiddleMouseDown(ImVec2 posLeftTop);
	virtual void OnMiddleMouseUp(ImVec2 posLeftTop);
	virtual void OnMouseMove(ImVec2 posLeftTop);
	virtual void OnEscape();
};
