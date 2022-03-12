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
#include "rect.h"

/*
 * Design:
 *
 * Widgets have multiple methods of drawing available.
 *
 * The first is calling draw() which issues draw commands to a buffer/queue.
 *
 * Cached Software Rendering (CSR) uses the draw commands to determine which
 * tiles of the screen need redrawn, combines the tiles into larger rectangles,
 * and then issues calls to paint() clipped to those regions.
 *
 * The draw commands can also be transformed into GPU instructions to perform
 * hardware rendering using an alternate backend renderer.
 *
 * The second is calling paint() which paints pixels in a region of the
 * framebuffer directly.
 *
 * CSR determines the regions which need redrawn and clips the widget geometry
 * such that only areas of the screen which need repainted are painted.
 *
 */

#define GUI_WIDGET_NAME             "Widget"
#define GUI_WIDGET                  (gui_widget_class_get())
#define GUI_WIDGET_CAST(obj)        ((gui_widget)obj)
#define GUI_WIDGET_CLASS_CAST(cls)  ((gui_widget_class)cls)
#define GUI_WIDGET_RECT(obj)        GUI_WIDGET_CAST(obj)->rect
#define GUI_WIDGET_LEFT(obj)        GUI_WIDGET_RECT(obj).left
#define GUI_WIDGET_TOP(obj)         GUI_WIDGET_RECT(obj).top
#define GUI_WIDGET_RIGHT(obj)       GUI_WIDGET_RECT(obj).right
#define GUI_WIDGET_BOTTOM(obj)      GUI_WIDGET_RECT(obj).bottom
#define GUI_WIDGET_PARENT(obj)      GUI_WIDGET_CAST(obj)->parent
#define GUI_WIDGET_CHILD(obj)       GUI_WIDGET_CAST(obj)->child
#define GUI_WIDGET_NEXT(obj)        GUI_WIDGET_CAST(obj)->next
#define GUI_WIDGET_LAYOUT(obj)      GUI_WIDGET_CAST(obj)->layout
#define GUI_WIDGET_WIDTH(obj)       (GUI_RECT_WIDTH(GUI_WIDGET_RECT(obj)))
#define GUI_WIDGET_HEIGHT(obj)      (GUI_RECT_HEIGHT(GUI_WIDGET_RECT(obj)))
#define GUI_WIDGET_PRINT(obj)       (GUI_WIDGET_CLASS_PRINT(COS_OBJECT_CLASS(obj))(obj))
#define GUI_WIDGET_CLASS_PRINT(cls) GUI_WIDGET_CLASS_CAST(cls)->print
#define GUI_WIDGET_CLASS_DRAW(cls)  GUI_WIDGET_CLASS_CAST(cls)->draw
#define GUI_WIDGET_CLASS_PAINT(cls) GUI_WIDGET_CLASS_CAST(cls)->paint

struct gui_widget_class_s {
        struct cos_class_s cls;
        void (*print)(gui_widget);
        void (*draw) (gui_widget, gui_commands);
        void (*paint)(gui_widget, gui_framebuffer, gui_rect);
};

struct gui_widget_s {
        struct cos_object_s obj;
        gui_widget          parent, child, next;
        gui_rect            rect;
        gui_layout          layout;
};

cos_class gui_widget_class_get();
void      gui_widget_class_construct(cos_class cls);
void      gui_widget_class_destruct(cos_class cls);
void      gui_widget_construct(cos_object obj, cos_values vals);
void      gui_widget_destruct(cos_object obj);
void      gui_widget_add(gui_widget parent, gui_widget child);
void      gui_widget_many(gui_widget parent, size_t n, ...);
void      gui_widget_print(gui_widget wdg);
void      gui_widget_draw(gui_widget wdg, gui_commands out);
void      gui_widget_paint(gui_widget wdg, gui_framebuffer fb, gui_rect rect);
void      gui_widget_layout(gui_widget wdg);
void      gui_widget_resize(gui_widget wdg, gui_rect rect);

#endif
