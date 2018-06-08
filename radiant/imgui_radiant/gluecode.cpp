#include "gluecode.h"

#if 0

// not exactly an imgui function lol
void Cvar_SetInt(cvar_t *cvar, int value) {
	Cvar_Set(cvar->name, va("%i", value));
}

namespace ImGui {

	// roses are red, qboolean is no bool
	bool Checkbox(char *label, qboolean *var) {
		bool tmp = *var;
		bool ret = ImGui::Checkbox(label, &tmp);
		*var = (qboolean) tmp;
		return ret;
	}

	bool CvarBool(cvar_t *cvar) {
		bool changed = ImGui::Checkbox(cvar->name, (qboolean *)&cvar->integer);
		//We don't have this in SP...
		/*if (cvar->description && cvar->description[0] && ImGui::IsItemHovered()) {
			ImGui::SetTooltip(cvar->description);
		}*/
		if (changed)
			Cvar_SetInt(cvar, cvar->integer);
		return changed;
	}
	bool CvarInt(cvar_t *cvar) {
		bool changed = ImGui::DragInt(cvar->name, &cvar->integer, /*cvar->dragspeed*/1.0, cvar->min, cvar->max);
		//We don't have this in SP...
		/*if (cvar->description && cvar->description[0] && ImGui::IsItemHovered()) {
			ImGui::SetTooltip(cvar->description);
		}*/
		if (changed)
			Cvar_SetInt(cvar, cvar->integer);
		return changed;
	}

	bool Cvar(cvar_t *cvar) {
		bool changed = false;
		//switch (cvar->typeinfo) {
		//	case CvarType_Bool:
		//		changed = ImGui::CvarBool(cvar);
		//		break;
		//
		//	case CvarType_Int:
		//		changed = ImGui::CvarInt(cvar);
		//		break;
		//
		//	default:
		//		ImGui::Text("Don't know how to show cvar->typeinfo=%d, please implement it for ImGui::Cvar()", cvar->typeinfo);
		//}
		ImGui::Text("Todo bool Cvar(cvar_t *cvar) again");
		return changed;
	}
}

#endif