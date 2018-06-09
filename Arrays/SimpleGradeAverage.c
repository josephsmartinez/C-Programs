#include <stdio.h>
#include <stdlib.h>
/**
* Simple programing that calculates the average of 10 numbers entered by a user.
*/
int main(int argc, char** argv) {

  int grades[10];
  int count = 10;
  long sum = 0;
  float average = 0.0f;

  printf("Enter the 10 grades:\n");

  //Read the ten numbers to be averaged
  int i;
  for(i=0; i < count; ++i){
    printf("%d> ", i + 1 );
    scanf("%d", &grades[i]);
    sum += grades[i];
  }

  average = (float) sum/count;

  printf("Average of the ten grades entered is: %f.2\n", average);

  return EXIT_SUCCESS;
}
