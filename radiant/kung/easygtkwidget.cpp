#include "easygtkwidget.h"

//#include "../duktape/js_stuff.h"

extern GtkAccelGroup* global_accel;
int set_global_hotkeys_state = 1;
int are_global_hotkeys_activated() {
	return set_global_hotkeys_state;
}

int set_global_hotkeys(int state) {
	set_global_hotkeys_state = state;
	if (state)
		gtk_window_add_accel_group( GTK_WINDOW( g_pParentWnd->m_pWidget ), global_accel );
	else
		gtk_window_remove_accel_group( GTK_WINDOW( g_pParentWnd->m_pWidget ), global_accel );
	return 1;
}


// always returns an allocated string, so its safe to free it everytime
char *gdk_keyval_to_string(int keyval) {
	char *text = NULL;

	if (
		(keyval >= 'a' && keyval <= 'z') ||
		(keyval >= 'A' && keyval <= 'Z') ||
		(keyval >= '0' && keyval <= '9')
	) {
		text = (char *) g_malloc(2);
		text[0] = keyval;
		text[1] = '\0';
		return text;
	}

	switch (keyval) {
		case GDK_Control_L: text = "Control Left";  break;
		case GDK_Control_R: text = "Control Right"; break;
		case GDK_Alt_L:     text = "Alt Left";      break;
		case GDK_Alt_R:     text = "Alt Right";     break;
		case GDK_Return:    text = "Enter";         break;
		case GDK_space:     text = "Space";         break;
		case 0xfe52:        text = "Tilde";         break;
		case GDK_Shift_L:   text = "Shift Left";    break;
		case GDK_Tab:       text = "Tab";           break;

	}

	if ( ! text)
		return g_strdup_printf("%d", keyval);

	return g_strdup(text);
}



///////////////////////

	EasyGtkWidget::EasyGtkWidget()                               { /* Example: EASYGTKWIDGET()->makeButton("Some Button") */                                     }
	EasyGtkWidget::EasyGtkWidget(GtkWidget *widget_)             { widget = widget_;                                                                             }
	EasyGtkWidget *EasyGtkWidget::setData(char *key, int value)  { g_object_set_data(G_OBJECT(widget), key, (void *)value);                         return this; }
	int EasyGtkWidget::getData(char *key)                        { return (int) g_object_get_data(G_OBJECT(widget), key);                                        }
	void EasyGtkWidget::setRefCount(int new_ref_count)           { G_OBJECT(widget)->ref_count = new_ref_count;                                                  }
	int EasyGtkWidget::getRefCount()                             { return G_OBJECT(widget)->ref_count;                                                           }
	GList *EasyGtkWidget::getChilds()                            { return gtk_container_get_children(GTK_CONTAINER(widget));                                     }
	EasyGtkWidget *EasyGtkWidget::getSubmenu()                   { return EASYGTKWIDGET(gtk_menu_item_get_submenu((GtkMenuItem *)widget));                       }
	int EasyGtkWidget::contains(GtkWidget *widget)               { return g_list_find(getChilds(), widget) != NULL;                                              }
	EasyGtkWidget *EasyGtkWidget::getParent()                    { return EASYGTKWIDGET(gtk_widget_get_parent(widget));                                          }
	char *EasyGtkWidget::getTypeName()                           { return (char *) G_OBJECT_TYPE_NAME(widget);                                                   }
	EasyGtkWidget *EasyGtkWidget::destroy()                      { gtk_widget_destroy(widget);                                                      return this; }
	EasyGtkWidget *EasyGtkWidget::show()                         { gtk_widget_show(widget);                                                         return this; }
	EasyGtkWidget *EasyGtkWidget::showAll()                      { gtk_widget_show_all(widget);                                                     return this; }

	int EasyGtkWidget::getCursorPos() {
		if (isTextView())
			return gtk_text_view_get_cursor_pos((GtkTextView *) widget);
		return 0;
	}

	char *EasyGtkWidget::getTextBetween(int from, int to) {
		return get_text_view_get_text_between((GtkTextView *) widget, from, to);
	}

	char *EasyGtkWidget::getName()           { return (char *)gtk_widget_get_name(widget); }
	void EasyGtkWidget::setName(char *name)  { gtk_widget_set_name(widget, name);          }

	EasyGtkWidget *EasyGtkWidget::getTabBar() {
		EasyGtkWidget *tabbar = this;
		do {
			if (tabbar->getData("isTabBar"))
				return tabbar;
		} while (tabbar = tabbar->getParent());
		return NULL;
	}

	EasyGtkWidget *EasyGtkWidget::replaceTextBetween(int from, int to, char *text) { gtk_text_view_replace_text_between(GTK_TEXT_VIEW(widget), from, to, text); return this; }

	// give all children the same size:
	// fill/expand on all childs
	// is same as:
	// expand on all childs and call setHomogeneous() on box IIRC
	EasyGtkWidget *EasyGtkWidget::setHomogeneous(bool homogeneous) {
		if (GTK_IS_BOX(widget))
			gtk_box_set_homogeneous(GTK_BOX(widget), homogeneous);
		return this;
	}

	EasyGtkWidget *EasyGtkWidget::addChild(EasyGtkWidget *child) {
		// http://stackoverflow.com/questions/2749896/whats-the-difference-between-gtk-box-pack-start-and-gtk-container-add
		if (GTK_IS_BOX(widget)) {
			gtk_box_pack_start( GTK_BOX(widget), child->widget, FALSE, FALSE, 0 );
			//gtk_box_pack_start( GTK_BOX(widget), child->widget, TRUE, TRUE, 0 );
			goto finish;
		}
		if (GTK_IS_CONTAINER(widget)) {
			gtk_container_add( GTK_CONTAINER(widget), child->widget );
			goto finish;
		}
		finish:
		child->show();
		return this;
	}
	
	EasyGtkWidget *EasyGtkWidget::addChildA(EasyGtkWidget *child)               { gtk_paned_pack1( GTK_PANED( widget ), child->widget, FALSE, FALSE ); child->show();            return this; }
	EasyGtkWidget *EasyGtkWidget::addChildB(EasyGtkWidget *child)               { gtk_paned_pack2( GTK_PANED( widget ), child->widget, FALSE, FALSE ); child->show();            return this; }
	EasyGtkWidget *EasyGtkWidget::setLabel(char *label)                         { gtk_button_set_label(GTK_BUTTON(widget), label);                                               return this; }
	EasyGtkWidget *EasyGtkWidget::setSpacing(int spacing)                       { gtk_widget_set(widget, "spacing", spacing, NULL);                                              return this; }
	EasyGtkWidget *EasyGtkWidget::setExpand(gboolean expand)                    { gtk_container_child_set(GTK_CONTAINER(getParent()->widget), widget, "expand", expand, NULL);   return this; }
	EasyGtkWidget *EasyGtkWidget::setFill(gboolean fill)                        { gtk_container_child_set(GTK_CONTAINER(getParent()->widget), widget, "fill", fill, NULL);       return this; }
	EasyGtkWidget *EasyGtkWidget::setPadding(guint padding)                     { gtk_container_child_set(GTK_CONTAINER(getParent()->widget), widget, "padding", padding, NULL); return this; }
	EasyGtkWidget *EasyGtkWidget::ref()                                         { g_object_ref(widget);                                                                          return this; }
	EasyGtkWidget *EasyGtkWidget::unref()                                       { g_object_unref(widget);                                                                        return this; }
	EasyGtkWidget *EasyGtkWidget::fixedPut(EasyGtkWidget *child, int x, int y)  { gtk_fixed_put(GTK_FIXED(widget), child->widget, x, y); child->show();                          return this; }

	EasyGtkWidget *EasyGtkWidget::resize(int width, int height)                 {
		if (GTK_IS_WINDOW(widget))
			gtk_window_resize(GTK_WINDOW(widget), width, height);
		return this;
	}

	EasyGtkWidget *EasyGtkWidget::removeFromContainer() {
		gtk_container_remove(GTK_CONTAINER(gtk_widget_get_parent(widget)), widget);
		return this;
	}
	
	EasyGtkWidget *EasyGtkWidget::makeButton(char *label) { widget = gtk_button_new_with_mnemonic(label); show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeLabel(char *label)  { widget = gtk_label_new_with_mnemonic(label);  show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeHorizontalBox()     { widget = gtk_hbox_new(FALSE, 0);              show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeVerticalBox()       { widget = gtk_vbox_new(FALSE, 0);              show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeHorizontalPane()    { widget = gtk_hpaned_new();                    show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeVerticalPane()      { widget = gtk_vpaned_new();                    show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeFixed()             { widget = gtk_fixed_new();                     show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeScrolledWindow()    { widget = gtk_scrolled_window_new(NULL, NULL); show(); return this; }
	EasyGtkWidget *EasyGtkWidget::makeTextView()          { widget = gtk_text_view_new();                 show(); return this; }



	EasyGtkWidget *EasyGtkWidget::makeTabButton(char *label) {
		EasyGtkWidget *realButton = EASYGTKWIDGET()->makeButton(label);
		EasyGtkWidget *closeButton = EASYGTKWIDGET()->makeButton("[x]");
		EasyGtkWidget *newBox = EASYGTKWIDGET()->makeHorizontalBox();
		newBox->setData("isTabButton", 1);
		newBox->addChild(realButton);
		newBox->addChild(closeButton);						
		closeButton->onClick([](EasyGtkWidget *button) {
			Sys_Printf("Pressed X!\n");
		});
		widget = newBox->widget;

		this->onTabClose([] (EasyGtkWidget *closebutton) {
			EasyGtkWidget *tabs =  closebutton->getTabBar(); // GtkHBox
			tabs->getParent()->onChilds(
				[] (int id, EasyGtkWidget *widget) {
					//Sys_Printf("button_click_close_tab() id=%d type=%s\n", id, widget->getTypeName());
					if (id > 0)
						widget->destroy();
				}
			);
			tabs->setData("currentTab", NULL);
			closebutton->getParent()->destroy();
		});

		return newBox;
	}

	void EasyGtkWidget::wrapper_on_click(GtkWidget *widget, gpointer func) {
		void (*func_on_click)(EasyGtkWidget *widget);
		*(int *)&func_on_click = (int) func;
		if (func_on_click)
			func_on_click(EASYGTKWIDGET(widget));
	}
	EasyGtkWidget *EasyGtkWidget::onClick(void (*func)(EasyGtkWidget *widget)) {
		if (getData("isTabButton")) {
			getChild(0)->onClick(func);
			//getChild(0)->setLabel("buuuargh");
			return this;
		}

		gtk_signal_connect(GTK_OBJECT(widget), "clicked", G_CALLBACK(wrapper_on_click), (gpointer) func);
		return this;
	}

	typedef int(*func_on_event_t)(EasyGtkWidget *widget);
	int EasyGtkWidget::wrapper_on_event(GtkWidget *widget, GdkEventCrossing *event, gpointer user_data_func) {		
		func_on_event_t func_on_event;
		func_on_event = (func_on_event_t) user_data_func;
		if (func_on_event)
			return func_on_event(EASYGTKWIDGET(widget));
		return FALSE; // if the callback is not found, just let gtk handle everything
	}
	EasyGtkWidget *EasyGtkWidget::onEvent(char *eventmsg, int (*func)(EasyGtkWidget *widget)) {
		gtk_signal_connect(GTK_OBJECT(widget), eventmsg, G_CALLBACK(wrapper_on_event), (gpointer) func);
		return this;
	}

	EasyGtkWidget *EasyGtkWidget::onTabClose(void (*func)(EasyGtkWidget *widget)) {
		if (getData("isTabButton")) {
			getChild(1)->onClick(func);
		}
		return this;
	}

	void EasyGtkWidget::setSize(int width, int height) {
		EasyGtkWidget *parent = getParent();
		gtk_container_child_set(GTK_CONTAINER(parent->widget), widget, "expand", FALSE, /*"fill", FALSE, "padding", 0,*/ NULL);
		gtk_widget_set_size_request(widget, width, height);
	}

	void EasyGtkWidget::onChilds(void (*func)(int id, EasyGtkWidget *easywidget)) {
		GList *childs = getChilds();
		int i = 0;
		for (int i=0; childs; childs = childs->next, i++) {
			func(i, new EasyGtkWidget(GTK_WIDGET(childs->data)));
		}
	}

	EasyGtkWidget *EasyGtkWidget::getChild(int id) {
		GList *childs = getChilds();
		int i = 0;
		for (int i=0; childs; childs = childs->next, i++) {
			if (i == id)
				return EASYGTKWIDGET((GtkWidget *) childs->data);
		}
		return EASYGTKWIDGET();
	}

	int EasyGtkWidget::isValid() {
		return widget != NULL;
	}
	
	int EasyGtkWidget::isContainer() { return GTK_IS_CONTAINER(widget); }
	int EasyGtkWidget::isLabel() { return GTK_IS_LABEL(widget); }
	int EasyGtkWidget::isButton() { return GTK_IS_BUTTON(widget); }
	int EasyGtkWidget::isImage() { return GTK_IS_IMAGE(widget); }
	int EasyGtkWidget::isMenu() { return GTK_IS_MENU(widget); }
	int EasyGtkWidget::isMenuItem() { return GTK_IS_MENU_ITEM(widget); }
	int EasyGtkWidget::isTextView() { return GTK_IS_TEXT_VIEW(widget); }
	

	void EasyGtkWidget::removeAllChilds(int from) {
		GList *childs = getChilds();
		// jump over the first from'th elements
		for (int i=0; i<from && childs; i++)
			childs = childs->next;
		while (childs) {
			// todo: increase ref count somewhere else
			g_object_ref(GTK_WIDGET(childs->data));
			//Sys_Printf("Ref Count: %d\n", G_OBJECT(childs->data)->ref_count);

			gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(childs->data));
			childs = childs->next;
		}
	}

	EasyGtkWidget *EasyGtkWidget::setBackgroundColor(char *color) {
		GdkColor tmp;
		gdk_color_parse(color, &tmp);
		gtk_widget_modify_bg(widget, GTK_STATE_NORMAL, &tmp);
		return this;
	}

	void EasyGtkWidget::replaceWithWidget(EasyGtkWidget *newWidget) {
		EasyGtkWidget *parent = getParent();
		
		if (GTK_IS_PANED(parent->widget))
		{
			int isA = gtk_paned_get_child1(GTK_PANED(parent->widget)) == widget;
			int isB = gtk_paned_get_child2(GTK_PANED(parent->widget)) == widget;
			this->removeFromContainer();
			if (isA)
				parent->addChildA(newWidget);
			if (isB)
				parent->addChildB(newWidget);
		} else if (GTK_IS_BOX(parent->widget) || GTK_IS_FRAME(parent->widget))
		{
			this->removeFromContainer();
			parent->addChild(newWidget);
		} else {
			//this->ref();
			//this->getParent()
			//gtk_widget_unparent(this->widget);
			Sys_Printf("Case for type=%s is not implemented yet!!\n", parent->getTypeName());
		}
	}
	
	EasyGtkWidget *EasyGtkWidget::splitIntoHorizontalPane(EasyGtkWidget *childB) {
		EasyGtkWidget *vpane = EASYGTKWIDGET()->makeHorizontalPane();
		ref();
		replaceWithWidget(vpane);
		vpane->addChildA(this);
		unref();
		vpane->addChildB(childB);
		return vpane;
	}
	EasyGtkWidget *EasyGtkWidget::splitIntoVerticalPane(EasyGtkWidget *childB) {
		EasyGtkWidget *vpane = EASYGTKWIDGET()->makeVerticalPane();
		ref();
		replaceWithWidget(vpane);
		vpane->addChildA(this);
		unref();
		vpane->addChildB(childB);
		return vpane;
	}
	
	EasyGtkWidget *EasyGtkWidget::getChildA() {
		return EASYGTKWIDGET(gtk_paned_get_child1(GTK_PANED(widget)));
	}
	EasyGtkWidget *EasyGtkWidget::getChildB() {
		return EASYGTKWIDGET(gtk_paned_get_child2(GTK_PANED(widget)));
	}

	// result needs to be freed
	char *EasyGtkWidget::getText() {
		char *text = g_strdup("");
		if (isLabel()) {
			text = (char *)gtk_label_get_text((GtkLabel *)widget);
			text = g_strdup(text);
		}
		if (isButton()) {
			text = (char *)gtk_button_get_label((GtkButton *)widget);
			text = g_strdup(text);
		}
		// gtk_text_view_get_text() allocates the result itself
		if (isTextView())
			text = gtk_text_view_get_text((GtkTextView *)widget);
		return text;
	}

	char *EasyGtkWidget::getSelectedText() {
		char *text = g_strdup("");
		// always free the result
		if (isTextView())
			text = gtk_text_view_get_selected_text((GtkTextView *)widget);
		return text;
	}
	char *EasyGtkWidget::getTooltipText() { return gtk_widget_get_tooltip_text(widget); }
	char *EasyGtkWidget::getTooltipMarkup() { return gtk_widget_get_tooltip_markup(widget); }

	////////////////////////



void dump_hierarchy() {

#if 0

	Sys_Printf("hierarchy\n");

		
	std::list<string> path;

		
	//Sys_Printf("Type of window: %s", easywin->getTypeName());
	EasyGtkWidget *window_vbox = NULL;
	int depth = 0;

	auto intend = [](int depth) {
		std::string tmp(depth, '\t');
		Sys_Printf( tmp.c_str() );
	};

	std::function<void (EasyGtkWidget *tmp)> recursive;
	recursive = [&](EasyGtkWidget *tmp) -> void {
			
		EasyGtkWidget *easygtkwidget = NULL;

			
		gint wx, wy;
		gtk_widget_translate_coordinates(tmp->widget, gtk_widget_get_toplevel(tmp->widget), 0, 0, &wx, &wy);


 	GtkAllocation alloc;
gtk_widget_get_allocation(tmp->widget, &alloc);

		char *text = tmp->getText();
		char *tooltip_text = tmp->getTooltipText();
		char *tooltip_markup = tmp->getTooltipMarkup();
		char *name = tmp->getName();
		char *type = tmp->getTypeName();
		
		std::list<string> args;
		if (strcmp(type, name)) // if type != name
			args.push_back( string_format("name: \"%s\"", name) );
		if (text && strcmp(text, ""))
			args.push_back( string_format("text: \"%s\"", text) );
		args.push_back( string_format("x: %d", wx) );
		args.push_back( string_format("y: %d", wy) );
		if (tooltip_text)
			args.push_back( string_format("tooltip: \"%s\"", tooltip_text) );

		string retlist = implode(",", path);
		Sys_Printf("widget([%s]) = new %s({%s})\n", retlist.c_str(), type, implode(", ", args).c_str());
		Sys_Printf("alloc.x=%d, alloc.y=%d, alloc.width=%d, alloc.height=%d\n", alloc.x, alloc.y, alloc.width, alloc.height);
		if ( ! tmp->isContainer()) {


			//intend(depth); Sys_Printf("{ type: \"%s\"; childs: []; depth: %d; x: %d, y: %d, text: \"%s\" tooltip_text: \"%s\" tooltip_markup: \"%s\", name: \"%s\"}\n", tmp->getTypeName(), depth, wx, wy, text, tooltip_text, tooltip_markup, name);
				
			//Sys_Printf("No container hence no childs\n");
			//path.pop_back();
			return;
		}
		GList *childs = tmp->getChilds();
			
		if ( ! childs) {
			//path.pop_back();
			return;
		}
			
		//intend(depth); Sys_Printf("{ containertype: \"%s\", childs = [\n", tmp->getTypeName(),tooltip_text, tooltip_markup);

		//intend(depth); Sys_Printf("childs: [\n");
			
		int i = 0;
		while (childs) {
			easygtkwidget = EASYGTKWIDGET((GtkWidget *)childs->data);

			//intend(depth+1); Sys_Printf("type: \"%s\" // depth=%d\n", easygtkwidget->getTypeName(), depth);

			if ( ! strcmp(easygtkwidget->getTypeName(), "GtkVBox")) { window_vbox = easygtkwidget; }


				
			path.push_back(string_format("%d", i));
			recursive(easygtkwidget);
			path.pop_back();

			childs = childs->next;
			i++;
		}

		if (tmp->isMenuItem()) {
			EasyGtkWidget *submenu = tmp->getSubmenu();
			if ( ! submenu->isValid()) {
				//Sys_Printf("%s HAS NO VALID SUBMENU!\n", tmp->getTypeName());
				// The items in MenuItems are MenuItems aswell, just with no submenu
				return;
			}

			// submenus are special snowflakes, the have a custom branch in hierarchy
			path.push_back(string_format("\"submenu\""));
			recursive(submenu);
			path.pop_back(); // pop the submenu
		}
	};
		
	EasyGtkWidget *easywin = EASYGTKWIDGET(window);
	recursive(easywin);


	Sys_Printf("     window = %.8p\n", window);
	Sys_Printf("window_vbox = %.8p\n", window_vbox);

#endif
}

#if 0
std::list<EasyGtkWidget *> widget_find_name(char *name_to_find) {
	//Sys_Printf("find name of: %s\n", name_to_find);

		
	std::list<string> path;

		
	//Sys_Printf("Type of window: %s", easywin->getTypeName());
	EasyGtkWidget *window_vbox = NULL;
	int depth = 0;

	auto intend = [](int depth) {
		std::string tmp(depth, '\t');
		Sys_Printf( tmp.c_str() );
	};

	std::list<EasyGtkWidget *> results;

	std::function<void (EasyGtkWidget *tmp)> recursive;
	recursive = [&](EasyGtkWidget *tmp) -> void {
			
		char *name = tmp->getName();
		
		if (strcmp(name, name_to_find) == 0)
			results.push_back(tmp);

		// no container hence no childs
		if ( ! tmp->isContainer()) {
			return;
		}

		GList *childs = tmp->getChilds();
		if ( ! childs) {
			//path.pop_back();
			return;
		}
			
		int i = 0;
		while (childs) {
			EasyGtkWidget *easygtkwidget = EASYGTKWIDGET((GtkWidget *)childs->data);

			path.push_back(string_format("%d", i));
			recursive(easygtkwidget);
			path.pop_back();

			childs = childs->next;
			i++;
		}
		if (0)
		if (tmp->isMenuItem()) {
			EasyGtkWidget *submenu = tmp->getSubmenu();
			if ( ! submenu->isValid()) {
				//Sys_Printf("%s HAS NO VALID SUBMENU!\n", tmp->getTypeName());
				// The items in MenuItems are MenuItems aswell, just with no submenu
				return;
			}

			// submenus are special snowflakes, the have a custom branch in hierarchy
			path.push_back(string_format("\"submenu\""));
			recursive(submenu);
			path.pop_back(); // pop the submenu
		}
	};
		
	EasyGtkWidget *easywin = EASYGTKWIDGET(window);
	recursive(easywin);


	return results;
}
#endif
int in_between(int min, int val, int max) {
	return val > min && val < max;
}

#if 0
std::list<EasyGtkWidget *> get_widget_at_position(int mouse_left, int mouse_top) {
	//Sys_Printf("find at: %d %d\n", mouse_left, mouse_top);

		
	std::list<string> path;

		
	//Sys_Printf("Type of window: %s", easywin->getTypeName());
	EasyGtkWidget *window_vbox = NULL;
	int depth = 0;

	auto intend = [](int depth) {
		std::string tmp(depth, '\t');
		Sys_Printf( tmp.c_str() );
	};

	GdkWindow *win = gtk_widget_get_window(window);

	
	//Sys_Printf("win:%d\n", win);
	int win_x, win_y;
	gdk_window_get_origin(win, &win_x, &win_y);

	//Sys_Printf("winx:%d winy:%d\n", win_x, win_y);

	std::list<EasyGtkWidget *> results;

	std::function<void (EasyGtkWidget *tmp)> recursive;
	recursive = [&](EasyGtkWidget *tmp) -> void {
			
		char *name = tmp->getName();
		

		GtkAllocation alloc;
		gtk_widget_get_allocation(tmp->widget, &alloc);

		if (in_between(alloc.x, mouse_left - win_x, alloc.x + alloc.width))
		if (in_between(alloc.y, mouse_top - win_y, alloc.y + alloc.height))
		{
			results.push_back(tmp);
			//Sys_Printf("below cursor: %s type=%s\n", name, tmp->getTypeName());
		}



		// no container hence no childs
		if ( ! tmp->isContainer()) {
			return;
		}

		GList *childs = tmp->getChilds();
		if ( ! childs) {
			//path.pop_back();
			return;
		}
			
		int i = 0;
		while (childs) {
			EasyGtkWidget *easygtkwidget = EASYGTKWIDGET((GtkWidget *)childs->data);

			path.push_back(string_format("%d", i));
			recursive(easygtkwidget);
			path.pop_back();

			childs = childs->next;
			i++;
		}
		if (0)
		if (tmp->isMenuItem()) {
			EasyGtkWidget *submenu = tmp->getSubmenu();
			if ( ! submenu->isValid()) {
				//Sys_Printf("%s HAS NO VALID SUBMENU!\n", tmp->getTypeName());
				// The items in MenuItems are MenuItems aswell, just with no submenu
				return;
			}

			// submenus are special snowflakes, the have a custom branch in hierarchy
			path.push_back(string_format("\"submenu\""));
			recursive(submenu);
			path.pop_back(); // pop the submenu
		}
	};
		
	EasyGtkWidget *easywin = EASYGTKWIDGET(window);
	recursive(easywin);


	return results;
}
#endif