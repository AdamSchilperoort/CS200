#include "mazelib.h"
#include "runner.h"

char tiles[] = {'E', ' ', '.', 'o', 'O', '@'};
int runner_coordinate[2];

void runner_init( void )
{
    runner_coordinate[0] = 1;
    runner_coordinate[1] = 1;
}

void runner_solve( void )
{
    while( maze_get_char( runner_coordinate[0], runner_coordinate[1] ) != 'E')
    {
       
        int new_direction = find_next_valid_tile( runner_coordinate[0], runner_coordinate[1] );
        switch ( new_direction )
        {
            case NORTH:
                runner_coordinate[1] = runner_coordinate[1] + 1;
                break;
            case EAST:
                runner_coordinate[0] = runner_coordinate[0] + 1;
                break;
            case SOUTH:
                runner_coordinate[1] = runner_coordinate[1] - 1;
                break;
            case WEST:
                runner_coordinate[0] = runner_coordinate[0] - 1;
                break;
        }
        char new_char;
        if ( get_tile_val( maze_get_char( runner_coordinate[0], runner_coordinate[1] ) ) + 1 > 5 )
        {
            new_char = '@';
        }
        else
        {
            new_char = tiles[ get_tile_val ( maze_get_char( runner_coordinate[0], runner_coordinate[1] ) ) + 1];
        }
        maze_set_char( runner_coordinate[0], runner_coordinate[1], new_char );
    }
}

int get_tile_val( char c )
{
    for( int i = 0; i < 6; i++ )
    {
        if( tiles[i] == c )
        {
            return i;
        }
    }
    return 999999;
}

int find_next_valid_tile( int x, int y )
{
    int lowest = 10;
    int direction = 0;
    for( int i = 0; i < 4; i++ )
    {
        int val;
        switch(i) {
            case NORTH:
                val = get_tile_val( maze_get_char( x, y + 1 ) );
                if( val < lowest )
                {
                    direction = i;
                    lowest = val;
                }
                break;
            case SOUTH:
                val = get_tile_val( maze_get_char( x, y - 1 ) );
                if( val < lowest )
                {
                    direction = i;
                    lowest = val;
                }
                break;
            case EAST:
                val = get_tile_val( maze_get_char( x + 1, y ) );
                if( val < lowest )
                {
                    direction = i;
                    lowest = val;
                }
                break;
            case WEST:
                val = get_tile_val( maze_get_char( x - 1, y ) );
                if( val < lowest )
                {
                    direction = i;
                    lowest = val;
                }
                break;
        }
    }
    
    return direction;
}
