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

#include "button.h"
#include "param.h"
#include "value.h"

static void gui_button_print_method(GUI_WIDGET this)
{
        printf("[%4d,%4d,%4d,%4d] [%s]", this->rect.left,
                                         this->rect.top,
                                         this->rect.right,
                                         this->rect.bottom,
                                         GUI_BUTTON_CAST(this)->text);
}

COS_CLASS gui_button_class_get()
{
        COS_CLASS class;
        COS_CLASS_INFO info;
        if (cos_class_lookup(GUI_BUTTON_CLASS_NAME, &class)) return class;
        info.name        = GUI_BUTTON_CLASS_NAME;
        info.parent      = GUI_WIDGET_CLASS;
        info.class.size  = sizeof(struct GUI_BUTTON_CLASS_S);
        info.class.ctor  = gui_button_class_ctor;
        info.class.dtor  = gui_button_class_dtor;
        info.inst.size   = sizeof(struct GUI_BUTTON_S);
        info.inst.ctor   = gui_button_ctor;
        info.inst.dtor   = gui_button_dtor;
        info.inst.params = cos_params(1, "text", COS_TYPE_C_STR);
        return cos_class_define(&info);
}

void gui_button_class_ctor(COS_CLASS class)
{
        gui_widget_class_ctor(class);
        GUI_WIDGET_CLASS_CAST(class)->print = gui_button_print_method;
}

void gui_button_class_dtor(COS_CLASS class)
{
        gui_widget_class_dtor(class);
}

void gui_button_ctor(COS_OBJECT this, COS_VALUES values)
{
        GUI_BUTTON button;
        const char *text;
        cos_super(GUI_WIDGET_CLASS, this);
        button = GUI_BUTTON_CAST(this);
        text = cos_unbox_c_str(cos_values_at(values, 0));
        button->text = malloc(strlen(text) + 1);
        strcpy(button->text, text);
}

void gui_button_dtor(COS_OBJECT this)
{
        free(GUI_BUTTON_CAST(this)->text);
        gui_widget_dtor(this);
}
