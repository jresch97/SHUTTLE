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
        GUI_WIDGET widget, button, label;
        
        if (!cos_init()) return EXIT_FAILURE;
        
        widget = cos_new(GUI_WIDGET_TYPE);
        button = cos_new(GUI_BUTTON_TYPE, "Hello Button");
        label  = cos_new(GUI_LABEL_TYPE,  "Hello Label");
        
        gui_widget_append(widget, button);
        gui_widget_append(widget, label);
        
        gui_widget_print(widget);
        
        cos_deref_many(3, button, widget, label);
        
        cos_term();
        
        return EXIT_SUCCESS;
}
