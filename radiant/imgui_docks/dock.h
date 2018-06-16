#ifndef DOCK_H
#define DOCK_H

#include "../imgui/imgui_dock.h"

// creating a new dock: add it to imgui_api.cpp line 457, like: docks.push_back(new DockExplorer());
#ifdef __cplusplus

class Dock {
public:
	CDock *cdock = NULL;
	ImVec2 screenpos;
	ImVec2 size;
	virtual const char *label();
	virtual void imgui();
	virtual void OnLeftMouseDown(ImVec2 posLeftTop);
	virtual void OnLeftMouseUp(ImVec2 posLeftTop);
	virtual void OnRightMouseDown(ImVec2 posLeftTop);
	virtual void OnRightMouseUp(ImVec2 posLeftTop);
	virtual void OnMiddleMouseDown(ImVec2 posLeftTop);
	virtual void OnMiddleMouseUp(ImVec2 posLeftTop);
	virtual void OnMouseMove(ImVec2 posLeftTop);
	virtual void OnKeyDown(int key);
	virtual void OnMouseWheelUp(ImVec2 posLeftTop);
	virtual void OnMouseWheelDown(ImVec2 posLeftTop);

};

#endif

#endif