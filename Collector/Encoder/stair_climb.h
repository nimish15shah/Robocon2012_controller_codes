void stair_climb_down(char s);
void stair_climb(char s);

char back;
char front;

void initialize_intersection(void);
void initial_debounce(char t, char z);
void calculate_intersection(void);

char e_front_white;
char e_front_black;
char e_back_white;
char e_back_black;
	
volatile char front_black_intersection;
volatile char front_white_intersection;

volatile char back_black_intersection;
volatile char back_white_intersection;


