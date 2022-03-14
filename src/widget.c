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

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widget.h"
#include "layout.h"

static cos_class g_cls = NULL;

static int gui_rand_color()
{
        return (rand() % 256 << 16) +
               (rand() % 256 <<  8) +
               (rand() % 256 <<  0);
}

static void _gui_widget_print(gui_widget wdg)
{
        printf("[%4d,%4d,%4d,%4d] ~",
                wdg->rect.left,
                wdg->rect.top,
                wdg->rect.right,
                wdg->rect.bottom);
}

static void _gui_widget_paint(gui_widget wdg, gui_rect rect, void *px)
{
        int x, y, w;
        w = GUI_RECT_WIDTH(rect);
        for (y = wdg->rect.top; y < wdg->rect.bottom; y++) {
                for (x = wdg->rect.left; x < wdg->rect.right; x++) {
                        ((int*)px)[x + y * w] = wdg->color;
                }
        }
}

gui_widget gui_new_widget(gui_layout layout)
{
        return cos_new(GUI_WIDGET, layout);
}

cos_class gui_widget_class_get()
{
        cos_class_spec spec;
        if (g_cls) return g_cls;
        spec.cls_name = "GUI_WIDGET";
        spec.parent_cls = COS_OBJECT;
        spec.cls_size = sizeof(struct gui_widget_class_s);
        spec.obj_size = sizeof(struct gui_widget_s);
        spec.cls_init_fn = gui_widget_class_init;
        spec.cls_term_fn = gui_widget_class_term;
        spec.obj_init_fn = gui_widget_init;
        spec.obj_term_fn = gui_widget_term;
        return cos_def_class(&spec);
}

void gui_widget_class_init(cos_class cls)
{
        gui_widget_class wdgcls;
        if (!g_cls) g_cls = cls;
        wdgcls = (gui_widget_class)cls;
        wdgcls->print = _gui_widget_print;
        wdgcls->draw = NULL;/*_gui_widget_draw;*/
        wdgcls->paint = _gui_widget_paint;
}

void gui_widget_class_term(cos_class cls)
{
        if (g_cls == cls) g_cls = NULL;
}

void gui_widget_init(cos_object obj, cos_args args)
{
        gui_widget wdg;
        cos_super(COS_OBJECT, obj);
        wdg = (gui_widget)obj;
        wdg->parent = wdg->child = wdg->next = NULL;
        wdg->layout = cos_arg(args, gui_layout);
        memset(&wdg->rect, 0, sizeof(wdg->rect));
        wdg->color = gui_rand_color();
}

void gui_widget_term(cos_object obj)
{
        gui_widget wdg, curr, tmp;
        wdg = (gui_widget)obj;
        curr = wdg->child;
        while (curr) {
                tmp = curr;
                curr = curr->next;
                cos_deref(tmp);
        }
        cos_deref_many(3, wdg->parent, wdg->next, wdg->layout);
}

void gui_widget_add(gui_widget wdg, gui_widget child)
{
        gui_widget curr;
        curr = wdg->child;
        if (curr) {
                while (curr->next) curr = curr->next;
                curr->next = child;
        } else wdg->child = child;
}

void gui_widget_add_many(gui_widget wdg, size_t n, ...)
{
        size_t i;
        va_list args;
        va_start(args, n);
        for (i = 0; i < n; i++) {
                gui_widget_add(wdg, va_arg(args, gui_widget));
        }
        va_end(args);
}

static void gui_widget_pr1nt(gui_widget wdg, int lvl)
{
        size_t i;
        gui_widget curr;
        for (i = 0; i < lvl; i++) printf("\t");
        ((gui_widget_class)cos_class_of(wdg))->print(wdg);
        printf("\n");
        curr = wdg->child;
        while (curr) {
                gui_widget_pr1nt(curr, lvl + 1);
                curr = curr->next;
        }
}

void gui_widget_print(gui_widget wdg)
{
        gui_widget_pr1nt(wdg, 0);
}

void gui_widget_layout(gui_widget wdg)
{
        gui_widget curr;
        if (wdg->layout) gui_layout_apply(wdg->layout, wdg);
        curr = wdg->child;
        while (curr) {
                gui_widget_layout(curr);
                curr = curr->next;
        }
}

void gui_widget_resize(gui_widget wdg, gui_rect rect)
{
        wdg->rect = rect;
        gui_widget_layout(wdg);
}

void gui_widget_paint(gui_widget wdg, gui_rect rect, void *px)
{
        gui_widget curr;
        ((gui_widget_class)cos_class_of(wdg))->paint(wdg, rect, px);
        curr = wdg->child;
        while (curr) {
                gui_widget_paint(curr, rect, px);
                curr = curr->next;
        }
}