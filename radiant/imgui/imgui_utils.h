#ifndef IMGUI_UTILS
#define IMGUI_UTILS


namespace ImGui {

	void DragVector3(float *vec3);
	void DragMatrix3x3(float mat[3][3]);
	void DragMatrix3x4(char *text, float mat[3][4]);
}

#endif