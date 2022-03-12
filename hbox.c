#include "hbox.h"

#include "widget.h"

static cos_class g_gui_hbox_class = NULL;

static void gui_hbox_layout_method(gui_layout lay, gui_widget wdg)
{
        int x, dx, n_child = 0;
        gui_widget curr = GUI_WIDGET_CHILD(wdg);
        while (curr) {
                curr = GUI_WIDGET_NEXT(curr);
                n_child++;
        }
        if (n_child == 0) return;
        x = GUI_WIDGET_LEFT(wdg);
        dx = GUI_WIDGET_WIDTH(wdg) / n_child;
        curr = GUI_WIDGET_CHILD(wdg);
        while (curr) {
                GUI_WIDGET_TOP(curr) = GUI_WIDGET_TOP(wdg);
                GUI_WIDGET_BOTTOM(curr) = GUI_WIDGET_BOTTOM(wdg);
                GUI_WIDGET_LEFT(curr) = x;
                x += dx;
                GUI_WIDGET_RIGHT(curr) = x;
                if (!curr->next) {
                        GUI_WIDGET_RIGHT(curr) = GUI_WIDGET_WIDTH(wdg);
                }
                curr = GUI_WIDGET_NEXT(curr);
        }
}

cos_class gui_hbox_class_get()
{
        cos_class cls;
        cos_class_spec info;
        if (g_gui_hbox_class) return g_gui_hbox_class;
        if (cos_class_lookup(GUI_HBOX_NAME, &cls)) return cls;
        info.name        = GUI_HBOX_NAME;
        info.parent      = GUI_LAYOUT;
        info.cls.size    = sizeof(struct gui_hbox_class_s);
        info.cls.ctor    = gui_hbox_class_construct;
        info.cls.dtor    = gui_hbox_class_destruct;
        info.inst.size   = sizeof(struct gui_hbox_s);
        info.inst.ctor   = gui_hbox_construct;
        info.inst.dtor   = gui_hbox_destruct;
        info.inst.params = cos_params_list(5,
                "padding.left",   COS_TYPE_INT,
                "padding.top",    COS_TYPE_INT,
                "padding.right",  COS_TYPE_INT,
                "padding.bottom", COS_TYPE_INT,
                "spacing",        COS_TYPE_INT);
        return cos_class_define(&info);
}

void gui_hbox_class_construct(cos_class cls)
{
        if (!g_gui_hbox_class) g_gui_hbox_class = cls;
        cos_super_class_construct(GUI_LAYOUT, cls);
        GUI_LAYOUT_CLASS_LAYOUT(cls) = gui_hbox_layout_method;
}

void gui_hbox_class_destruct(cos_class cls)
{
        cos_super_class_destruct(GUI_LAYOUT, cls);
        if (g_gui_hbox_class == cls) g_gui_hbox_class = NULL;
}

void gui_hbox_construct(cos_object obj, cos_values vals)
{
        cos_super_construct(GUI_LAYOUT, obj);
}

void gui_hbox_destruct(cos_object obj)
{
        cos_super_destruct(GUI_LAYOUT, obj);
}