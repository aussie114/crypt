#ifndef MAIN_H
#define MAIN_H

#define WINDOW                     widgets[ 0].obj
#define GRID                       widgets[ 1].obj
#define OUTPUT                     widgets[ 2].obj
#define TOP_KEYWORD_ENTRY          widgets[ 3].obj 
#define GENERATE_FROM_FILE_BUTTON  widgets[ 4].obj
#define SCROLLED_WINDOW            widgets[ 5].obj
#define SERVICE_ENTRY              widgets[ 6].obj
#define USERNAME_ENTRY             widgets[ 7].obj
#define LENGTH_ENTRY               widgets[ 8].obj
#define SPECIAL_ENTRY              widgets[ 9].obj
#define BOTTOM_KEYWORD_ENTRY       widgets[10].obj
#define GENERATE_SINGLE_BUTTON     widgets[11].obj

typedef struct {
	GtkWidget * obj;
	int x, y, w, h;
} widget;

#endif
