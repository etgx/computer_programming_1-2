
#ifndef STAGE_H // include guard
#define STAGE_H

#include <vector>
#include "game_body.h"

class Stage{
    public:
        Stage(const int width, const int height);
        ~Stage();
        int init();
        int terminate();
        int destroy();
        void show_err(int msg);
        void main_page();
        void about_page();
        void page(int is_win, char *img_path, int is_last_page);
        void run();
        int is_current_level_over();
        int is_win();
        int set_window(int window_code, int is_conti_update);
        int updater(ALLEGRO_EVENT event);
        int set_game_over();
        void delete_current_stage();
        void delete_roles();
        // Upgrade
        void upgrade_atk(int);
        void upgrade_hp(int);
        void clear_upgrade();
        // Set up stages
        void set_up_stage1();
        void show_stage1();
        void set_up_stage2();
        void show_stage2();
        void set_up_stage3();
        void show_stage3();
        void set_up_stage4();
        void show_stage4();
        void set_up_stage5();
        void show_stage5();

        int _stage();
        int _window();
        Role *_hero();
        Role *_client();
        ALLEGRO_EVENT_QUEUE *_event_queue();
        ALLEGRO_DISPLAY *_display();
        ALLEGRO_SAMPLE *_song();
        ALLEGRO_FONT *_font();
        ALLEGRO_BITMAP *_background();
    protected:
        int width;
        int height;
        int window;
        int stage;
        int hero_add_hp;
        int hero_add_atk;
        int is_able_upgrade;
        int is_terminate;
        int is_continue_update;
        int is_able_next_page;
        int is_stage_setup;
        int is_in_about_page;
        Role *hero;
        Role *client;
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_DISPLAY *display;
        ALLEGRO_SAMPLE *song;
        ALLEGRO_FONT *font;
        ALLEGRO_BITMAP *background;

};
#endif
