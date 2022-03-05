#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "game_body.h"

Attack::Attack(int atk, int speed, int is_auto_fire, int atk_dir_x, int atk_dir_y, double fps, int width, int height, char *atk_img_path, ALLEGRO_EVENT_QUEUE *event_queue){
    this->atk = atk;
    this->speed = speed;
    this->atk_dir_x = atk_dir_x;
    this->atk_dir_y = atk_dir_y;
    this->fps = fps;
    this->width = width;
    this->height = height;
    this->atk_img_path = atk_img_path;

    this->event_timer = al_create_timer(fps);
    this->atk_bitmap = al_load_bitmap(atk_img_path);

    al_register_event_source(event_queue, al_get_timer_event_source(this->event_timer));
    al_start_timer(this->event_timer);
}
Attack::~Attack(){
    delete(this->event_timer);
    delete(this->atk_bitmap);
    delete(this->atk_img_path);
    this->pos_xs.clear();
    this->pos_ys.clear();
}
void Attack::move(){
    for(int i = 0; i < this->pos_ys.size(); i++){
        //if(x_dir == 1){
            this->pos_xs.at(i) += this->atk_dir_x * this->speed;
        //}else if(x_dir == -1){
          //  this->pos_xs.at(i) -= this->atk_dir_y * this->speed;
        //}
        //if(y_dir == 1){
            this->pos_ys.at(i) += this->atk_dir_y * this->speed;
        //}else if(y_dir == -1){
          //  this->pos_ys.at(i) -= this->speed;
        //}

        if(this->pos_ys.at(i) > this->height || this->pos_xs.at(i) > this->width || this->pos_ys.at(i) < 0 || this->pos_xs.at(i) < 0){
            this->pos_xs.erase(this->pos_xs.begin() + i);
            this->pos_ys.erase(this->pos_ys.begin() + i);
        }
    }
}

void Attack::add(int pos_x, int pos_y){
    this->pos_xs.push_back(pos_x);
    this->pos_ys.push_back(pos_y);
}

int Attack::hit(int pos_x, int pos_y, int r){
    int accum_atk = 0;
    for(int i = 0; i < this->pos_ys.size(); i++){
        int  dis = (this->pos_xs.at(i) - pos_x) * (this->pos_xs.at(i) - pos_x) + (this->pos_ys.at(i) - pos_y) * (this->pos_ys.at(i) - pos_y);
        if(dis <= r * r){
            printf("ATK: %d in %d\n", this->atk, this->pos_ys.size());
            accum_atk += this->atk;
            this->disappear(i);
        }
    }
    return accum_atk;
}
bool Attack::update_timer_event(ALLEGRO_EVENT event){
    if(event.timer.source == this->event_timer){
        this->move();
        //if(this->is_auto_fire){this->add();}
        return 1;
    }
    return 0;
}
void Attack::show(){
    for(int i = 0; i < this->pos_xs.size(); i++){
        //if()
        al_draw_bitmap(this->atk_bitmap, this->pos_xs.at(i), this->pos_ys.at(i), 0);
    }
}
void Attack::disappear(int idx){
    this->pos_xs.erase(this->pos_xs.begin() + idx);
    this->pos_ys.erase(this->pos_ys.begin() + idx);
}


Role::Role(int hp, int atk1, int atk2, int is_auto_fire, int atk_dir_x, int atk_dir_y, int pos_x, int pos_y, int move_unit, int move_type, double fps, int width, int height, ALLEGRO_EVENT_QUEUE *event_queue, char *role_img_path, char *atk1_img_path, char *atk2_img_path){
    this->hp = hp;
    this->is_alive = 1;
    this->atk1 = atk1;
    this->atk2 = atk2;
    this->is_auto_fire = is_auto_fire;
    this->atk_dir_x = atk_dir_x;
    this->atk_dir_y = atk_dir_y;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->move_unit = move_unit;
    this->move_type = move_type; // Move Type = 1: horizontal_walk, = 2: random_walk
    this->move_dir = 1;// move_unit = 1: move right, = -1 move left
    this->fps = fps;
    this->width = width;
    this->height = height;
    this->event_queue = event_queue;
    this->event_timer = al_create_timer(fps);
    this->role_img_path = role_img_path;
    this->atk1_img_path = atk1_img_path;
    this->atk2_img_path = atk2_img_path;
    this->atks1 = new Attack(atk1, move_unit, is_auto_fire, atk_dir_x, atk_dir_y, fps, width, height, this->atk1_img_path, event_queue);
    this->atks2 = new Attack(atk2, move_unit, is_auto_fire, atk_dir_x, atk_dir_y, fps, width, height, this->atk2_img_path, event_queue);
    this->role_bitmap = al_load_bitmap(role_img_path);

    al_register_event_source(event_queue, al_get_timer_event_source(this->event_timer));
    //al_start_timer(this->event_timer);
}
Role::~Role(){
    delete(this->role_img_path);
    delete(this->atk1_img_path);
    delete(this->atk2_img_path);
    delete(this->atks1);
    delete(this->atks2);
    delete(this->event_queue);
    delete(this->event_timer);
    delete(this->role_bitmap);
}
void Role::go_up(){
    if(this->is_alive){this->pos_y -= this->move_unit;}
}
void Role::go_down(){
    if(this->is_alive){this->pos_y += this->move_unit;}
}
void Role::go_left(){
    if(this->is_alive){this->pos_x -= this->move_unit;}
}
void Role::go_right(){
    if(this->is_alive){this->pos_x += this->move_unit;}
}
void Role::random_walk(){
    if(this->is_alive){
        this->pos_x = rand() %this->width;
        this->pos_y = rand() % this->height;
    }
}
void Role::horizontal_walk(){
    if(this->is_alive){
        if(this->pos_x >= this->width || this->pos_x <= 0){
            this->move_unit = -this->move_unit;
        }
        this->pos_x = this->pos_x + this->move_unit;
    }
}
void Role::fire1(){
    if(this->is_alive){this->atks1->add(this->pos_x, this->pos_y);}
}
void Role::fire2(){
    if(this->is_alive){this->atks2->add(this->pos_x, this->pos_y);}
}
void Role::lose_hp(int lose){
    if(this->is_alive){this->hp -= lose;}
    if(this->hp <= 0){this->die();}
}
void Role::start_timer(){
    al_start_timer(this->event_timer);
}
bool Role::update_keyboard_event(ALLEGRO_EVENT event){
    if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_UP:
                this->go_up();
                break;
            case ALLEGRO_KEY_DOWN:
                this->go_down();
                break;
            case ALLEGRO_KEY_LEFT:
                this->go_left();
                break;
            case ALLEGRO_KEY_RIGHT:
                this->go_right();
                break;
            case ALLEGRO_KEY_A:
                this->fire1();
                break;
            case ALLEGRO_KEY_S:
                this->fire2();
               break;
        }
    }
}
bool Role::update_atks_event(ALLEGRO_EVENT event, Role *enemy){
    if(event.timer.source == this->event_timer && this->is_auto_fire){
        this->fire1();
    }
    int res1 = this->atks1->update_timer_event(event);
    int res2 = this->atks2->update_timer_event(event);
    enemy->lose_hp(this->atks1->hit(enemy->pos_x, enemy->pos_y, 50));
    enemy->lose_hp(this->atks2->hit(enemy->pos_x, enemy->pos_y, 50));
    return res1 + res2;
}
bool Role::update_random_walk_event(ALLEGRO_EVENT event){
    if(event.timer.source == this->event_timer){
        this->random_walk();
        return 1;
    }
    return 0;
}
bool Role::update_horizontal_walk_event(ALLEGRO_EVENT event){
    if(event.timer.source == this->event_timer){
        this->horizontal_walk();
        return 1;
    }
    return 0;
}
bool Role::update_walk_event(ALLEGRO_EVENT event){
    if(this->move_type == 1){
        return this->update_horizontal_walk_event(event);
    }else if(this->move_type == 2){
        return this->update_random_walk_event(event);
    }
}
void Role::show(){
    if(this->is_alive){
        al_draw_bitmap(this->role_bitmap, this->pos_x, this->pos_y, 0);
    }
    this->atks1->show();
    this->atks2->show();
}
void Role::die(){
    this->pos_x = -100;
    this->pos_y = -100;
    this->is_alive = 0;
}
int Role::_hp(){return this->hp;}
int Role::_is_alive(){return this->is_alive;}
int Role::_atk1(){return this->atk1;}
int Role::_atk2(){return this->atk2;}
int Role::_pos_x(){return this->pos_x;}
int Role::_pos_y(){return this->pos_y;}
int Role::_move_unit(){return this->move_unit;}
double Role::_fps(){return this->fps;}
char *Role::_role_img_path(){return this->role_img_path;}
ALLEGRO_EVENT_QUEUE *Role::_event_queue(){return this->event_queue;}
ALLEGRO_TIMER *Role::_event_timer(){return this->event_timer;}
ALLEGRO_BITMAP *Role::_role_bitmap(){return this->role_bitmap;}
