void initialize();
void init_ports();
void init_ADC();
void init_timer();

void right_move(char speed_l,char speed_r);
void left_move(char speed_l,char speed_r);
void drop_move();
void bun_picking();

char path;
char red_arena;
char blue_arena;
char final_fall;
char break_check;

