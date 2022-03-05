#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "allegro_var.h"
#include "game_body.h"
#include "stage.h"
#include "main_page.h"

#define GAME_TERMINATE -1

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_FONT *font = NULL;

//Custom Definition
const char *title = "Final Project 10xxxxxxx";
const float FPS = 60;
const int WIDTH = 400;
const int HEIGHT = 600;

Role *hero = NULL;
Role *client= NULL;
Stage *game = NULL;

int imageWidth = 0;
int imageHeight = 0;
int draw = 0;
int done = 0;
int window = 1;
bool judge_next_window = false;
bool ture = true; //true: appear, false: disappear
bool next = false; //true: trigger
bool dir = true; //true: left, false: right

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();

int main(int argc, char *argv[]) {
    int msg = 0;
    game = new Stage(WIDTH, HEIGHT);
    game->init();

    //game->main_page();
    game->run();
    delete(game);
    return 0;
}
