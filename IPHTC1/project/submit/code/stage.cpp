
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "stage.h"
#include "game_body.h"

Stage::Stage(const int width, const int height){
    this->width = width;
    this->height = height;
    this->window = 0;
    this->is_terminate = 0;
    this->is_continue_update = 1;
    this->is_able_next_page = 1;
    this->stage = 1;
    this->hero_add_hp = 0;
    this->hero_add_atk = 0;
    this->is_able_upgrade = 0;
    this->is_stage_setup = 0;
    this->is_in_about_page = 0;

    this->hero = NULL;
    this->client = NULL;
    this->hero = NULL;
    this->client = NULL;
    this->event_queue = NULL;
    this->display = NULL;
    this->song = NULL;
    this->font = NULL;
    this->background = NULL;
}
Stage::~Stage(){
    delete(this->hero);
    delete(this->client);
    delete(this->event_queue);
    delete(this->display);
    delete(this->song);
    delete(this->font);
    delete(this->background);
}
int Stage::init(){
    if (!al_init()) {
        this->show_err(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        this->show_err(-2);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        this->show_err(-3);
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        this->show_err(-4);
    }
    // Create display
    this->display = al_create_display(this->width, this->height);
    this->event_queue = al_create_event_queue();
    if (this->display == NULL || this->event_queue == NULL) {
        this->show_err(-5);
    }
    // Initialize Allegro settings
    al_set_window_position(this->display, 0, 0);
    al_set_window_title(this->display, "Corporate Slave's Counterattack");
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
int Stage::terminate(){
    this->is_terminate = 1;
    return 1;
}
int Stage::destroy(){
    // Make sure you destroy all things
    al_destroy_event_queue(this->event_queue);
    al_destroy_display(this->display);
    al_destroy_sample(this->song);
    al_destroy_font(this->font);
}
void Stage::show_err(int msg){
    fprintf(stderr, "unexpected msg: %d\n", msg);
    this->destroy();
    exit(9);
}
void Stage::main_page(){
    printf("Here is main_page\n");

    // Load sound
    song = al_load_sample( "./song/cs.wav" );
    if (!this->song){
        printf( "Audio clip sample not loaded!\n" );
        // show_err_msg(-6);
    }
    // Loop the song until the display closes
    al_play_sample(this->song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    al_clear_to_color(al_map_rgb(234,193,000));
    // Load and draw text
    this->font = al_load_ttf_font("./font/lemon_juice.otf",30,0);
    al_draw_text(this->font, al_map_rgb(255,88,9), this->width/2, this->height/2-100 , ALLEGRO_ALIGN_CENTRE, "corporate slave's");
    al_draw_text(this->font, al_map_rgb(255,88,9), this->width/2, this->height/2-80 , ALLEGRO_ALIGN_CENTRE, "counterattack");
    al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2+100 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2+150 , ALLEGRO_ALIGN_CENTRE, "Press 'Esc' to exit");
    al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2+200 , ALLEGRO_ALIGN_CENTRE, "Press 'Q' for more detail");
    al_draw_rectangle(this->width/2 - 180, this->height/2 + 100, this->width/2 + 180, this->height/2 + 136, al_map_rgb(255, 255, 255), 0);
    al_draw_rectangle(this->width/2 - 180, this->height/2 + 150, this->width/2 + 180, this->height/2 + 186, al_map_rgb(255, 255, 255), 0);
    al_draw_rectangle(this->width/2 - 180, this->height/2 + 200, this->width/2 + 180, this->height/2 + 236, al_map_rgb(255, 255, 255), 0);
    al_flip_display();
}
void Stage::about_page(){
    printf("Here is main_page\n");

    // Load sound
    /**
    song = al_load_sample( "./song/cs.wav" );
    if (!this->song){
        printf( "Audio clip sample not loaded!\n" );
        // show_err_msg(-6);
    }
    // Loop the song until the display closes
    al_play_sample(this->song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    **/
    al_clear_to_color(al_map_rgb(234,193,000));
    // Load and draw text
    //this->font = al_load_ttf_font("./font/lemon_juice.otf",30,0);
    al_draw_text(this->font, al_map_rgb(255,88,9), this->width/2, this->height/2-100 , ALLEGRO_ALIGN_CENTRE, "corporate slave's");
    al_draw_text(this->font, al_map_rgb(255,88,9), this->width/2, this->height/2-80 , ALLEGRO_ALIGN_CENTRE, "counterattack");
    al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2+100 , ALLEGRO_ALIGN_CENTRE, "NTHU Computer Programming Final Project");
    al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2+150 , ALLEGRO_ALIGN_CENTRE, "HT Chen");
    al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2+200 , ALLEGRO_ALIGN_CENTRE, "Author: SYC, CHH");
    //al_draw_rectangle(this->width/2 - 180, this->height/2 + 100, this->width/2 + 180, this->height/2 + 136, al_map_rgb(255, 255, 255), 0);
    //al_draw_rectangle(this->width/2 - 180, this->height/2 + 150, this->width/2 + 180, this->height/2 + 186, al_map_rgb(255, 255, 255), 0);
    //al_draw_rectangle(this->width/2 - 180, this->height/2 + 200, this->width/2 + 180, this->height/2 + 236, al_map_rgb(255, 255, 255), 0);
    al_flip_display();
}
void Stage::page(int is_win, char *img_path, int is_last_page){
    al_clear_to_color(al_map_rgb(234,193,000));
    if(is_win && !is_last_page){
        al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2 - 200, ALLEGRO_ALIGN_CENTRE, "You WIN");

        ALLEGRO_BITMAP *magicImg = al_load_bitmap(img_path);
        al_draw_bitmap(magicImg, this->width/2  - 160, this->height/2 - 100, 0);

        // Upgrade HP Image
        ALLEGRO_BITMAP *hpImg = al_load_bitmap("./img/hp.png");
        al_draw_bitmap(hpImg, this->width/2 - 190, this->height/2 + 100, 0);
        al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2 - 110, this->height/2 + 250, ALLEGRO_ALIGN_CENTRE, "HP + 20 (Z)");

        // Upgrade ATK Image
        ALLEGRO_BITMAP *atkImg = al_load_bitmap("./img/atk.png");
        al_draw_bitmap(atkImg, this->width/2 + 40, this->height/2 + 100, 0);
        al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2 + 110, this->height/2 + 250, ALLEGRO_ALIGN_CENTRE, "ATK + 20 (X)");

        this->is_able_upgrade = 1;
    }else if(is_win && is_last_page){
        al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2 - 200, ALLEGRO_ALIGN_CENTRE, "You WIN");
    }else{
        al_draw_text(this->font, al_map_rgb(255,255,255), this->width/2, this->height/2 - 100, ALLEGRO_ALIGN_CENTRE, "You LOSE");
        this->is_able_upgrade = 0;
    }
    al_flip_display();
}
int Stage::is_current_level_over(){
    if(this->hero == NULL|| this->client == NULL){return 1;}
    return !(this->hero->_is_alive() && this->client->_is_alive());
}
int Stage::is_win(){
    if(this->hero == NULL|| this->client == NULL){return 1;}
    return !this->client->_is_alive();
}
void Stage::run(){
    while(!this->is_terminate){
        if(this->is_continue_update){
            if(this->is_in_about_page){
                // About Page
                this->is_continue_update = 0;
                this->is_able_next_page = 0;
                this->is_stage_setup = 0;
                this->about_page();
            }else if(this->window == 0){
                // Main Page
                this->is_continue_update = 0;
                this->is_able_next_page = 1;
                this->is_stage_setup = 0;

                // Setup parameter
                this->clear_upgrade();
                //this->delete_roles();

                this->main_page();
                //this->set_up_stage1();


            }else if(this->window == 1){
                //Level 1 Setup
                if(!this->is_stage_setup){
                    this->delete_roles();
                    this->set_up_stage1();
                    this->is_stage_setup = 1;
                }
                // Level 1 Gaming
                this->hero->start_timer();
                this->client->start_timer();
                this->is_continue_update = 1;
                this->is_able_next_page = 0;

                if(!this->is_current_level_over()){
                    this->show_stage1();
                }else{
                    printf("Auto Page1\n");
                    this->set_window(this->window+1, 1);
                }
            }else if(this->window == 2){
                // Level 1 Finished
                this->is_continue_update = 0;
                this->is_able_next_page = 1;
                this->is_stage_setup = 0;

                this->page(this->is_win(), "./img/goodsong.png", 0);

                // ============================================
            }else if(this->window == 3){
                //Level 2 Setup
                if(!this->is_stage_setup){
                    this->delete_roles();
                    this->set_up_stage2();
                    this->is_stage_setup = 1;
                }
                // Level 2 Gaming
                this->hero->start_timer();
                this->client->start_timer();
                this->is_continue_update = 1;
                this->is_able_next_page = 0;

                if(!this->is_current_level_over()){
                    this->show_stage1();
                }else{
                    //this->delete_current_stage();
                    printf("Auto Page2\n");
                    this->set_window(this->window+1, 1);
                }
            }else if(this->window == 4){
                // Level 2 Finished
                //this->delete_current_stage();
                this->is_continue_update = 0;
                this->is_able_next_page = 1;
                this->is_stage_setup = 0;

                this->page(this->is_win(), "./img/goodsong.png", 0);

                // ============================================
            }else if(this->window == 5){
                //Level 3 Setup
                if(!this->is_stage_setup){
                    this->delete_roles();
                    this->set_up_stage3();
                    this->is_stage_setup = 1;
                }
                // Level 3 Gaming
                this->hero->start_timer();
                this->client->start_timer();
                this->is_continue_update = 1;
                this->is_able_next_page = 0;

                if(!this->is_current_level_over()){
                    this->show_stage1();
                }else{
                    //this->delete_current_stage();
                    printf("Auto Page3\n");
                    this->set_window(this->window+1, 1);
                }
            }else if(this->window == 6){
                // Level 3 Finished
                //this->delete_current_stage();
                this->is_continue_update = 0;
                this->is_able_next_page = 1;
                this->is_stage_setup = 0;

                this->page(this->is_win(), "./img/goodsong.png", 0);
                this->set_up_stage1();

                // ============================================
            }else if(this->window == 7){
                //Level 4 Setup
                if(!this->is_stage_setup){
                    this->delete_roles();
                    this->set_up_stage4();
                    this->is_stage_setup = 1;
                }
                // Level 4 Gaming
                this->hero->start_timer();
                this->client->start_timer();
                this->is_continue_update = 1;
                this->is_able_next_page = 0;

                if(!this->is_current_level_over()){
                    this->show_stage1();
                }else{
                    //this->delete_current_stage();
                    printf("Auto Page3\n");
                    this->set_window(this->window+1, 1);
                }
            }else if(this->window == 8){
                // Level 4 Finished
                //this->delete_current_stage();
                this->is_continue_update = 0;
                this->is_able_next_page = 1;
                this->is_stage_setup = 0;

                this->page(this->is_win(), "./img/goodsong.png", 0);
                this->set_up_stage1();

                // ============================================
            }else if(this->window == 9){
                //Level 5 Setup
                if(!this->is_stage_setup){
                    this->delete_roles();
                    this->set_up_stage5();
                    this->is_stage_setup = 1;
                }
                // Level 5 Gaming
                this->hero->start_timer();
                this->client->start_timer();
                this->is_continue_update = 1;
                this->is_able_next_page = 0;

                if(!this->is_current_level_over()){
                    this->show_stage1();
                }else{
                    //this->delete_current_stage();
                    printf("Auto Page3\n");
                    this->set_window(this->window+1, 1);
                }
            }else if(this->window == 10){
                // Level 5 Finished
                //this->delete_current_stage();
                this->is_continue_update = 0;
                this->is_able_next_page = 1;
                this->is_stage_setup = 0;

                this->page(this->is_win(), "./img/goodsong.png", 1);
                this->set_up_stage1();

                // ============================================
            }
            else{
                this->is_continue_update = 1;
                this->is_able_next_page = 1;
                this->window = 0;
            }
        }

        if (!al_is_event_queue_empty(this->event_queue)) {
            //error = process_event();
            ALLEGRO_EVENT event;
            al_wait_for_event(this->event_queue, &event);
            updater(event);
        }

    }

    this->destroy();
}

int Stage::set_window(int window_code, int is_conti_update){
    printf("%d %d\n", window_code, is_conti_update);
    this->window = window_code;
    this->is_continue_update = is_conti_update;
}
int Stage::updater(ALLEGRO_EVENT event){
    //printf("Is_terminate: %d\n", this->is_terminate);
    if(this->client != NULL){
        this->client->update_walk_event(event);
        this->client->update_atks_event(event, this->hero);
    }

    if(this->hero != NULL){
        this->hero->update_keyboard_event(event);
        this->hero->update_atks_event(event, this->client);
    }

    if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){
            // For Start Menu
            case ALLEGRO_KEY_ENTER:
                if(this->is_able_next_page){
                    this->set_window(this->window+1, 1);
                }
                break;
            case ALLEGRO_KEY_Q:
                this->is_continue_update = 1;
                if(!this->is_in_about_page){
                    this->is_in_about_page = 1;
                }else{
                    this->is_in_about_page = 0;
                }
            case ALLEGRO_KEY_Z:
                this->upgrade_hp(20);
                break;
            case ALLEGRO_KEY_X:
                this->upgrade_atk(20);
                break;
            case ALLEGRO_KEY_ESCAPE:
                int res = this->set_game_over();
                return res;
                break;

        }
    }

    // Shutdown our program
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        int res = this->set_game_over();
        return res;
    }

    return 0;

}
int Stage::set_game_over(){
    this->is_terminate = 1;
    return 1;
}
void Stage::delete_current_stage(){
    delete(this->hero);
    delete(this->client);
    //delete(this->background);
}
void Stage::delete_roles(){
    if(this->hero != NULL){
        delete(this->hero);
    }
    if(this->client != NULL){
        delete(this->client);
    }
    //delete(this->background);
}
void Stage::upgrade_hp(int add_hp){
    if(this->is_able_upgrade){
        al_draw_rectangle(this->width/2 - 185, this->height/2 + 100, this->width/2 - 35, this->height/2 + 250, al_map_rgb(255, 255, 255), 0);
        al_flip_display();
        this->hero_add_hp += add_hp;
        this->is_able_upgrade = 0;
    }
}
void Stage::upgrade_atk(int add_atk){
    if(this->is_able_upgrade){
        al_draw_rectangle(this->width/2 + 35, this->height/2 + 100, this->width/2 + 185, this->height/2 + 250, al_map_rgb(255, 255, 255), 0);
        al_flip_display();
        this->hero_add_atk += add_atk;
        this->is_able_upgrade = 0;
    }
}
void Stage::clear_upgrade(){
    this->hero_add_atk = 0;
    this->hero_add_hp = 0;
}
void Stage::set_up_stage1(){
    //this->delete_roles();
    this->hero = new Role(100, 5, 3, 0, 0, -1, this->width/2, this->height/2+100, 30, 0, 0.1, this->width, this->height, this->event_queue, "./img/hero.png", "./img/pee.png", "./img/poop.png");
    this->client = new Role(10, 5, 5, 1, 0, 1, this->width/2, this->height/5, 10, 1, 1, this->width, this->height, this->event_queue, "./img/monster1.png", "./img/monster_attack1.png", "./img/monster_attack1.png");
    this->background = al_load_bitmap("./img/background1.jpg");
}
void Stage::set_up_stage2(){
    //this->delete_roles();
    this->hero = new Role(20 + this->hero_add_hp, 10 + this->hero_add_atk, 3 + this->hero_add_atk, 0, 0, -1, this->width/2, this->height/2+100, 30, 0, 0.1, this->width, this->height, this->event_queue, "./img/hero.png", "./img/pee.png", "./img/poop.png");
    this->client = new Role(20, 5, 5, 1, 0, 1, this->width/2, this->height/5, 20, 1, 0.5, this->width, this->height, this->event_queue, "./img/monster2.png", "./img/monster_attack2.png", "./img/monster_attack2.png");
    this->background = al_load_bitmap("./img/background2.jpg");

}
void Stage::set_up_stage3(){
    //this->delete_roles();
    this->hero = new Role(20 + this->hero_add_hp, 10 + this->hero_add_atk, 3 + this->hero_add_atk, 0, 0, -1, this->width/2, this->height/2+100, 30, 0, 0.1, this->width, this->height, this->event_queue, "./img/hero.png", "./img/pee.png", "./img/poop.png");
    this->client = new Role(40, 5, 5, 1, 0, 1, this->width/2, this->height/5, 10, 2, 0.3, this->width, this->height, this->event_queue, "./img/monster3.png", "./img/monster_attack3.png", "./img/monster_attack3.png");
    this->background = al_load_bitmap("./img/background3.jpg");
}
void Stage::set_up_stage4(){
    //this->delete_roles();
    this->hero = new Role(20 + this->hero_add_hp, 10 + this->hero_add_atk, 3 + this->hero_add_atk, 0, 0, -1, this->width/2, this->height/2+100, 30, 0, 0.1, this->width, this->height, this->event_queue, "./img/hero.png", "./img/pee.png", "./img/poop.png");
    this->client = new Role(80, 5, 5, 1, 0, 1, this->width/2, this->height/5, 10, 2, 0.2, this->width, this->height, this->event_queue, "./img/monster4.png", "./img/monster_attack4.png", "./img/monster_attack4.png");
    this->background = al_load_bitmap("./img/background4.jpg");
}
void Stage::set_up_stage5(){
    //this->delete_roles();
    this->hero = new Role(20 + this->hero_add_hp, 10 + this->hero_add_atk, 3 + this->hero_add_atk, 0, 0, -1, this->width/2, this->height/2+100, 30, 0, 0.1, this->width, this->height, this->event_queue, "./img/hero.png", "./img/pee.png", "./img/poop.png");
    this->client = new Role(160, 5, 5, 1, 0, 1, this->width/2, this->height/5, 10, 2, 0.1, this->width, this->height, this->event_queue, "./img/monster5.png", "./img/monster_attack5.png", "./img/monster_attack5.png");
    this->background = al_load_bitmap("./img/background5.jpg");

}
void Stage::show_stage1(){
    al_draw_bitmap(this->background, 0,0, 0);
    this->hero->show();
    this->client->show();

    this->is_able_upgrade = 0;
    // Show HP
    std::string hero_hp = std::to_string(this->hero->_hp());
    std::string client_hp = std::to_string(this->client->_hp());
    hero_hp = "HP: " + hero_hp;
    client_hp = "HP: " + client_hp;
    printf("HP: %d ATK: %d %d\n", this->hero->_hp(), this->hero->_atk1(), this->hero->_atk2());
    al_draw_text(this->font, al_map_rgb(255, 255, 255), this->width/2 + 140, this->height/2+250 , ALLEGRO_ALIGN_CENTER, hero_hp.c_str());
    al_draw_text(this->font, al_map_rgb(255, 255, 255), this->width/2 - 130, this->height/2+250 , ALLEGRO_ALIGN_CENTER, client_hp.c_str());

    al_flip_display();
}
void Stage::show_stage2(){
    al_draw_bitmap(this->background, 0,0, 0);
    this->hero->show();
    this->client->show();

    al_flip_display();
    //al_clear_to_color(al_map_rgb(0,0,0));
}
void Stage::show_stage3(){
    al_draw_bitmap(this->background, 0,0, 0);
    this->hero->show();
    this->client->show();

    al_flip_display();
    //al_clear_to_color(al_map_rgb(0,0,0));
}

int Stage::_stage(){return this->stage;};
int Stage::_window(){return this->window;};
Role *Stage::_hero(){return this->hero;};
Role *Stage::_client(){return this->client;};
ALLEGRO_EVENT_QUEUE *Stage::_event_queue(){return this->event_queue;}
ALLEGRO_DISPLAY *Stage::_display(){return this->display;}
ALLEGRO_SAMPLE *Stage::_song(){return this->song;};
ALLEGRO_FONT *Stage::_font(){return this->font;};
ALLEGRO_BITMAP *Stage::_background(){return this->background;};
