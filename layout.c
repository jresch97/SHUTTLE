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

static cos_class g_gui_layout_class = NULL;

cos_class gui_layout_class_get()
{
        cos_class cls;
        cos_class_spec spec;
        if (g_gui_layout_class) return g_gui_layout_class;
        if (cos_class_lookup(GUI_LAYOUT_NAME, &cls)) return cls;
        spec.name        = GUI_LAYOUT_NAME;
        spec.parent      = COS_OBJECT;
        spec.cls.size    = sizeof(struct gui_layout_class_s);
        spec.cls.ctor    = gui_layout_class_construct;
        spec.cls.dtor    = gui_layout_class_destruct;
        spec.inst.size   = sizeof(struct gui_layout_s);
        spec.inst.ctor   = gui_layout_construct;
        spec.inst.dtor   = gui_layout_destruct;
        spec.inst.params = cos_params_list(0);
        return cos_class_define(&spec);
}

void gui_layout_class_construct(cos_class cls)
{
        if (!g_gui_layout_class) g_gui_layout_class = cls;
        cos_super_class_construct(COS_OBJECT, cls);
}

void gui_layout_class_destruct(cos_class cls)
{
        cos_super_class_destruct(COS_OBJECT, cls);
        if (g_gui_layout_class == cls) g_gui_layout_class = NULL;
}

void gui_layout_construct(cos_object obj, cos_values vals)
{
        cos_super_construct(COS_OBJECT, obj);
}

void gui_layout_destruct(cos_object obj)
{
        cos_super_destruct(COS_OBJECT, obj);
}

void gui_layout_apply(gui_layout layout, gui_widget wdg)
{
        GUI_LAYOUT_LAYOUT(layout, wdg);
}