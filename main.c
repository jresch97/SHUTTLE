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

#include "gui.h"

int main(void)
{
        gui_rect   screen_rect;
        gui_widget root, widget1, widget2;
        /*
        gui_widget label1, label2, button1, button2;
        */
        
        if (!cos_init()) return EXIT_FAILURE;

        screen_rect.left  = screen_rect.top = 0;
        screen_rect.right = 640, screen_rect.bottom = 480;

        root    = cos_new(GUI_WIDGET);
        widget1 = cos_new(GUI_WIDGET);
        widget2 = cos_new(GUI_WIDGET);

        /*
        label1  = cos_new(GUI_LABEL,  "Label 1");
        label2  = cos_new(GUI_LABEL,  "Label 2");
        button1 = cos_new(GUI_BUTTON, "Button 1");
        button2 = cos_new(GUI_BUTTON, "Button 2");
        */

        gui_widget_add_many(root,    2, widget1, widget2);
        /*
        gui_widget_add_many(widget1, 2, label1, button1);
        gui_widget_add_many(widget2, 2, label2, button2);
        */

        gui_widget_resize(root, screen_rect);
        gui_widget_print(root);
        
        cos_deref_many(3, root, widget1, widget2);
        
        /*
        cos_deref_many(4, button1, button2, label1, label2);
        */

        cos_term();
        
        return EXIT_SUCCESS;
}
