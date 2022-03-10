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

#include "label.h"
#include "param.h"
#include "value.h"

static void gui_lbl_print_method(GUI_WIDGET this)
{
        printf("[%4d,%4d,%4d,%4d] \"%s\"",
                GUI_WIDGET_LEFT(this),
                GUI_WIDGET_TOP(this),
                GUI_WIDGET_RIGHT(this),
                GUI_WIDGET_BOTTOM(this),
                GUI_LABEL_TEXT(this));
}

COS_CLASS gui_lbl_class_get()
{
        COS_CLASS class;
        COS_CLASS_INFO info;
        if (cos_class_lookup(GUI_LABEL_CLASS_NAME, &class)) return class;
        info.name        = GUI_LABEL_CLASS_NAME;
        info.parent      = GUI_WIDGET_TYPE;
        info.class.size  = sizeof(struct GUI_LABEL_CLASS_S);
        info.class.ctor  = gui_lbl_class_ctor;
        info.class.dtor  = gui_lbl_class_dtor;
        info.inst.size   = sizeof(struct GUI_LABEL_S);
        info.inst.ctor   = gui_lbl_ctor;
        info.inst.dtor   = gui_lbl_dtor;
        info.inst.params = cos_params(1, "text", COS_TYPE_C_STR);
        return cos_class_define(&info);
}

void gui_lbl_class_ctor(COS_CLASS class)
{
        cos_super_class_ctor(GUI_WIDGET_TYPE);
        GUI_WIDGET_CLASS_PRINT(class) = gui_lbl_print_method;
}

void gui_lbl_class_dtor(COS_CLASS class)
{
        cos_super_class_dtor(GUI_WIDGET_TYPE);
}

void gui_lbl_ctor(COS_OBJECT this, COS_VALUES vals)
{
        const char *text;
        cos_super_ctor(GUI_WIDGET_TYPE, this, GUI_LAYOUT_NONE);
        text = cos_unbox_c_str(cos_values_at(vals, 0));
        GUI_LABEL_TEXT(this) = malloc(strlen(text) + 1);
        strcpy(GUI_LABEL_TEXT(this), text);
}

void gui_lbl_dtor(COS_OBJECT this)
{
        if (GUI_LABEL_TEXT(this)) free(GUI_LABEL_TEXT(this));
        cos_super_dtor(GUI_WIDGET_TYPE, this);
}
