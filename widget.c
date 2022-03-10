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
#include <object.h>
#include <param.h>
#include <value.h>

#include "widget.h"

static COS_CLASS gui_widget_class = NULL;

static void gui_widget_pr1nt(GUI_WIDGET this, int level)
{
        size_t i;
        GUI_WIDGET curr = GUI_WIDGET_CHILD(this);
        for (i = 0; i < level; i++) printf("\t");
        GUI_WIDGET_CLASS_PRINT(GUI_WIDGET_CLASS(this))(this);
        printf("\n");
        while (curr) {
                gui_widget_pr1nt(curr, level + 1);
                curr = GUI_WIDGET_NEXT(curr);
        }
}

static void gui_widget_print_method(GUI_WIDGET this)
{
        printf("[%4d,%4d,%4d,%4d] ~",
                GUI_WIDGET_LEFT  (this),
                GUI_WIDGET_TOP   (this),
                GUI_WIDGET_RIGHT (this),
                GUI_WIDGET_BOTTOM(this));
}

COS_CLASS gui_widget_class_get()
{
        COS_CLASS_INFO info;
        if (gui_widget_class) return gui_widget_class;
        if (cos_class_lookup(GUI_WIDGET_CLASS_NAME,
                             &gui_widget_class)) {
                return gui_widget_class;
        }
        info.name        = GUI_WIDGET_CLASS_NAME;
        info.parent      = COS_OBJECT_TYPE;
        info.class.size  = sizeof(struct GUI_WIDGET_CLASS_S);
        info.class.ctor  = gui_widget_class_ctor;
        info.class.dtor  = gui_widget_class_dtor;
        info.inst.size   = sizeof(struct GUI_WIDGET_S);
        info.inst.ctor   = gui_widget_ctor;
        info.inst.dtor   = gui_widget_dtor;
        info.inst.params = cos_params(0);
        return cos_class_define(&info);
}

void gui_widget_class_ctor(COS_CLASS class)
{
        gui_widget_class = class;
        cos_super_class_ctor(COS_OBJECT_TYPE);
        GUI_WIDGET_CLASS_PRINT(class) = gui_widget_print_method;
}

void gui_widget_class_dtor(COS_CLASS class)
{
        cos_super_class_dtor(COS_OBJECT_TYPE);
        gui_widget_class = NULL;
}

void gui_widget_ctor(COS_OBJECT this, COS_VALUES values)
{
        cos_super_ctor(COS_OBJECT_TYPE, this);
        GUI_WIDGET_CHILD (this) = NULL;
        GUI_WIDGET_NEXT  (this) = NULL;
        GUI_WIDGET_LEFT  (this) = 0;
        GUI_WIDGET_TOP   (this) = 0;
        GUI_WIDGET_RIGHT (this) = 0;
        GUI_WIDGET_BOTTOM(this) = 0;
}

void gui_widget_dtor(COS_OBJECT this)
{
        GUI_WIDGET curr = GUI_WIDGET_CHILD(this), tmp;
        while (curr) {
                tmp = curr;
                curr = GUI_WIDGET_NEXT(tmp);
                cos_deref(tmp);
        }
        cos_super_dtor(COS_OBJECT_TYPE, this);
}

void gui_widget_append(GUI_WIDGET this, GUI_WIDGET child)
{
        GUI_WIDGET curr;
        if (GUI_WIDGET_CHILD(this)) {
                curr = GUI_WIDGET_CHILD(this);
                while (GUI_WIDGET_NEXT(curr)) curr = GUI_WIDGET_NEXT(curr);
                GUI_WIDGET_NEXT(curr) = cos_ref(child);
        } else GUI_WIDGET_CHILD(this) = cos_ref(child);
}

void gui_widget_print(GUI_WIDGET this)
{
        gui_widget_pr1nt(this, 0);
}

GUI_RECT gui_widget_rect(GUI_WIDGET this)
{
        return GUI_WIDGET_RECT(this);
}

int gui_widget_width(GUI_WIDGET this)
{
        return GUI_WIDGET_WIDTH(this);
}

int gui_widget_height(GUI_WIDGET this)
{
        return GUI_WIDGET_HEIGHT(this);
}
