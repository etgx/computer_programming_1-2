
#ifndef GAME_BODY_H // include guard
#define GAME_BODY_H

#include <vector>

class Attack{
    public:
        Attack(int atk, int speed, int is_auto_fire, int atk_dir_x, int atk_dir_y, double fps, int width, int height, char *atk_img_path, ALLEGRO_EVENT_QUEUE *event_queue);
        ~Attack();
        void move();
        void add(int pos_x, int pos_y);
        int hit(int pos_x, int pos_y, int r);
        bool update_timer_event(ALLEGRO_EVENT even);
        void show();
        void disappear(int idx);
    protected:
        int atk;
        int n;
        int speed;
        int is_auto_fire;
        int atk_dir_x;
        int atk_dir_y;
        double fps;
        int width;
        int height;
        char *atk_img_path;
        std::vector<int> pos_xs;
        std::vector<int> pos_ys;
        ALLEGRO_TIMER *event_timer;
        ALLEGRO_BITMAP *atk_bitmap;
};

class Role{
    public:
        Role(int hp, int atk1, int atk2, int is_auto_fire, int atk_dir_x, int atk_dir_y, int pos_x, int pos_y, int move_unit, int move_type, double fps, int width, int height, ALLEGRO_EVENT_QUEUE *event_queue, char *role_img_path, char *atk1_img_path, char *atk2_img_path);
        ~Role();
        void go_up();
        void go_down();
        void go_left();
        void go_right();
        void random_walk();
        void horizontal_walk();
        void fire1();
        void fire2();
        void lose_hp(int lose);
        void start_timer();
        bool update_keyboard_event(ALLEGRO_EVENT event);
        bool update_atks_event(ALLEGRO_EVENT event, Role *enemy);
        bool update_random_walk_event(ALLEGRO_EVENT event);
        bool update_horizontal_walk_event(ALLEGRO_EVENT event);
        bool update_walk_event(ALLEGRO_EVENT event);
        void show();
        void die();

        int _hp();
        int _is_alive();
        int _atk1();
        int _atk2();
        int _pos_x();
        int _pos_y();
        int _move_unit();
        double _fps();
        char *_role_img_path();
        ALLEGRO_EVENT_QUEUE *_event_queue();
        ALLEGRO_TIMER *_event_timer();
        ALLEGRO_BITMAP *_role_bitmap();
    protected:
        int hp;
        int is_alive;
        int atk1;
        int atk2;
        int is_auto_fire;
        int atk_dir_x;
        int atk_dir_y;
        int pos_x;
        int pos_y;
        int move_unit;
        int move_type;
        int move_dir;
        double fps;
        int width;
        int height;
        char *role_img_path;
        char *atk1_img_path;
        char *atk2_img_path;
        Attack *atks1;
        Attack *atks2;
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_TIMER *event_timer;
        ALLEGRO_BITMAP *role_bitmap;
};
#endif
