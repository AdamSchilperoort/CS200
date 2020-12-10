#ifndef _runner_h
#define _runner_h

//performs any necessary setup for the runner_solve() function
void runner_init(void);

//uses maze library functions provided to solve a maze
void runner_solve(void);

int get_tile_val(char c);
int find_next_valid_tile(int x, int y);

#endif
