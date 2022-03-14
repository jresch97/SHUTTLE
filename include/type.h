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

#ifndef GUI_TYPE_H
#define GUI_TYPE_H

#include "rect.h"

typedef struct gui_framebuffer_s  *gui_framebuffer;
typedef struct gui_commands_s     *gui_commands;
typedef struct gui_widget_class_s *gui_widget_class;
typedef struct gui_widget_s       *gui_widget;
typedef struct gui_button_class_s *gui_button_class;
typedef struct gui_button_s       *gui_button;
typedef struct gui_layout_class_s *gui_layout_class;
typedef struct gui_layout_s       *gui_layout;

#endif
