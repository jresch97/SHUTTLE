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

#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "widget.h"

#define GUI_BUTTON_CLASS_NAME        "Button"
#define GUI_BUTTON_TYPE              (gui_button_class_get())
#define GUI_BUTTON_CAST(btn)         ((GUI_BUTTON)btn)
#define GUI_BUTTON_TEXT(btn)         (((GUI_BUTTON)btn)->text)
#define GUI_BUTTON_CLASS_CAST(class) ((GUI_BUTTON_CLASS)class)

typedef struct GUI_BUTTON_CLASS_S *GUI_BUTTON_CLASS;
typedef struct GUI_BUTTON_S       *GUI_BUTTON;

struct GUI_BUTTON_CLASS_S {
        struct GUI_WIDGET_CLASS_S class;
};

struct GUI_BUTTON_S {
        struct GUI_WIDGET_S widget;
        char *text;
};

COS_CLASS gui_button_class_get();
void      gui_button_class_ctor(COS_CLASS class);
void      gui_button_class_dtor(COS_CLASS class);
void      gui_button_ctor(COS_OBJECT this, COS_VALUES vals);
void      gui_button_dtor(COS_OBJECT this);

#endif
