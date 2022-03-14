#include "vbox.h"

#include "widget.h"

static cos_class g_cls = NULL;

static void _gui_vbox_apply(gui_layout layout, gui_widget wdg)
{
        int y, dy;
        gui_widget curr;
        size_t n_child;
        curr = wdg->child;
        n_child = 0;
        while (curr) {
                curr = curr->next;
                n_child++;
        }
        if (n_child == 0) return;
        y = wdg->rect.top;
        dy = (wdg->rect.bottom - wdg->rect.top) / n_child;
        curr = wdg->child;
        while (curr) {
                curr->rect.left = wdg->rect.left;
                curr->rect.right = wdg->rect.right;
                curr->rect.top = y;
                y += dy;
                if (!curr->next) curr->rect.bottom = wdg->rect.bottom;
                else curr->rect.bottom = y;
                curr = curr->next;
        }
}

cos_class gui_vbox_class_get()
{
        cos_class_spec spec;
        if (g_cls) return g_cls;
        spec.cls_name = "GUI_VBOX";
        spec.parent_cls = GUI_LAYOUT;
        spec.cls_size = sizeof(struct gui_vbox_class_s);
        spec.obj_size = sizeof(struct gui_vbox_s);
        spec.cls_init_fn = gui_vbox_class_init;
        spec.cls_term_fn = gui_vbox_class_term;
        spec.obj_init_fn = gui_vbox_init;
        spec.obj_term_fn = gui_vbox_term;
        return cos_def_class(&spec);
}

void gui_vbox_class_init(cos_class cls)
{
        if (!g_cls) g_cls = cls;
        ((gui_layout_class)cls)->apply = _gui_vbox_apply;
}

void gui_vbox_class_term(cos_class cls)
{
        if (g_cls == cls) g_cls = NULL;
}

void gui_vbox_init(cos_object obj, cos_args args)
{
        cos_super(GUI_LAYOUT, obj);
}

void gui_vbox_term(cos_object obj)
{

}