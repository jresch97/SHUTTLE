#ifndef GUI_TYPE_H
#define GUI_TYPE_H

enum GUI_LAYOUT_TYPES {
        GUI_LAYOUT_NONE,
        GUI_LAYOUT_VBOX,
        GUI_LAYOUT_HBOX
};

typedef struct GUI_FRAMEBUFFER_S *GUI_FRAMEBUFFER;
typedef struct GUI_COMMANDS_S    *GUI_COMMANDS;

typedef struct GUI_WIDGET_CLASS_S *GUI_WIDGET_CLASS;
typedef struct GUI_WIDGET_S       *GUI_WIDGET;

#endif
