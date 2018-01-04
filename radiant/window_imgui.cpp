#include "stdafx.h"
#include "window_imgui.h"

WindowImGui::WindowImGui () : GLWindow( FALSE ){
}

WindowImGui::~WindowImGui(){
}

void WindowImGui::OnCreate(){
	//g_qeglobals_gui.d_z = m_pWidget;

	if ( !MakeCurrent() ) {
		Error( "wglMakeCurrent in WindowImGui::OnCreate failed" );
	}
}

void WindowImGui::OnLButtonDown( guint32 nFlags, int pointx, int pointy ){
	SetFocus();
	SetCapture();
	Z_MouseDown( pointx, m_pWidget->allocation.height - 1 - pointy, nFlags );
}

void WindowImGui::OnMButtonDown( guint32 nFlags, int pointx, int pointy ){
	SetFocus();
	SetCapture();
	Z_MouseDown( pointx, m_pWidget->allocation.height - 1 - pointy, nFlags );
}

void WindowImGui::OnRButtonDown( guint32 nFlags, int pointx, int pointy ){
	SetFocus();
	SetCapture();
	Z_MouseDown( pointx, m_pWidget->allocation.height - 1 - pointy, nFlags );
}

void WindowImGui::OnLButtonUp( guint32 nFlags, int pointx, int pointy ){
	Z_MouseUp( pointx, m_pWidget->allocation.height - 1 - pointy, nFlags );
	ReleaseCapture();
}

void WindowImGui::OnMButtonUp( guint32 nFlags, int pointx, int pointy ){
	Z_MouseUp( pointx, m_pWidget->allocation.height - 1 - pointy, nFlags );
	ReleaseCapture();
}

void WindowImGui::OnRButtonUp( guint32 nFlags, int pointx, int pointy ){
	Z_MouseUp( pointx, m_pWidget->allocation.height - 1 - pointy, nFlags );
	ReleaseCapture();
}

void WindowImGui::OnMouseMove( guint32 nFlags, int pointx, int pointy ){
	float fz = z.origin[2] + ( ( m_pWidget->allocation.height - 1 - pointy ) - ( z.height / 2 ) ) / z.scale;
	fz = floor( fz / g_qeglobals.d_gridsize + 0.5 ) * g_qeglobals.d_gridsize;
	CString strStatus;
	strStatus.Format( "Z:: %.1f", fz );
	g_pParentWnd->SetStatusText( 1, strStatus );
	Z_MouseMoved( pointx, m_pWidget->allocation.height - 1 - pointy, nFlags );
}

void WindowImGui::OnExpose(){
	if ( !MakeCurrent() ) {
		Sys_FPrintf( SYS_ERR, "ERROR: wglMakeCurrent failed..\n " );
		Sys_Printf( "Please restart Radiant if the Z view is not working\n" );
	}
	else
	{
		QE_CheckOpenGLForErrors();
		Z_Draw();
		QE_CheckOpenGLForErrors();
		SwapBuffers();
	}
}

void WindowImGui::OnSize( int cx, int cy ){
	z.width = cx;
	z.height = cy;
	if ( z.width < 10 ) {
		z.width = 10;
	}
	if ( z.height < 10 ) {
		z.height = 10;
	}
	RedrawWindow();
}
