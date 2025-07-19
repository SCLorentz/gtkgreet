#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <gtk/gtk.h>
#include <fstream>

#include "gtkgreet.h"
//#include "config.h"

using namespace std;

extern "C" {

int config_update_command_selector(GtkWidget *combobox)
{
    int entries = 0;
    if (gtkgreet->command != NULL) {
        gtk_combo_box_text_append((GtkComboBoxText*)combobox, NULL, gtkgreet->command);
    	entries++;
    }

    char buffer[255];
    ifstream fp("/etc/greetd/environments");
    if (!fp) return entries;

    while(fp.getline(buffer, 256))
    {
        size_t len = strlen(buffer);
        if (len > 0 && len < 255 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        if (gtkgreet->command != NULL && strcmp(gtkgreet->command, buffer) == 0)
        	continue;

        gtk_combo_box_text_append((GtkComboBoxText*)combobox, NULL, buffer);
        entries++;
    }

    fp.close();
    return entries;
}

}