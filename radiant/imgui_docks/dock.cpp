#include "dock.h"
#include "../imgui/include_imgui.h"

// creating a new dock: add it to imgui_api.cpp line 457, like: docks.push_back(new DockExplorer());

const char *Dock::label() {
	return "implement Dock::label()";
}

void Dock::imgui() {
	ImGui::Button("implement Dock::imgui()");
}

void Dock::OnLeftMouseDown(ImVec2 posLeftTop) {}
void Dock::OnLeftMouseUp(ImVec2 posLeftTop) {}
void Dock::OnRightMouseDown(ImVec2 posLeftTop) {}
void Dock::OnRightMouseUp(ImVec2 posLeftTop) {}
void Dock::OnMiddleMouseDown(ImVec2 posLeftTop) {}
void Dock::OnMiddleMouseUp(ImVec2 posLeftTop) {}
void Dock::OnMouseMove(ImVec2 posLeftTop) {}
void Dock::OnKeyDown(int key) {}