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

#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <object.h>

#include "rect.h"

typedef struct GUI_WIDGET_CLASS_S *GUI_WIDGET_CLASS_T;
typedef struct GUI_WIDGET_S       *GUI_WIDGET;

#define GUI_WIDGET_CLASS             (gui_widget_class_get())
#define GUI_WIDGET_CLASS_NAME        "Widget"
#define GUI_WIDGET_CLASS_CAST(class) ((GUI_WIDGET_CLASS_T)class)

struct GUI_WIDGET_CLASS_S {
        struct COS_CLASS_S class;
        void (*print)(GUI_WIDGET);
};

COS_CLASS gui_widget_class_get();
void      gui_widget_class_ctor(COS_CLASS class);
void      gui_widget_class_dtor(COS_CLASS class);

#define GUI_WIDGET_CAST(obj) ((GUI_WIDGET)obj)

struct GUI_WIDGET_S {
        struct COS_OBJECT_S obj;
        GUI_WIDGET child, next;
        GUI_RECT rect;
};

void gui_widget_ctor(COS_OBJECT this, COS_VALUES values);
void gui_widget_dtor(COS_OBJECT this);
void gui_widget_append(GUI_WIDGET this, GUI_WIDGET child);
void gui_widget_print(GUI_WIDGET this);
int  gui_widget_width(GUI_WIDGET this);
int  gui_widget_height(GUI_WIDGET this);

#endif
