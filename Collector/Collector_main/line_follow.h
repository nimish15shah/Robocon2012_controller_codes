char enable_intersection;
char intersection;
int temp_intersection;
int debounce;
void init_line_follow(void);
void clear_intersection();

signed int single_diff;
void front_line_follow(char speed_1,char normal);
void double_line_follow(char speed);
void reverse_line_follow(char speed_1);
void reverse_double_line_follow(char speed);



signed int double_diff;
int single_delay_n;
int double_delay_n;
char pwm_i;
char pwm_j;
char momentum;
char momentum_reverse;
