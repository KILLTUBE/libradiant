#include "dock_all.h"
#include "../imgui_docks/dock_console.h"

DockAll::DockAll() {}

const char *DockAll::label() {
	return "All";
}
/*
findDock(name) = ccall( (:findDock, libradiant), Ptr{Int}, (Cstring,), name)
dockTop(from, to) = ccall( (:dockTop, libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockTab(from, to) = ccall( (:dockTab, libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)
dockRight(from, to) = ccall( (:dockRight, libradiant), Bool, (Ptr{Int}, Ptr{Int}), from, to)


all = findDock("All")
tex = findDock("Textures")
con = findDock("Console")
node = findDock("Node")

dockTop(all, C_NULL)

dockTab(con, all)
dockRight(node, all)
dockTab(tex, node)
*/
CCALL CDock *findDock(char *name) {
	for (CDock *dock : g_dock.m_docks) {
		if (strcmp(dock->label, name) == 0)
			return dock;
	}
	return NULL;
}
CDock *rootDock() {
	return g_dock.getRootDock();
}

bool undock(CDock *dock) {
	if (dock == NULL)
		return false;
	//if (dock->status != Status_::Status_Docked)
	//	return false;
	g_dock.doUndock(*dock);
	dock->status = Status_Float;
}

bool dockLeft(CDock *from, CDock *to) {
	if (from == NULL || to == NULL)
		return false;
	g_dock.doUndock(*from);
	from->status = Status_Float;
	g_dock.doDock(*from, to, Slot_::Slot_Left);
	from->status = Status_Docked;
	return true;
}
CCALL bool dockTop(CDock *from, CDock *to) {
	//if (from == NULL || to == NULL)
	//	return false;
	g_dock.doUndock(*from);
	from->status = Status_Float;
	g_dock.doDock(*from, to, Slot_::Slot_Top);
	from->status = Status_Docked;
	return true;
}
bool dockBottom(CDock *from, CDock *to) {
	if (from == NULL || to == NULL)
		return false;
	g_dock.doUndock(*from);
	from->status = Status_Float;
	g_dock.doDock(*from, to, Slot_::Slot_Bottom);
	from->status = Status_Docked;
	return true;
}
CCALL bool dockRight(CDock *from, CDock *to) {
	if (from == NULL || to == NULL)
		return false;
	g_dock.doUndock(*from);
	from->status = Status_Float;
	g_dock.doDock(*from, to, Slot_::Slot_Right);
	from->status = Status_Docked;
	return true;
}
CCALL bool dockTab(CDock *from, CDock *to) {
	if (from == NULL || to == NULL)
		return false;
	if (to->status != Status_::Status_Docked)
		return false;
	g_dock.doUndock(*from);
	from->status = Status_Float;
	g_dock.doDock(*from, to, Slot_::Slot_Tab);
	from->status = Status_::Status_Docked;
	return true;
}

namespace ImGui {
	////bool Enum(char *name, int enumCount, ...) {
	//bool Enum(char *name, char **names, int *values) {
	//	//va_list valist;
	//	//va_start(valist, enumCount);
	//	//
	//	//for(int i=0; i<enumCount; i++) {
	//	//	char *enumName = va_arg(valist, char *);
	//	//	int enumValue = va_arg(valist, int);
	//	//	ImGui::Text("enumName=%s enumValue=%d", enumName, enumValue);
	//	//}
	//	//va_end(valist);
	//
	//	return false;
	//}

	bool Enum(Status_ *status) {
        //return ImGui::Combo("Status", (int *)&status, "Status_Docked\0Status_Float\0Status_Drag\0\0");
		//int current_item = 1;
		char *names[] = {"Docked", "Float", "Drag"};
		int bla = *status;
		bool ret = ImGui::Combo("Status",  (int *)&bla, names, 3);
		if (ret) {
			*status = (Status_)bla;
		}
		//ImGui::SameLine();
		//ImGui::Text("aaaaaaaaaaaaaaaaaaaaa ret=%d bla=%d", (int)ret, bla);
		return ret;
	}

}

void alignTabsDefault() {
	// first make sure everything is undocked
	for (CDock *dock : g_dock.m_docks) {
	//	g_dock.doUndock(*dock);
	//	dock->status = Status_Float;
		if (dock->label[0] == 0)
			continue; // dont try to undock ghost docks
		undock(dock);
	}

	CDock *all = findDock("All");
	CDock *console = findDock("Console");
	CDock *node = findDock("Node");

	
	dockTop(all, NULL);
	
	
	dockBottom(console, all);
	dockRight(node, console);
	// dock all the rest to top
	for (CDock *dock : g_dock.m_docks) {
		//	strcpy(dock->location, "2"); // 1=left, 2=top, 3=bottom, 4=right
		//	dock->status = Status_::Status_Docked;
		//	g_dock.doDock(*dock, g_dock.getRootDock(), Slot_::Slot_Top);
		if (dock->status == Status_::Status_Docked)
			continue;

		dockTab(dock, all);
	}
	
	
	//dockRight(node, console);
	//
	//dockRight(node, console);


}

extern int setConsoleHeight;
void DockAll::imgui() {
	int i = 0;
	for (CDock *dock : g_dock.m_docks) {
		ImGui::PushID(dock);
		

		ImGui::Text("i=%d on=%d open=%d childs=%s,%s tabs=%s,%s parent=%s\n", i, 
					dock->active,
					dock->opened,
					dock->children[0] ? g_dock.m_docks[i]->children[0]->label : "None",
					dock->children[1] ? g_dock.m_docks[i]->children[1]->label : "None",
					dock->prev_tab    ? g_dock.m_docks[i]->prev_tab->label    : "None",
					dock->next_tab    ? g_dock.m_docks[i]->next_tab->label    : "None",
					dock->parent      ? g_dock.m_docks[i]->parent->label      : "None"
		);
		
		ImGui::PushItemWidth(80);

		ImGui::Enum(&dock->status);

		ImGui::SameLine();
		ImGui::DragFloat2("pos", (float *)&dock->pos);

		ImGui::SameLine();
		ImGui::DragFloat2("size", (float *)&dock->size);
		
		ImGui::SameLine();
		ImGui::InputText("label", dock->label, sizeof(dock->label));
		ImGui::SameLine();
		ImGui::InputText("location", dock->location, sizeof(dock->location));
		ImGui::PopItemWidth();
		ImGui::SameLine();
		if (ImGui::Button("Update Location")) {
			g_dock.tryDockToStoredLocation(*dock);
		}
		if (ImGui::Button("Undock")) {
			undock(dock);
		}
		if (ImGui::Button("dockLeft(dock, rootDock())")) {
			dockLeft(dock, rootDock());
		}

		ImGui::PopID();
		i++;
	}
	
	
	CDock *all = findDock("All");
	CDock *console = findDock("Console");
	CDock *node = findDock("Node");
		
	if (ImGui::Button("dockTop(all, rootDock());"))
		dockTop(all, rootDock());

	if (ImGui::Button("dockBottom(console, rootDock());"))
		dockBottom(console, rootDock());

	if (ImGui::Button("dockRight(node, console);"))
		dockRight(node, console);

	if (ImGui::Button("alignTabsDefault()")) {
		alignTabsDefault();
	}

	if (ImGui::Button("console->parent->size.y = 180")) {
		console->parent->size.y = 180;
	}
	
	if (ImGui::Button("dockTab(julia, all)")) {
		
		CDock *julia = findDock("Julia");
		CDock *all = findDock("All");
		dockTab(julia, all);
		

	}


	
	//CDock *all = findDock("All");
	//CDock *console = findDock("Console");
	//CDock *node = findDock("Node");

	if (ImGui::Button("dockTop(all, NULL);")) {
		dockTop(all, NULL);
	}
	
	if (ImGui::Button("dockBottom(console, all);")) {
	
		dockBottom(console, all);
	}
	if (ImGui::Button("dockRight(node, console);")) {
		dockRight(node, console);
	}

}
