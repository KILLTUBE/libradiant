#include "dock_z.h"
#include "../imgui_docks/dock_console.h"

#include "../radiant/qe3.h"
#include "../radiant/mainframe.h"
//#include "../mainframe.h"

DockZ::DockZ() {}

const char *DockZ::label() {
	return "Z";
}


extern MainFrame *mainframe_intance;

void DockZ::imgui() {
	//auto pos = ImGui::GetWindowPos();
	screenpos = ImGui::GetCursorScreenPos();
	auto size = ImGui::GetWindowSize();
	size -= ImVec2(16,16); // substract a bit so there is no overflow to right/bottom
	//ImGui::Text("pos %f %f size %f %f", pos.x, pos.y, size.x, size.y);
	auto &io = ImGui::GetIO();
	auto fullsize = io.DisplaySize;
	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->m_nWidth = size.x;
		mainframe_intance->m_pZWnd->m_nHeight = size.y;
		mainframe_intance->m_pZWnd->viewport_left = screenpos.x;
		mainframe_intance->m_pZWnd->viewport_bottom = fullsize.y - (screenpos.y + size.y);
	}
}

guint32 getMouseFlags();

extern MainFrame *mainframe_intance;

// left mouse

void DockZ::OnLeftMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->OnLButtonDown(getMouseFlags(), left, top);
	}

}

void DockZ::OnLeftMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->OnLButtonUp(getMouseFlags(), left, top);
	}
}

// right mouse

void DockZ::OnRightMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->OnRButtonDown(getMouseFlags(), left, top);
	}
}

void DockZ::OnRightMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->OnRButtonUp(getMouseFlags(), left, top);
	}
}

// middle mouse

void DockZ::OnMiddleMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->OnMButtonDown(getMouseFlags(), left, top);
	}
}

void DockZ::OnMiddleMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->OnMButtonUp(getMouseFlags(), left, top);
	}
}


void DockZ::OnMouseMove(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnMouseMove %d %d\n", left, top);



	if (mainframe_intance && mainframe_intance->m_pZWnd) {
		mainframe_intance->m_pZWnd->OnMouseMove(getMouseFlags(), left, top);
	}
}


void DockZ::OnEscape() {
	mainframe_intance->OnSelectionDeselect();
}