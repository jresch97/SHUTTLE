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

#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "widget.h"

#define GUI_BUTTON_NAME            "Button"
#define GUI_BUTTON                 (gui_button_class_get())
#define GUI_BUTTON_CAST(obj)       ((gui_button)obj)
#define GUI_BUTTON_CLASS_CAST(cls) ((gui_button_class)cls)
#define GUI_BUTTON_TEXT(obj)       GUI_BUTTON_CAST(obj)->text

typedef struct gui_button_class_s *gui_button_class;
typedef struct gui_button_s       *gui_button;

struct gui_button_class_s {
        struct gui_widget_class_s cls;
};

struct gui_button_s {
        struct gui_widget_s wdg;
        char *text;
};

cos_class gui_button_class_get();
void      gui_button_class_construct(cos_class cls);
void      gui_button_class_destruct(cos_class cls);
void      gui_button_construct(cos_object obj, cos_values vals);
void      gui_button_destruct(cos_object obj);

#endif
