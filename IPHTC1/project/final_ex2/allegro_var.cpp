#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "allegro_var.h"

Allegro_Var::Allegro_Var(int window_width, int window_height, double fps, char *title){
    this->window_width = window_width;
    this->window_height = window_height;
    this->fps = fps;
    this->title = title;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize Allegro!\n");
        // show_err_msg(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        // show_err_msg(-2);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        // show_err_msg(-3);
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        // show_err_msg(-4);
    }
    // Create display
    this->display = al_create_display(window_width, window_height);
    this->event_queue = al_create_event_queue();
    if (this->display == NULL || this->event_queue == NULL) {
        // show_err_msg(-5);
    }
    // Initialize Allegro settings
    al_set_window_position(this->display, 0, 0);
    al_set_window_title(this->display, title);
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Register event
    al_register_event_source(this->event_queue, al_get_display_event_source(this->display));
    al_register_event_source(this->event_queue, al_get_keyboard_event_source());
}
