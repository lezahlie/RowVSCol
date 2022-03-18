#include <stdio.h>
#include <stdlib.h>
#include "timer.h" // for getting current time

void traversal(int row, int col, double *row_t, double *col_t)  {

  // doubles for start and finish time
  double start, finish; 

  // pointer to matrix using malloc to allocate new mem block for passed row*col size
  int *matrix = (int*)malloc(row*col*sizeof(int));

  GET_TIME(start);   // get start time for row major

  for (int a = 0; a < row; a++)   // loops each row first
    for (int b = 0; b < col; b++)   // traverses each col index in current row
        *(matrix + a*col + b) = a*b;  // stores arbitrary sum to each [row][col] coordinate 

  GET_TIME(finish);  // get finish time for row major
  *row_t = (finish - start);  // stores elapsed time for row major 

  free(matrix);  // frees matrix pointer from memory 
  // reallocates new mem block with same row*col sizes for column major
  matrix = (int*)malloc(row*col*sizeof(int)); 

  GET_TIME(start); // get start time for column major 

  for (int b = 0; b < col; b++)   // loops each col first
    for (int a = 0; a < row; a++)   // traverses each row index in current col
        *(matrix + a*col + b) = a*b;  // stores arbitrary sum to each [row][col] coordinate 

  GET_TIME(finish);  // get finish time for column major 
  *col_t = (finish - start);  // stores elapsed time for row major 

  free(matrix);  // frees matrix pointer from memory 
}

int main(int argc, char** argv) {

  int exitCode = EXIT_FAILURE;
  // checks if 4 arguments have are not entered
  if (argc == 4) {  

    char *pMin,*pMax, *pStep; // pointers for max, max, and step args

    int min = strtol((char*)argv[1], &pMin, 10);  // converts each char in <min> to base 10 int 
    int max = strtol((char*)argv[2], &pMax, 10);  // converts each char in <max> to base 10 int 
    int step = strtol((char*)argv[3], &pStep, 10);  // converts each char in <step> to base 10 int 

    // checks if any pointer for args parsed above do not reach end in mem, meaning an arg was not valid base 10 int
    if(*pMin != '\0' || *pMax != '\0' || *pStep != '\0') {
      // print error stmt and exit with failure 
      printf("error: args for <min> <max> <step> must be valid integers\n"); 
    }// checks if min 0 or negative, max is less than min, step is more than max, or step 0 or negative
    else if(min < 1 || min > max || max < step || step < 1) {
      // print error stmt and exit with failure 
      printf("error: args for <min> <max> <step> contain invalid bounds for increasing array size\n"); 
    } // args are valid, call traversal function
    else {

        double row_time, col_time; // elapsed time doubles to be retrieved
        // loops from min to max, increasing by step value
        for(int m = min; m <= max; m+=step ) {     
          // calls traversal method with parameters: m for row and col size, mem addr for row and col time
          traversal(m, m, &row_time, &col_time);
          // prints each new sizes results for row and column majors elapsed time
          printf("m (#rows and cols) = %d, elapsed time (row major) = %f seconds, elapsed time (col major) = %f seconds\n", m, row_time, col_time);
        }
        exitCode = EXIT_SUCCESS;
    }
   
  } // print usage stmt and exit with failure
  else printf("usage: %s <min> <max> <step>\n", argv[0]); 

  exit(exitCode);   // exit program with success!
}