#include <gtk/gtk.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


void on_button_clicked(GtkButton *button);
void image_flipper(GtkButton *button);
void gtk_widget_destroy (GtkWidget *widget);
void gtk_window_close (GtkWindow *window);
void infowin_close(GtkButton *button);
void on_helpbutton_clicked(GtkButton *button);
void on_settingsbutton_clicked(GtkButton *button);
void image_flipper_back(GtkButton *button);
void image_flipper_front(GtkButton *button);
void on_settingsingame_clicked(GtkButton *button);

void compare(GtkButton*button);




void game_mode(GtkButton *button);
void choose_level_multi(GtkButton *button);

void get_score(GtkWidget *button);
