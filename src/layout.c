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

#include <stdio.h>
#include <stdlib.h>

#include "layout.h"
#include "widget.h"

static cos_class g_cls = NULL;

cos_class gui_layout_class_get()
{
        cos_class_spec spec;
        if (g_cls) return g_cls;
        spec.cls_name = "GUI_LAYOUT";
        spec.parent_cls = COS_OBJECT;
        spec.cls_size = sizeof(struct gui_layout_class_s);
        spec.obj_size = sizeof(struct gui_layout_s);
        spec.cls_init_fn = gui_layout_class_init;
        spec.cls_term_fn = gui_layout_class_term;
        spec.obj_init_fn = gui_layout_init;
        spec.obj_term_fn = gui_layout_term;
        return cos_def_class(&spec);
}

void gui_layout_class_init(cos_class cls)
{
        if (!g_cls) g_cls = cls;
}

void gui_layout_class_term(cos_class cls)
{
        if (g_cls == cls) g_cls = NULL;
}

void gui_layout_init(cos_object obj, cos_args args)
{
        cos_super(COS_OBJECT, obj);
}

void gui_layout_term(cos_object obj)
{

}

void gui_layout_apply(gui_layout layout, gui_widget wdg)
{
        ((gui_layout_class)cos_class_of(layout))->apply(layout, wdg);
}