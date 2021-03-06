#include <stdio.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_dock.h"
#include "../imgui_docks/dock.h"
#include "imgui_radiant_default_docks.h"
#include "../imgui/imgui_api.h"

// custom docks
#include "../imgui_docks_radiant/dock_all.h"
#include "../imgui_docks_radiant/dock_textures.h"
#include "../imgui_docks_radiant/dock_xy.h"
#include "../imgui_docks_radiant/dock_z.h"
#include "../imgui_docks_radiant/dock_cam.h"

#include <list>
std::list<Dock *> imgui_quake_docks;

void alignTabsDefault();

CCALL int add_dock(Dock *dock) {
	imgui_quake_docks.push_back(dock);
	return 1;
}

CCALL void *imgui_get_current_dock();
CCALL bool dockRight(CDock *from, CDock *to);
CCALL CDock *findDock(char *name);

// extern DockXY *dock_xy;
// extern DockZ *dock_z;
// extern DockCam *dock_cam;
DockXY *dock_xy = NULL;
DockZ *dock_z = NULL;
DockCam *dock_cam = NULL;


CCALL Dock *getHoveredDock(ImVec2 screenpos) {
	int x = screenpos.x;
	int y = screenpos.y;
	for (Dock *dock : imgui_quake_docks) {
		if (dock->cdock->active == 0)
			continue;
		auto min = dock->screenpos;
		auto max = dock->screenpos + dock->size;
		int min_x = min.x;
		int min_y = min.y;
		int max_x = max.x;
		int max_y = max.y;
		if (
			x >= min_x && x <= max_x &&
			y >= min_y && y <= max_y
		)
		return dock;
	}
	return NULL;
}

CCALL int imgui_radiant_default_docks() {
	if (imgui_quake_docks.size() == 0) {
		// the last dock is seen first when pressing F2, so lets make it an useful one
		//imgui_quake_docks.push_back(new DockMapInfo());
		//imgui_quake_docks.push_back(new DockPerf());
		imgui_quake_docks.push_back(new DockAll());
		imgui_quake_docks.push_back(new DockTextures());
		dock_xy = new DockXY(); // just temporally, so i can test the OnLeftMouseDown etc. methods on this dock
		imgui_quake_docks.push_back(dock_xy);
		dock_z = new DockZ(); // just temporally, so i can test the OnLeftMouseDown etc. methods on this dock
		imgui_quake_docks.push_back(dock_z);
		dock_cam = new DockCam(); // just temporally, so i can test the OnLeftMouseDown etc. methods on this dock
		imgui_quake_docks.push_back(dock_cam);
		//imgui_quake_docks.push_back(new DockExplorer());
		//imgui_quake_docks.push_back(new DockAnims());
		//imgui_quake_docks.push_back(new DockSound());
		//imgui_quake_docks.push_back(new DockVars());
		//imgui_quake_docks.push_back(new DockQuakeShaders());
		//imgui_quake_docks.push_back(new DockHuds());
		//imgui_quake_docks.push_back(new DockEntity());
		//imgui_quake_docks.push_back(new DockConfigstrings());
#ifndef EMSCRIPTEN
		//imgui_quake_docks.push_back(new DockDuktape());
		//imgui_quake_docks.push_back(new DockOpsys( "opsystems/matmulpoint.opsys" ));
#endif
	}

	for (Dock *dock : imgui_quake_docks) {
		bool closed = true;
		if (BeginDock(dock->label(), &closed, 0, dock->cdock)) {
			if (dock->cdock == NULL)
				dock->cdock = (CDock *)imgui_get_current_dock();

			ImVec2 scrolling = ImVec2( ImGui::GetScrollX(), ImGui::GetScrollY() );
			dock->screenpos = ImGui::GetCursorScreenPos() + scrolling;
			dock->size = ImGui::GetWindowSize();
			dock->imgui();
		}
		EndDock();
	}


	return 1;

	// gotta make sure that the docks were at least drawn once, otherwise cant find them via string label
	static int first = 1;
	if (first == 2) {

		CDock *all = findDock("All");
		CDock *console = findDock("Console");
		CDock *node = findDock("Node");
		dockRight(node, console);


		// until i figure out how the dock code exactly works this must be good enough...
		// basically every step gets more successive to the aimed value (todo: rewrite dock system...)
		g_dock.getRootDock()->setPosSize(g_dock.getRootDock()->pos, g_dock.getRootDock()->size);
		console->parent->size.y = 180;
		g_dock.getRootDock()->setPosSize(g_dock.getRootDock()->pos, g_dock.getRootDock()->size);
		console->parent->size.y = 180;
		g_dock.getRootDock()->setPosSize(g_dock.getRootDock()->pos, g_dock.getRootDock()->size);
		console->parent->size.y = 180;

		first = 0;
	}
	if (first == 1) {
		alignTabsDefault();
		first = 2;
	}


	return 1;
}
