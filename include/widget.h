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

#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <cosine.h>

#include "type.h"

#define GUI_WIDGET (gui_widget_class_get())

struct gui_widget_class_s {
        struct cos_class_s cls;
        void (*print)(gui_widget);
        void (*draw)(gui_widget, gui_commands);
        void (*paint)(gui_widget, gui_rect, void *px);
};

struct gui_widget_s {
        struct cos_object_s obj;
        gui_widget parent;
        gui_widget child;
        gui_widget next;
        gui_layout layout;
        gui_rect   rect;
        int        color;
};

gui_widget gui_new_widget(gui_layout layout);
cos_class  gui_widget_class_get();
void       gui_widget_class_init(cos_class cls);
void       gui_widget_class_term(cos_class cls);
void       gui_widget_init(cos_object obj, cos_args args);
void       gui_widget_term(cos_object obj);
void       gui_widget_add(gui_widget wdg, gui_widget child);
void       gui_widget_add_many(gui_widget wdg, size_t n, ...);
void       gui_widget_layout(gui_widget wdg);
void       gui_widget_resize(gui_widget wdg, gui_rect rect);
void       gui_widget_print(gui_widget wdg);
void       gui_widget_draw(gui_widget wdg, gui_commands out);
void       gui_widget_paint(gui_widget wdg, gui_rect rect, void *px);

#endif
