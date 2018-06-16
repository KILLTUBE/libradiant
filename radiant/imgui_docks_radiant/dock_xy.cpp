#include "dock_xy.h"
#include "../imgui_docks/dock_console.h"

#include "../radiant/qe3.h"
#include "../radiant/mainframe.h"
//#include "../mainframe.h"

DockXY::DockXY() {}

const char *DockXY::label() {
	return "XY";
}


extern MainFrame *mainframe_intance;

void DockXY::imgui() {
	//auto pos = ImGui::GetWindowPos();
	
	auto size = ImGui::GetWindowSize();
	size -= ImVec2(16,16); // substract a bit so there is no overflow to right/bottom
	//ImGui::Text("pos %f %f size %f %f", pos.x, pos.y, size.x, size.y);

	auto &io = ImGui::GetIO();
	auto fullsize = io.DisplaySize;


	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->m_nWidth = size.x;
		mainframe_intance->m_pXYWnd->m_nHeight = size.y;
		mainframe_intance->m_pXYWnd->viewport_left = screenpos.x;
		mainframe_intance->m_pXYWnd->viewport_bottom = fullsize.y - (screenpos.y + size.y);
	}
}

guint32 getMouseFlags() {
	guint32 flags = 0;
	if (ImGui::IsMouseDown(0))
		flags |= MK_LBUTTON;
	if (ImGui::IsMouseDown(1))
		flags |= MK_RBUTTON;
	if (ImGui::IsMouseDown(2))
		flags |= MK_MBUTTON;
	ImGuiIO& io = ImGui::GetIO();
	if (io.KeyShift)
		flags |= MK_SHIFT;
	if (io.KeyCtrl)
		flags |= MK_CONTROL;
	return flags;
}

extern MainFrame *mainframe_intance;

// left mouse

void DockXY::OnLeftMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnLButtonDown(getMouseFlags(), left, top);
	}

}

void DockXY::OnLeftMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnLButtonUp(getMouseFlags(), left, top);
	}
}

// right mouse

void DockXY::OnRightMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnRButtonDown(getMouseFlags(), left, top);
	}
}

void DockXY::OnRightMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnRButtonUp(getMouseFlags(), left, top);
	}
}

// middle mouse

void DockXY::OnMiddleMouseDown(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseDown %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnMButtonDown(getMouseFlags(), left, top);
	}
}

void DockXY::OnMiddleMouseUp(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnLeftMouseUp %d %d\n", left, top);

	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnMButtonUp(getMouseFlags(), left, top);
	}
}


void DockXY::OnMouseMove(ImVec2 posLeftTop) {
	int left = posLeftTop.x;
	int top = posLeftTop.y;
	//imgui_log("DockXY::OnMouseMove %d %d\n", left, top);



	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnMouseMove(getMouseFlags(), left, top);
	}
}

void DockXY::OnKeyDown(int key) {
	switch (key) {
		case VK_ESCAPE:
			mainframe_intance->OnSelectionDeselect();
		default:
			mainframe_keypress(key);
			//imgui_log("DockXY::OnKeyDown(int key=%d)\n", key);
	}
}

void DockXY::OnMouseWheelUp(ImVec2 posLeftTop) {
	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnMouseWheel(true, posLeftTop.x, posLeftTop.y);
	}
}

void DockXY::OnMouseWheelDown(ImVec2 posLeftTop) {
	if (mainframe_intance && mainframe_intance->m_pXYWnd) {
		mainframe_intance->m_pXYWnd->OnMouseWheel(false, posLeftTop.x, posLeftTop.y);
	}
}
