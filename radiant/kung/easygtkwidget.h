#ifndef EASYGTKWIDGET_HPP
#define EASYGTKWIDGET_HPP

#include "../stdafx.h"
#ifdef _WIN32
extern "C" {
#include <gdk/gdkwin32.h>
}
#endif
#include <gtk/gtk.h>

#include <gtk/gtkgl.h>

#include <glib/gi18n.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkprivate.h>
#include <sys/stat.h>
#if defined ( __linux__ ) || defined ( __APPLE__ )
  #include <unistd.h>
#endif
#include "../gtkmisc.h"
#include "../groupdialog.h"
#include "../patchdialog.h"
#include "../filters.h"

#include <functional>
#include <stack>


#include "../stdafx.h"
#include <string>
//#include <duktapestuff.h>
#include "../radiant/qe3.h"


extern GtkWidget* window;

char *gdk_keyval_to_string(int keyval);

static char *gtk_text_view_get_text(GtkTextView *textview) {
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
    gchar *text;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	// the result needs to be freed
    return text;
}

static int gtk_text_view_get_cursor_pos(GtkTextView *textview) {
	// todo: add label which shows current line or so for error messages
	// and/or mark the errored line
	//int row = gtk_text_iter_get_line(&iter);
	//int col = gtk_text_iter_get_line_offset(&iter);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
	GtkTextMark *textmark = gtk_text_buffer_get_insert(buffer);
	GtkTextIter iter_cursor;
	gtk_text_buffer_get_iter_at_mark(buffer, &iter_cursor, textmark);
	return gtk_text_iter_get_offset(&iter_cursor);
}

static char *get_text_view_get_text_between(GtkTextView *textview, int from, int to) {
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
	GtkTextIter iter_from, iter_to;
	gtk_text_buffer_get_iter_at_offset(buffer, &iter_from, from);
	gtk_text_buffer_get_iter_at_offset(buffer, &iter_to  , to  );
    return gtk_text_buffer_get_text(buffer, &iter_from, &iter_to, FALSE);
}

static void gtk_text_view_replace_text_between(GtkTextView *textview, int from, int to, char *text) {
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
	GtkTextIter iter_from, iter_to;
	gtk_text_buffer_get_iter_at_offset(buffer, &iter_from, from);
	gtk_text_buffer_get_iter_at_offset(buffer, &iter_to  , to  );
	gtk_text_buffer_delete(buffer, &iter_from, &iter_to);
	// maybe I should get a new iter, because the textiters are corrupted after textbuffer change? but the iter_from kinda shouldnt be affected
	//gtk_text_buffer_get_iter_at_offset(buffer, &iter_from, from);
	gtk_text_buffer_insert(buffer, &iter_from, text, strlen(text));
}

static char *gtk_text_view_get_selected_text(GtkTextView *textview) {
	GtkTextBuffer *buf = gtk_text_view_get_buffer(textview);
	GtkTextMark *mark = gtk_text_buffer_get_selection_bound (buf);
	GtkTextIter start, end;
	//gtk_text_buffer_get_iter_at_offset(buf, &start, 0);
	//gtk_text_buffer_get_iter_at_offset(buf, &end, 10);
	int has_selection = gtk_text_buffer_get_selection_bounds(buf, &start, &end);
	char *text = g_strdup(""); // so we can always free the result without any special case
	if (has_selection)
		text = gtk_text_buffer_get_text(buf, &start, &end, true);
	return text;
}

class EasyGtkWidget;
static EasyGtkWidget *EASYGTKWIDGET(GtkWidget *gtkwidget = NULL);

class EasyGtkWidget {
	public:
	GtkWidget *widget = NULL;

	EasyGtkWidget();
	EasyGtkWidget(GtkWidget *widget_);
	EasyGtkWidget *setData(char *key, int value);
	int getData(char *key);
	void setRefCount(int new_ref_count);
	int getRefCount();
	GList *getChilds();
	EasyGtkWidget *getSubmenu();
	int contains(GtkWidget *widget);
	EasyGtkWidget *getParent();
	char *getTypeName();
	EasyGtkWidget *destroy();
	EasyGtkWidget *show();
	EasyGtkWidget *showAll();

	int getCursorPos();

	char *getTextBetween(int from, int to);

	char *getName();
	void setName(char *name);

	EasyGtkWidget *getTabBar();

	EasyGtkWidget *replaceTextBetween(int from, int to, char *text);

	EasyGtkWidget *setHomogeneous(bool homogeneous);

	EasyGtkWidget *addChild(EasyGtkWidget *child);
	
	EasyGtkWidget *addChildA(EasyGtkWidget *child);
	EasyGtkWidget *addChildB(EasyGtkWidget *child);
	EasyGtkWidget *setLabel(char *label);
	EasyGtkWidget *setSpacing(int spacing);
	EasyGtkWidget *setExpand(gboolean expand);
	EasyGtkWidget *setFill(gboolean fill);
	EasyGtkWidget *setPadding(guint padding);
	EasyGtkWidget *ref();
	EasyGtkWidget *unref();
	EasyGtkWidget *fixedPut(EasyGtkWidget *child, int x, int y);

	EasyGtkWidget *resize(int width, int height);

	EasyGtkWidget *removeFromContainer();
	
	EasyGtkWidget *makeButton(char *label);
	EasyGtkWidget *makeLabel(char *label);
	EasyGtkWidget *makeHorizontalBox();
	EasyGtkWidget *makeVerticalBox();
	EasyGtkWidget *makeHorizontalPane();
	EasyGtkWidget *makeVerticalPane();
	EasyGtkWidget *makeFixed();
	EasyGtkWidget *makeScrolledWindow();
	EasyGtkWidget *makeTextView();



	EasyGtkWidget *makeTabButton(char *label);

	static void wrapper_on_click(GtkWidget *widget, gpointer func);
	EasyGtkWidget *onClick(void (*func)(EasyGtkWidget *widget));

	static int wrapper_on_event(GtkWidget *widget, GdkEventCrossing *event, gpointer user_data_func);
	EasyGtkWidget *onEvent(char *eventmsg, int (*func)(EasyGtkWidget *widget));

	EasyGtkWidget *onTabClose(void (*func)(EasyGtkWidget *widget));

	void setSize(int width, int height);

	void onChilds(void (*func)(int id, EasyGtkWidget *easywidget)) ;

	EasyGtkWidget *getChild(int id) ;

	int isValid() ;
	
	int isContainer();
	int isLabel();
	int isButton();
	int isImage();
	int isMenu();
	int isMenuItem();
	int isTextView();
	

	void removeAllChilds(int from=0);

	EasyGtkWidget *setBackgroundColor(char *color);

	void replaceWithWidget(EasyGtkWidget *newWidget);
	
	EasyGtkWidget *splitIntoHorizontalPane(EasyGtkWidget *childB);
	EasyGtkWidget *splitIntoVerticalPane(EasyGtkWidget *childB);
	
	EasyGtkWidget *getChildA();
	EasyGtkWidget *getChildB();

	// result needs to be freed
	char *getText();

	char *getSelectedText();
	char *getTooltipText();
	char *getTooltipMarkup();
};

EasyGtkWidget *EASYGTKWIDGET(GtkWidget *gtkwidget) {
	if (gtkwidget == NULL)
		goto finish;
	EasyGtkWidget *tmp;
	tmp = (EasyGtkWidget *) g_object_get_data(G_OBJECT(gtkwidget), "easygtkwidget");
	if (tmp) {
		//Sys_Printf("Reusing old EasyGtkWidget instance!\n");
		return tmp;
	}
	finish:
	tmp = new EasyGtkWidget(gtkwidget);
	tmp->setData("easygtkwidget", (int) tmp);
	return tmp;
}



void dump_hierarchy();
std::list<EasyGtkWidget *> widget_find_name(char *name_to_find);
int in_between(int min, int val, int max);
std::list<EasyGtkWidget *> get_widget_at_position(int mouse_left, int mouse_top);

int set_global_hotkeys(int state);
int are_global_hotkeys_activated();

#endif