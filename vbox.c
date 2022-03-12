#include "vbox.h"

#include "widget.h"

static cos_class g_gui_vbox_class = NULL;

static void gui_vbox_layout_method(gui_layout layout, gui_widget wdg)
{
        int y, dy, n_child = 0;
        gui_widget curr = GUI_WIDGET_CHILD(wdg);
        while (curr) {
                curr = GUI_WIDGET_NEXT(curr);
                n_child++;
        }
        if (n_child == 0) return;
        y = GUI_WIDGET_TOP(wdg);
        dy = GUI_WIDGET_HEIGHT(wdg) / n_child;
        curr = GUI_WIDGET_CHILD(wdg);
        while (curr) {
                GUI_WIDGET_LEFT(curr) = GUI_WIDGET_LEFT(wdg);
                GUI_WIDGET_RIGHT(curr) = GUI_WIDGET_RIGHT(wdg);
                GUI_WIDGET_TOP(curr) = y;
                y += dy;
                GUI_WIDGET_BOTTOM(curr) = y;
                curr = GUI_WIDGET_NEXT(curr);
        }
}

cos_class gui_vbox_class_get()
{
        cos_class cls;
        cos_class_spec info;
        if (g_gui_vbox_class) return g_gui_vbox_class;
        if (cos_class_lookup(GUI_VBOX_NAME, &cls)) return cls;
        info.name        = GUI_VBOX_NAME;
        info.parent      = GUI_LAYOUT;
        info.cls.size    = sizeof(struct gui_vbox_class_s);
        info.cls.ctor    = gui_vbox_class_construct;
        info.cls.dtor    = gui_vbox_class_destruct;
        info.inst.size   = sizeof(struct gui_vbox_s);
        info.inst.ctor   = gui_vbox_construct;
        info.inst.dtor   = gui_vbox_destruct;
        info.inst.params = cos_params_list(5,
                "padding.left",   COS_TYPE_INT,
                "padding.top",    COS_TYPE_INT,
                "padding.right",  COS_TYPE_INT,
                "padding.bottom", COS_TYPE_INT,
                "spacing",        COS_TYPE_INT);
        return cos_class_define(&info);
}

void gui_vbox_class_construct(cos_class cls)
{
        if (!g_gui_vbox_class) g_gui_vbox_class = cls;
        cos_super_class_construct(GUI_LAYOUT, cls);
        GUI_LAYOUT_CLASS_LAYOUT(cls) = gui_vbox_layout_method;
}

void gui_vbox_class_destruct(cos_class cls)
{
        cos_super_class_destruct(GUI_LAYOUT, cls);
        if (g_gui_vbox_class == cls) g_gui_vbox_class = NULL;
}

void gui_vbox_construct(cos_object obj, cos_values vals)
{
        cos_super_construct(GUI_LAYOUT, obj);
}

void gui_vbox_destruct(cos_object obj)
{
        cos_super_destruct(GUI_LAYOUT, obj);
}