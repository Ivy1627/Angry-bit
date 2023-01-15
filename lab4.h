/* Jingxin Zhang */

void change_world(Sim *p2sim);
void check_argc(int num, Sim *p2sim);
void clear_everything(Sim *p2sim);
void close_file(Sim *p2sim);
int init();
int main(int argc, char *argv[]);
int open_file(int argc, char *argv[], Sim *p2sim);
void run_bonus(Sim *p2sim);
void run_compatible(Sim *p2sim);
void run_sim(Sim *p2sim);
int stop_sim(Sim *p2sim);
void teardown();
