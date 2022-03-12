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

#include "label.h"
#include "param.h"
#include "value.h"

static cos_class g_gui_label_class = NULL;

static void gui_label_print_method(gui_widget wdg)
{
        printf("[%4d,%4d,%4d,%4d] \"%s\"",
                GUI_WIDGET_LEFT(wdg),
                GUI_WIDGET_TOP(wdg),
                GUI_WIDGET_RIGHT(wdg),
                GUI_WIDGET_BOTTOM(wdg),
                GUI_LABEL_TEXT(wdg));
}

cos_class gui_label_class_get()
{
        cos_class cls;
        cos_class_spec info;
        if (g_gui_label_class) return g_gui_label_class;
        if (cos_class_lookup(GUI_LABEL_NAME, &cls)) return cls;
        info.name        = GUI_LABEL_NAME;
        info.parent      = GUI_WIDGET;
        info.cls.size    = sizeof(struct gui_label_class_s);
        info.cls.ctor    = gui_label_class_construct;
        info.cls.dtor    = gui_label_class_destruct;
        info.inst.size   = sizeof(struct gui_label_s);
        info.inst.ctor   = gui_label_construct;
        info.inst.dtor   = gui_label_destruct;
        info.inst.params = cos_params_list(1, "text", COS_TYPE_STRING);
        return cos_class_define(&info);
}

void gui_label_class_construct(cos_class cls)
{
        g_gui_label_class = cls;
        cos_super_class_construct(GUI_WIDGET);
        GUI_WIDGET_CLASS_PRINT(cls) = gui_label_print_method;
}

void gui_label_class_destruct(cos_class cls)
{
        cos_super_class_destruct(GUI_WIDGET);
        g_gui_label_class = NULL;
}

void gui_label_construct(cos_object obj, cos_values vals)
{
        const char *text;
        cos_super_construct(GUI_WIDGET, obj);
        text = cos_unbox_string(cos_values_at(vals, 0));
        GUI_LABEL_TEXT(obj) = malloc(strlen(text) + 1);
        strcpy(GUI_LABEL_TEXT(obj), text);
}

void gui_label_destruct(cos_object obj)
{
        if (GUI_LABEL_TEXT(obj)) free(GUI_LABEL_TEXT(obj));
        cos_super_destruct(GUI_WIDGET, obj);
}
