#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* DEFINEs*/
/* -------------------------------------------------------- */

/* N*N maze. N is the number of rows or number of columns. */
#define N 20

/* Assuming each number has length of am most 10 characters. */
#define MAX_NUMBER_LENGTH 10

/* Maximum size of a two tuple with brackets ("(123,124)").
  +3 for the brackets and comma. */
#define MAX_TWO_TUPLE_WITH_BRACKETS_LENGTH (MAX_NUMBER_LENGTH*2+3)

/* FUNCTIONS */
/* -------------------------------------------------------- */


/*
   find_path_length - Finds the length of a solution path in the maze.
   Inputs: valid_tiles - a 2-dimensional array that contains
                    1 if the tile is a valid tile or 0 otherwise.
                    Note that the source and destination tiles
                    are defined as valid tiles.
           source_row, source, col - row and column position (0 based)
                    of the source tile.
           dest_row, dest, col - row and column position (0 based)
                    of the destination tile.
    Returns - Length of a solution path, or 0 if there is no solution
              path.
*/
unsigned int find_path_length(int valid_tiles[N][N],
                              unsigned int source_row,
                              unsigned int source_col,
                              unsigned int dest_row,
                              unsigned int dest_col)
{
    valid_tiles [source_row][source_col]=0;
    int path=0;
    if ((source_row==dest_row)&&(source_col==dest_col))
        return 1;
         if (((int)(source_col-1)>=0)&&(valid_tiles[source_row][source_col-1]==1))
                {
                    path=find_path_length( valid_tiles,source_row,source_col-1,dest_row,dest_col);
                    if(path!=0)
                        return path+1;
                }
         if ((source_col+1<=N-1)&&(valid_tiles[source_row][source_col+1]==1))
                {
                    path=find_path_length( valid_tiles,source_row,source_col+1,dest_row,dest_col);
                    if(path!=0)
                        return path+1;
                }
         if (((int)(source_row-1)>=0)&&(valid_tiles[source_row-1][source_col]==1))
                {
                    path=find_path_length( valid_tiles,source_row-1,source_col,dest_row,dest_col);
                    if(path!=0)
                        return path+1;
                }
         if ((source_row+1<=N)&&(valid_tiles[source_row+1][source_col]==1))
                {
                    path=find_path_length( valid_tiles,source_row+1,source_col,dest_row,dest_col);
                    if(path!=0)
                        return path+1;
                }
    return 0;
}




    /* TODO: Implement this function */

    /* TODO: Change the following line to return the solution path length. */




/*
   get_tiles_string - Gets tiles from standard input.
   This function prints a message to the standard output and gets the tiles
   string from standard input.
   This function does not validate the input string other than basic validation.
   Inputs: tiles - the tiles string.
   Returns true if and only if the function gets the input successfully.
*/
bool get_tiles_string(char* tiles) {
    printf("Please enter the maze tiles.\n");
    printf("Example: (0,1),(1,2),(5,6),(2,3),(7,1)\n");
    return (scanf("%s", tiles) == 1);
}


bool get_source(char* source) {
    printf("Please enter a source tile.\n");
    printf("Example: (5,6)\n");
    return (scanf("%s", source) == 1);
}


bool get_destination(char* source) {
    printf("Please enter a destination tile.\n");
    printf("Example: (8,3)\n");
    return (scanf("%s", source) == 1);
}

bool valid_tile(char* s)
{
    unsigned int a,b;
    if (sscanf(s, "(%u,%u)", &a, &b) != 2)
        return false;
    return (a<N) && (b<N);
}

/*
   validate_input - Validates program input.
   Returns true if and only if the input is valid.
*/
bool validate_input(char* tiles, char* source, char* destination) {
    if (!valid_tile(source)) {
        printf("Note: the source tile is invalid\n");
        return false;
    }
    if (!valid_tile(destination)) {
        printf("Note: the destination tile is invalid\n");
        return false;
    }
    while (*tiles != '\0')
    {
        if (!valid_tile(tiles)) {
            printf("Note: the maze tiles string contains an invalid tile.\n");
            return false;
        }
        while (*tiles != ')')
            ++tiles;
        ++tiles;
        if ((*tiles != ',') && (*tiles != '\0')) {
            printf("Note: the maze tiles string contains an invalid separator (non comma).\n");
            return false;
        }

        if (*tiles == ',')
            ++tiles;
    }
    return true;
}


void get_tile_position(char* tile,
                       unsigned int* row_ptr,
                       unsigned int* col_ptr) {
    sscanf(tile, "(%u,%u)", row_ptr, col_ptr);
}

/* Fill valid_tiles array with 1's in positions of tiles/source/destination.
   Assumes valid_tiles is initialized with zeros. */
void fill_valid_tiles_array(char* tiles,
                            char* source,
                            char* destination,
                            int valid_tiles[N][N]) {
    unsigned int row, column;
    get_tile_position(source, &row, &column);
    valid_tiles[row][column]=1;
    get_tile_position(destination, &row, &column);
    valid_tiles[row][column]=1;
    while (*tiles != '\0')
    {
        get_tile_position(tiles, &row, &column);
        valid_tiles[row][column]=1;
        while (*tiles != ')')
            ++tiles;
        ++tiles;
        if (*tiles == ',')
            ++tiles;
    }
}


/*
   main function.
   Inputs: none.
   Returns 0 when the program run successfully.
   Any other value indicates an error.
*/
int main() {
    unsigned int max_tiles_string_length;
    char* tiles = NULL;
    char source[MAX_TWO_TUPLE_WITH_BRACKETS_LENGTH+1] = { '\0' };
    char destination[MAX_TWO_TUPLE_WITH_BRACKETS_LENGTH+1] = { '\0' };
    unsigned int source_row;
    unsigned int source_col;
    unsigned int destination_row;
    unsigned int destination_col;
    unsigned int path_length;
    int valid_tiles[N][N] = {{0}}; /* Initialize the array with zeros. */

    /*
       Calculate the maximum length of the tiles string.
       (It is a function of n).
    */
    max_tiles_string_length = N*N*(MAX_TWO_TUPLE_WITH_BRACKETS_LENGTH+1)-1;

    /* Allocate memory of the tiles string.
       +1 for the terminating null character. */
    tiles = (char*)malloc(max_tiles_string_length+1);
    if (NULL == tiles) {
        printf("Memory allocation error\n");
        return 1;
    }

    if (!get_tiles_string(tiles))
        return 1;

    if (!get_source(source))
        return 1;

    if (!get_destination(destination))
        return 1;

    if (!validate_input(tiles, source, destination)) {
        printf("ERROR: invalid input\n");
        return 2;
    }

    fill_valid_tiles_array(tiles, source, destination, valid_tiles);

    get_tile_position(source, &source_row, &source_col);
    get_tile_position(destination, &destination_row, &destination_col);

    path_length=find_path_length(valid_tiles,
                                 source_row,
                                 source_col,
                                 destination_row,
                                 destination_col);

    /* Print the returned solution path length. */
    printf("%u\n", path_length);

    return 0;
}
