#include "dock_textures.h"
#include "../imgui_docks/dock_console.h"

DockTextures::DockTextures() {}

const char *DockTextures::label() {
	return "Textures";
}

namespace ImGui {
	bool DragUShort(const char *str, unsigned short *val) {
		int tmp = *val;
		bool ret = DragInt(str, &tmp);
		*val = tmp;
		return ret;
	}
	bool DragShort(const char *str, short *val) {
		int tmp = *val;
		bool ret = DragInt(str, &tmp);
		*val = tmp;
		return ret;
	}
	bool DragChar(const char *str, signed char *val) {
		int tmp = *val;
		bool ret = DragInt(str, &tmp);
		*val = tmp;
		return ret;
	}
}

void texwnd_imgui();

DockTextures *dock_tex = NULL;
void DockTextures::imgui() {
	dock_tex = this;
	texwnd_imgui();
}

