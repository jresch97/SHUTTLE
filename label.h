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

#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#include "widget.h"

#define GUI_LABEL_NAME            "Label"
#define GUI_LABEL                 (gui_label_class_get())
#define GUI_LABEL_CAST(obj)       ((gui_label)obj)
#define GUI_LABEL_CLASS_CAST(cls) ((gui_label_class)cls)
#define GUI_LABEL_TEXT(obj)       (GUI_LABEL_CAST(obj)->text)

typedef struct gui_label_class_s *gui_label_class;
typedef struct gui_label_s       *gui_label;

struct gui_label_class_s {
        struct gui_widget_class_s cls;
};

struct gui_label_s {
        struct gui_widget_s widget;
        char               *text;
};

cos_class   gui_label_class_get();
void        gui_label_class_construct(cos_class cls);
void        gui_label_class_destruct(cos_class cls);
void        gui_label_construct(cos_object obj, cos_values vals);
void        gui_label_destruct(cos_object obj);
const char *gui_label_text(gui_label label);

#endif
