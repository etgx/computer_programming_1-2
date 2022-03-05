
#ifndef ALLEGRO_VAR_H // include guard
#define ALLEGRO_VAR_H

class Allegro_Var{
    public:
        Allegro_Var(int window_width, int window_height, double fps, char *title);

        int window_width;
        int window_height;
        double fps;
        char *title;
        ALLEGRO_DISPLAY* display = NULL;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_BITMAP *image = NULL;
        ALLEGRO_BITMAP *image2 = NULL;
        ALLEGRO_BITMAP *image3 = NULL;
        ALLEGRO_BITMAP *background = NULL;
        ALLEGRO_KEYBOARD_STATE keyState ;
        ALLEGRO_TIMER *timer = NULL;
        ALLEGRO_TIMER *timer2 = NULL;
        ALLEGRO_TIMER *timer3 = NULL;
        ALLEGRO_SAMPLE *song=NULL;
        ALLEGRO_FONT *font = NULL;
};


#endif
