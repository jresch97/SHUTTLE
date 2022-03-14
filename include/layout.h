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

#ifndef GUI_LAYOUT_H
#define GUI_LAYOUT_H

#include <cosine.h>

#include "type.h"

#define GUI_LAYOUT (gui_layout_class_get())

struct gui_layout_class_s {
        struct cos_class_s cls;
        void (*apply)(gui_layout, gui_widget);
};

struct gui_layout_s {
        struct cos_object_s obj;
};

cos_class gui_layout_class_get();
void      gui_layout_class_init(cos_class cls);
void      gui_layout_class_term(cos_class cls);
void      gui_layout_init(cos_object obj, cos_args args);
void      gui_layout_term(cos_object obj);
void      gui_layout_apply(gui_layout layout, gui_widget wdg);

#endif
