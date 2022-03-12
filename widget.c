/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of GUI.
 * 
 * GUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * GUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with GUI. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widget.h"
#include "layout.h"

static cos_class g_gui_widget_class = NULL;

static void gui_widget_print_method(gui_widget obj)
{
        printf("[%4d,%4d,%4d,%4d] ~",
                GUI_WIDGET_LEFT(obj),
                GUI_WIDGET_TOP(obj),
                GUI_WIDGET_RIGHT(obj),
                GUI_WIDGET_BOTTOM(obj));
}

cos_class gui_widget_class_get()
{
        cos_class cls;
        cos_class_spec spec;
        if (g_gui_widget_class) return g_gui_widget_class;
        if (cos_class_lookup(GUI_WIDGET_NAME, &cls)) return cls;
        spec.name        = GUI_WIDGET_NAME;
        spec.parent      = COS_OBJECT;
        spec.cls.size    = sizeof(struct gui_widget_class_s);
        spec.cls.ctor    = gui_widget_class_construct;
        spec.cls.dtor    = gui_widget_class_destruct;
        spec.inst.size   = sizeof(struct gui_widget_s);
        spec.inst.ctor   = gui_widget_construct;
        spec.inst.dtor   = gui_widget_destruct;
        spec.inst.params = cos_params_list(1, "layout", COS_TYPE_OBJECT);
        return cos_class_define(&spec);
}

void gui_widget_class_construct(cos_class cls)
{
        g_gui_widget_class = cls;
        cos_super_class_construct(COS_OBJECT);
        GUI_WIDGET_CLASS_PRINT(cls) = gui_widget_print_method;
}

void gui_widget_class_destruct(cos_class cls)
{
        cos_super_class_destruct(COS_OBJECT);
        g_gui_widget_class = NULL;
}

void gui_widget_construct(cos_object obj, cos_values vals)
{
        cos_super_construct(COS_OBJECT, obj);
        GUI_WIDGET_PARENT(obj) = NULL;
        GUI_WIDGET_CHILD(obj)  = NULL;
        GUI_WIDGET_NEXT(obj)   = NULL;
        GUI_WIDGET_LEFT(obj)   = 0;
        GUI_WIDGET_TOP(obj)    = 0;
        GUI_WIDGET_RIGHT(obj)  = 0;
        GUI_WIDGET_BOTTOM(obj) = 0;
        GUI_WIDGET_LAYOUT(obj) = GUI_LAYOUT_CAST(
                cos_unbox_object(cos_values_at(vals, 0)));
}

void gui_widget_destruct(cos_object obj)
{
        gui_widget curr = GUI_WIDGET_CHILD(obj), tmp;
        while (curr) {
                tmp = curr, curr = GUI_WIDGET_NEXT(tmp);
                cos_deref(tmp);
        }
        cos_super_destruct(COS_OBJECT, obj);
}

void gui_widget_add(gui_widget parent, gui_widget child)
{
        gui_widget curr = GUI_WIDGET_CHILD(parent);
        if (curr) {
                while (GUI_WIDGET_NEXT(curr)) curr = GUI_WIDGET_NEXT(curr);
                GUI_WIDGET_NEXT(curr)   = cos_ref(child);
        } else GUI_WIDGET_CHILD(parent) = cos_ref(child);
}

void gui_widget_add_many(gui_widget parent, size_t n, ...)
{
        size_t i;
        va_list args;
        va_start(args, n);
        for (i = 0; i < n; i++) {
                gui_widget_add(parent, va_arg(args, gui_widget));
        }
        va_end(args);
}

static void gui_widget_pr1nt(gui_widget wdg, int lvl)
{
        size_t i;
        gui_widget curr = GUI_WIDGET_CHILD(wdg);
        for (i = 0; i < lvl; i++) printf("\t");
        GUI_WIDGET_PRINT(wdg);
        printf("\n");
        while (curr) {
                gui_widget_pr1nt(curr, lvl + 1);
                curr = GUI_WIDGET_NEXT(curr);
        }
}

void gui_widget_print(gui_widget wdg)
{
        gui_widget_pr1nt(wdg, 0);
}

void gui_widget_layout(gui_widget wdg)
{
        gui_widget curr;
        /*
        switch (GUI_WIDGET_LAYOUT(wdg)) {
                case GUI_LAYOUT_VBOX:
                        gui_layout_vbox(wdg);
                        break;
                case GUI_LAYOUT_HBOX:
                        gui_layout_hbox(wdg);
                        break;
        }
        */
        curr = GUI_WIDGET_CHILD(wdg);
        while (curr) {
                gui_widget_layout(curr);
                curr = GUI_WIDGET_NEXT(curr);
        }
}

void gui_widget_resize(gui_widget wdg, gui_rect rect)
{
        GUI_WIDGET_RECT(wdg) = rect;
        gui_widget_layout(wdg);
}
