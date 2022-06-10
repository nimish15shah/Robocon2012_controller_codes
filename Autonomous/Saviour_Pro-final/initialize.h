void initialize(void);
void init_port(void);

void path_basket_1(void);
void path_basket_2(void);
void path_basket_check(void);
void path_collector(void);
void path_restart(void);

void forward_move();
void drop_move();
void right_move(char speed_l,char speed_r);
void left_move(char speed_l,char speed_r);
void drop_collector();
void restart_move();

char red_arena;
char blue_arena;
char path;

char division_factor;
