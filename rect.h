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

#ifndef GUI_RECT_H
#define GUI_RECT_H

typedef struct GUI_RECT_S { int left, top, right, bottom; } GUI_RECT;

#define GUI_RECT_WIDTH(rect)  (rect.right - rect.left)
#define GUI_RECT_HEIGHT(rect) (rect.bottom - rect.top)

#endif
