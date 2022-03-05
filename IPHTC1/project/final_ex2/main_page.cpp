#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "main_page.h"

void main_page(ALLEGRO_DISPLAY **display, ALLEGRO_SAMPLE **song, ALLEGRO_FONT **font, const int width, const int height){
    printf("Here is main_page\n");

    // Load sound
    /**
    song = al_load_sample( "hello.wav" );
    if (!song){
        printf( "Audio clip sample not loaded!\n" );
        // show_err_msg(-6);
    }**/
    // Loop the song until the display closes
    // al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    al_clear_to_color(al_map_rgb(100,100,100));
    // Load and draw text
    (*font) = al_load_ttf_font("pirulen.ttf",12,0);
    al_draw_text(*font, al_map_rgb(255,255,255), width/2, height/2+100 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_text(*font, al_map_rgb(255,255,255), width/2, height/2+150 , ALLEGRO_ALIGN_CENTRE, "Press 'Esc' to exit");
    al_draw_text(*font, al_map_rgb(255,255,255), width/2, height/2+200 , ALLEGRO_ALIGN_CENTRE, "Press 'Q' for more detail");
    al_draw_rectangle(width/2-150, height/2+88, width/2+150, height/2+124, al_map_rgb(255, 255, 255), 0);
    al_draw_rectangle(width/2-150, height/2+138, width/2+150, height/2+174, al_map_rgb(255, 255, 255), 0);
    al_draw_rectangle(width/2-150, height/2+188, width/2+150, height/2+224, al_map_rgb(255, 255, 255), 0);
    al_flip_display();
}
