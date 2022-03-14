/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of SHUTTLE.
 * 
 * SHUTTLE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * SHUTTLE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with SHUTTLE. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "button.h"

static cos_class g_cls = NULL;

static void _gui_button_print(gui_widget wdg)
{
        gui_button btn = (gui_button)wdg;
        printf("[%4d,%4d,%4d,%4d] [%s]",
                wdg->rect.left,
                wdg->rect.top,
                wdg->rect.right,
                wdg->rect.bottom,
                btn->text->c_str);
}

cos_class gui_button_class_get()
{
        cos_class_spec spec;
        if (g_cls) return g_cls;
        spec.cls_name = "GUI_BUTTON";
        spec.parent_cls = GUI_WIDGET;
        spec.cls_size = sizeof(struct gui_widget_class_s);
        spec.obj_size = sizeof(struct gui_widget_s);
        spec.cls_init_fn = gui_button_class_init;
        spec.cls_term_fn = gui_button_class_term;
        spec.obj_init_fn = gui_button_init;
        spec.obj_term_fn = gui_button_term;
        return cos_def_class(&spec);
}

void gui_button_class_init(cos_class cls)
{
        gui_widget_class wdgcls;
        if (!g_cls) g_cls = cls;
        gui_widget_class_init(cls);
        wdgcls = (gui_widget_class)cls;
        wdgcls->print = _gui_button_print;
}

void gui_button_class_term(cos_class cls)
{
        gui_widget_class_term(cls);
        if (g_cls == cls) g_cls = NULL;
}

void gui_button_init(cos_object obj, cos_args args)
{
        gui_button btn;
        cos_super(GUI_WIDGET, obj, NULL);
        btn = (gui_button)obj;
        btn->text = cos_new_string(cos_arg(args, const char *));
}

void gui_button_term(cos_object obj)
{
        cos_deref(((gui_button)obj)->text);
}
