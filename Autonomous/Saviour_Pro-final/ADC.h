void init_ADC(void);
volatile int ADC_channel;
volatile int ADC_threshold;
int	temp_result;
char final_temp_result;
volatile int ADC_result;
int ADC_value[8];
signed int last_ADC_result;
int final_ADC_result;
volatile char counter;
char implied_intersection;
char final_counter;