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

#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#include "widget.h"

typedef struct GUI_LABEL_CLASS_S *GUI_LABEL_CLASS_T;
typedef struct GUI_LABEL_S       *GUI_LABEL;

#define GUI_LABEL_CLASS             (gui_label_class_get())
#define GUI_LABEL_CLASS_NAME        "Label"
#define GUI_LABEL_CLASS_CAST(class) ((GUI_LABEL_CLASS_T)class)

struct GUI_LABEL_CLASS_S {
        struct COS_CLASS_S class;
};

COS_CLASS gui_label_class_get();
void      gui_label_class_ctor(COS_CLASS class);
void      gui_label_class_dtor(COS_CLASS class);

#define GUI_LABEL_CAST(obj) ((GUI_LABEL)obj)

struct GUI_LABEL_S {
        struct GUI_WIDGET_S widget;
        char *text;
};

void gui_label_ctor(COS_OBJECT this, COS_VALUES values);
void gui_label_dtor(COS_OBJECT this);

#endif
