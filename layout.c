#include <stdio.h>
#include <stdlib.h>

#include "layout.h"
#include "widget.h"

void gui_layout_vbox(GUI_WIDGET widget)
{
        int y, dy, n_child = 0;
        GUI_WIDGET curr;
        curr = GUI_WIDGET_CHILD(widget);
        while (curr) {
                curr = GUI_WIDGET_NEXT(curr);
                n_child++;
        }
        y = GUI_WIDGET_TOP(widget);
        dy = GUI_WIDGET_HEIGHT(widget) / n_child;
        curr = GUI_WIDGET_CHILD(widget);
        while (curr) {
                GUI_WIDGET_LEFT(curr) = GUI_WIDGET_LEFT(widget);
                GUI_WIDGET_RIGHT(curr) = GUI_WIDGET_RIGHT(widget);
                GUI_WIDGET_TOP(curr) = y;
                y += dy;
                GUI_WIDGET_BOTTOM(curr) = y;
                curr = GUI_WIDGET_NEXT(curr);
        }
}

void gui_layout_hbox(GUI_WIDGET widget)
{
        int x, dx, n_child = 0;
        GUI_WIDGET curr;
        curr = GUI_WIDGET_CHILD(widget);
        while (curr) {
                curr = GUI_WIDGET_NEXT(curr);
                n_child++;
        }
        x = GUI_WIDGET_LEFT(widget);
        dx = GUI_WIDGET_WIDTH(widget) / n_child;
        curr = GUI_WIDGET_CHILD(widget);
        while (curr) {
                GUI_WIDGET_TOP(curr) = GUI_WIDGET_TOP(widget);
                GUI_WIDGET_BOTTOM(curr) = GUI_WIDGET_BOTTOM(widget);
                GUI_WIDGET_LEFT(curr) = x;
                x += dx;
                GUI_WIDGET_RIGHT(curr) = x;
                curr = GUI_WIDGET_NEXT(curr);
        }
}
