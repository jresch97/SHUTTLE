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

#include "type.h"
#include "rect.h"
#include "layout.h"

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

#define GUI_WIDGET_CLASS_NAME         "Widget"
#define GUI_WIDGET_TYPE               (gui_wdg_class_get())
#define GUI_WIDGET_CAST(wdg)          ((GUI_WIDGET)wdg)
#define GUI_WIDGET_CLASS(wdg)         ((GUI_WIDGET_CLASS)wdg->obj.class)
#define GUI_WIDGET_RECT(wdg)          (((GUI_WIDGET)wdg)->rect)
#define GUI_WIDGET_LEFT(wdg)          (((GUI_WIDGET)wdg)->rect.left)
#define GUI_WIDGET_TOP(wdg)           (((GUI_WIDGET)wdg)->rect.top)
#define GUI_WIDGET_RIGHT(wdg)         (((GUI_WIDGET)wdg)->rect.right)
#define GUI_WIDGET_BOTTOM(wdg)        (((GUI_WIDGET)wdg)->rect.bottom)
#define GUI_WIDGET_WIDTH(wdg)         (((GUI_WIDGET)wdg)->rect.right - \
                                       ((GUI_WIDGET)wdg)->rect.left)
#define GUI_WIDGET_HEIGHT(wdg)        (((GUI_WIDGET)wdg)->rect.bottom - \
                                       ((GUI_WIDGET)wdg)->rect.top)
#define GUI_WIDGET_CHILD(wdg)         (((GUI_WIDGET)wdg)->child)
#define GUI_WIDGET_NEXT(wdg)          (((GUI_WIDGET)wdg)->next)
#define GUI_WIDGET_LAYOUT(wdg)        (((GUI_WIDGET)wdg)->layout)
#define GUI_WIDGET_CLASS_CAST(class)  ((GUI_WIDGET_CLASS)class)
#define GUI_WIDGET_CLASS_PRINT(class) (((GUI_WIDGET_CLASS)class)->print)
#define GUI_WIDGET_CLASS_DRAW(class)  (((GUI_WIDGET_CLASS)class)->draw)
#define GUI_WIDGET_CLASS_PAINT(class) (((GUI_WIDGET_CLASS)class)->paint)

struct GUI_WIDGET_CLASS_S {
        struct COS_CLASS_S class;
        void (*print)(GUI_WIDGET);
        void  (*draw)(GUI_WIDGET, GUI_COMMANDS);
        void (*paint)(GUI_WIDGET, GUI_FRAMEBUFFER, GUI_RECT);
};

struct GUI_WIDGET_S {
        struct COS_OBJECT_S obj;
        GUI_WIDGET          child, next;
        GUI_RECT            rect;
        int                 layout;
};

COS_CLASS gui_wdg_class_get();
void      gui_wdg_class_ctor(COS_CLASS class);
void      gui_wdg_class_dtor(COS_CLASS class);
void      gui_wdg_ctor(COS_OBJECT this, COS_VALUES values);
void      gui_wdg_dtor(COS_OBJECT this);
void      gui_wdg_append(GUI_WIDGET this, GUI_WIDGET child);
void      gui_wdg_print(GUI_WIDGET this);
void      gui_wdg_draw(GUI_WIDGET this, GUI_COMMANDS out);
void      gui_wdg_paint(GUI_WIDGET this, GUI_FRAMEBUFFER fb, GUI_RECT rect);
GUI_RECT  gui_wdg_rect(GUI_WIDGET this);
int       gui_wdg_width(GUI_WIDGET this);
int       gui_wdg_height(GUI_WIDGET this);
void      gui_wdg_layout(GUI_WIDGET this);
void      gui_wdg_resize(GUI_WIDGET this, GUI_RECT rect);

#endif
