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

#ifndef GUI_HBOX_H
#define GUI_HBOX_H

#include <cosine.h>

#include "type.h"
#include "layout.h"

#define GUI_HBOX_NAME            "HBox"
#define GUI_HBOX                 (gui_hbox_class_get())
#define GUI_HBOX_CAST(obj)       ((gui_hbox)obj)
#define GUI_HBOX_CLASS_CAST(cls) ((gui_hbox_class)cls)
#define GUI_HBOX_PADDING(obj)    GUI_HBOX_CAST(obj)->padding
#define GUI_HBOX_SPACING(obj)    GUI_HBOX_CAST(obj)->spacing

struct gui_hbox_class_s {
        struct gui_layout_class_s cls;
};

struct gui_hbox_s {
        struct gui_layout_s obj;
        gui_rect padding;
        int spacing;
};

cos_class gui_hbox_class_get();
void      gui_hbox_class_construct(cos_class cls);
void      gui_hbox_class_destruct(cos_class cls);
void      gui_hbox_construct(cos_object obj, cos_values vals);
void      gui_hbox_destruct(cos_object obj);

#endif
