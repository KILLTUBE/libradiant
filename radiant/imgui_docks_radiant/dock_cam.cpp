#include "dock_cam.h"
#include "../imgui_docks/dock_console.h"

#include "../radiant/qe3.h"
#include "../radiant/mainframe.h"
//#include "../mainframe.h"

DockCam::DockCam() {}

const char *DockCam::label() {
	return "Cam";
}

extern MainFrame *mainframe_intance;

#include "dock_cam.h"
extern DockCam *dock_cam;

void rendercallback_cam(const ImDrawList* parent_list, const ImDrawCmd* cmd) {
	if (dock_cam->cdock->active && mainframe_intance && mainframe_intance->m_pCamWnd)
		mainframe_intance->m_pCamWnd->Render();
}

void DockCam::imgui() {
	auto size = ImGui::GetWindowSize();
	size -= ImVec2(16,16); // substract a bit so there is no overflow to right/bottom
	//ImGui::Text("pos %f %f size %f %f", pos.x, pos.y, size.x, size.y);
	auto &io = ImGui::GetIO();
	auto fullsize = io.DisplaySize;
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->m_nWidth = size.x;
		mainframe_intance->m_pCamWnd->m_nHeight = size.y;
		mainframe_intance->m_pCamWnd->m_Camera.width = size.x;
		mainframe_intance->m_pCamWnd->m_Camera.height = size.y;
		mainframe_intance->m_pCamWnd->viewport_left = screenpos.x;
		mainframe_intance->m_pCamWnd->viewport_bottom = fullsize.y - (screenpos.y + size.y);
	}

	ImDrawList *drawlist = ImGui::GetWindowDrawList();
	drawlist->AddCallback(rendercallback_cam, NULL);
}

guint32 getMouseFlags();

extern MainFrame *mainframe_intance;

// left mouse

void DockCam::OnLeftMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->OnLButtonDown(getMouseFlags(), left, top);
	}
}

void DockCam::OnLeftMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->OnLButtonUp(getMouseFlags(), left, top);
	}
}

// right mouse

void DockCam::OnRightMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->OnRButtonDown(getMouseFlags(), left, top);
	}
}

void DockCam::OnRightMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->OnRButtonUp(getMouseFlags(), left, top);
	}
}

// middle mouse

void DockCam::OnMiddleMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->OnMButtonDown(getMouseFlags(), left, top);
	}
}

void DockCam::OnMiddleMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->OnMButtonUp(getMouseFlags(), left, top);
	}
}

void DockCam::OnMouseMove(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnMouseMove %d %d\n", left, top);
	if (mainframe_intance && mainframe_intance->m_pCamWnd) {
		mainframe_intance->m_pCamWnd->OnMouseMove(getMouseFlags(), left, top);
	}
}

void DockCam::OnKeyDown(int key) {
	switch (key) {
		case VK_ESCAPE:
			mainframe_intance->OnSelectionDeselect();
		case 'W': // forward
		case 'S': // backward
		case 'A': // left
		case 'D': // right
		case 'Q': // down
		case 'E': // up
			// noops in C++, so I can script these in Julia via keyPressed('W') etc.
			break;
		default:
			mainframe_keypress(key);
			//imgui_log("DockXY::OnKeyDown(int key=%d)\n", key);
	}
}