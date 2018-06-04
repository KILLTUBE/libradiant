
//#include "../duktape/js_stuff.h"
#include "../radiant/qe3.h"
#include "easygtkwidget.h"
#include <ccall/ccall.h>

int (*callback_repl)(int selection_from, int selection_to, char *text) = NULL;
CCALL void set_callback_repl(int (*cb)(int selection_from, int selection_to, char *text)) {
        callback_repl = cb;
}



gboolean on_textview2_keypress(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
	char *key = gdk_keyval_to_string(event->keyval);

	int func_ret = FALSE; // by default, dont do event.preventDefault(); it will be set from console_key_press return value

	int selection_from = 2;
	int selection_to = 4;
	char *text = "println(321)";

        // cb returns 1 == handled, return...
        // cb returns 0 == handled, but still do the normal C stuff
        if (callback_repl && callback_repl(selection_from, selection_to, text)) {
			//return 0;
        }

		Sys_Printf("keypress %s\n", key);

	//js_push_global_by_name(ctx, "console_key_press");
	//duk_push_int(ctx, (int) widget);
	//duk_push_string(ctx, key);
	//duk_push_global_object(ctx);
	//int ret = duk_pcall(ctx, 3);
	//if (ret != 0) {
	//	Sys_Printf("js> console_key_press() failed: %s\n", duk_safe_to_string(ctx, -1));
	//} else {
	//	//Sys_Printf("js> console_key_press() ret: %s\n", duk_safe_to_string(ctx, -1));
	//	func_ret = duk_to_int(ctx, -1);
	//}
	//duk_pop(ctx);

	//unsigned int code = gdk_keyval_to_upper( event->keyval );
	//if ( code == GDK_ISO_Left_Tab ) {
	//	code = GDK_Tab;
	//}
	//Sys_Printf( "key: %d 0x%x (keyval: %d) (ctrl: %d) stringkey=%s hardware=%d time=%d type=%d is_modifier=%d\n", code, event->keyval, event->keyval, event->state & GDK_CONTROL_MASK , key, event->hardware_keycode, event->time, event->type, event->is_modifier);

	// for some fucked up reason Alt-Gr sends TWO key press events, first Control Left and then Alt Right
	// so control_pressed is 1
	//if (strcmp(key, "Alt Right") == 0) {
	//	control_pressed = 0;
	//}
	
	g_free(key);
	return func_ret;
}

gboolean on_textview2_keyrelease(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
	char *key = gdk_keyval_to_string(event->keyval);

	
		Sys_Printf("keyrelease %s\n", key);

	//js_push_global_by_name(ctx, "console_key_release");
	//duk_push_int(ctx, (int) widget);
	//duk_push_string(ctx, key);
	//duk_push_global_object(ctx);
	//int ret = duk_pcall(ctx, 3);
	//if (ret != 0) {
	//	Sys_Printf("js> console_key_press() failed: %s\n", duk_safe_to_string(ctx, -1));
	//}
	//duk_pop(ctx);
	
	g_free(key);
	return FALSE;
}

EasyGtkWidget *get_js_console() {

	EasyGtkWidget *easy_scrolledwindow2;

	EasyGtkWidget *textview_r;


	easy_scrolledwindow2  = EASYGTKWIDGET()->makeScrolledWindow();
	easy_scrolledwindow2->setName("scrolledwindow_r");
			
	textview_r = EASYGTKWIDGET()->makeTextView();
	textview_r->setName("textview_r");
			
	easy_scrolledwindow2->addChild(textview_r);
			

	easy_scrolledwindow2->setExpand(true)->setFill(true);
			
	textview_r->onEvent("focus_in_event", [](EasyGtkWidget *asd) -> int {
		set_global_hotkeys(0);
		
		//Sys_Printf("focus_in_event\n");
		return FALSE;
	});
	textview_r->onEvent("focus_out_event", [](EasyGtkWidget *asd) -> int {
		set_global_hotkeys(1);
		
		//Sys_Printf("focus_out_event\n");
		return FALSE;
	});

	g_signal_connect ((gpointer) textview_r->widget, "key_press_event", G_CALLBACK (on_textview2_keypress), NULL);
	g_signal_connect ((gpointer) textview_r->widget, "key_release_event", G_CALLBACK (on_textview2_keyrelease), NULL);
	easy_scrolledwindow2->setName("jsconsole");
	return easy_scrolledwindow2;
}