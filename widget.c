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
#include "param.h"
#include "value.h"

static void gui_widget_print_method(GUI_WIDGET this)
{
        printf("[%4d,%4d,%4d,%4d] ~", this->rect.left,
                                      this->rect.top,
                                      this->rect.right,
                                      this->rect.bottom);
}

static void gui_widget_pr1nt(GUI_WIDGET this, int level)
{
        size_t i;
        GUI_WIDGET curr;
        for (i = 0; i < level; i++) printf("\t");
        GUI_WIDGET_CLASS_CAST(this->obj.class)->print(this);
        printf("\n");
        curr = this->child;
        while (curr) {
                gui_widget_pr1nt(curr, level + 1);
                curr = curr->next;
        }
}

COS_CLASS gui_widget_class_get()
{
        COS_CLASS class;
        COS_CLASS_INFO info;
        if (cos_class_lookup(GUI_WIDGET_CLASS_NAME, &class)) return class;
        info.name        = GUI_WIDGET_CLASS_NAME;
        info.parent      = COS_OBJECT_CLASS;
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
        cos_obj_class_ctor(class);
        GUI_WIDGET_CLASS_CAST(class)->print = gui_widget_print_method;
}

void gui_widget_class_dtor(COS_CLASS class)
{
        cos_obj_class_dtor(class);
}

void gui_widget_ctor(COS_OBJECT this, COS_VALUES values)
{
        GUI_WIDGET widget;
        cos_super(COS_OBJECT_CLASS, this);
        widget = GUI_WIDGET_CAST(this);
        widget->child = widget->next = NULL;
        widget->rect.left   = 0;
        widget->rect.top    = 0;
        widget->rect.right  = 0;
        widget->rect.bottom = 0;
}

void gui_widget_dtor(COS_OBJECT this)
{
        GUI_WIDGET widget, curr;
        widget = GUI_WIDGET_CAST(this);
        curr = widget->child;
        while (curr) {
                cos_deref(curr);
                curr = curr->next;
        }
}

void gui_widget_append(GUI_WIDGET this, GUI_WIDGET child)
{
        GUI_WIDGET curr;
        if (this->child) {
                curr = this->child;
                while (curr->next) curr = curr->next;
                curr->next = cos_ref(child);
        } else this->child = cos_ref(child);
}

void gui_widget_print(GUI_WIDGET this)
{
        gui_widget_pr1nt(this, 0);
}

int gui_widget_width(GUI_WIDGET this)
{
        return GUI_RECT_WIDTH(this->rect);
}

int gui_widget_height(GUI_WIDGET this)
{
        return GUI_RECT_HEIGHT(this->rect);
}
