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

#include <stdio.h>
#include <stdlib.h>

#include <cosine.h>

#include "widget.h"
#include "button.h"
#include "label.h"

int main(void)
{
        GUI_RECT rect;
        GUI_WIDGET widget1, widget2, widget3, button1, button2, label1, label2;
        if (!cos_init()) return EXIT_FAILURE;
        rect.left = rect.top = 0, rect.right = 640, rect.bottom = 480;
        widget1 = cos_new(GUI_WIDGET_TYPE, GUI_LAYOUT_VBOX);
        widget2 = cos_new(GUI_WIDGET_TYPE, GUI_LAYOUT_HBOX);
        widget3 = cos_new(GUI_WIDGET_TYPE, GUI_LAYOUT_HBOX);
        button1 = cos_new(GUI_BUTTON_TYPE, "Button 1");
        label1 = cos_new(GUI_LABEL_TYPE, "Label 1");
        button2 = cos_new(GUI_BUTTON_TYPE, "Button 2");
        label2 = cos_new(GUI_LABEL_TYPE, "Label 2");
        gui_wdg_append(widget1, widget2);
        gui_wdg_append(widget1, widget3);
        gui_wdg_append(widget2, button1);
        gui_wdg_append(widget2, label1);
        gui_wdg_append(widget3, button2);
        gui_wdg_append(widget3, label2);
        gui_wdg_resize(widget1, rect);
        gui_wdg_print(widget1);
        cos_deref_many(7, widget1, widget2, widget3, button1, button2, label1, label2);
        cos_term();
        return EXIT_SUCCESS;
}
