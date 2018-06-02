/** *******************************************************************
 * Purpose/Description: Simulate a Queue Data Structure using two Stacks
 * Author’s Panther ID: 3816842
 * Certification:
 * I hereby certify that this work is my own and none of it is the work of
 * any other person.
 ******************************************************************* */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constants
#define MAX_SIZE 10

//Globally defined struct
typedef struct Stack_Class{
	int stack[MAX_SIZE];
	int top;
}Stack;

//Stack Functions
void push(Stack *s, int x);
int pop(Stack *s);

//Queue Functions
void enqueue(Stack *s1, int x);
int deeueue(Stack *s1, Stack *s2);
void traverse(Stack *s1, Stack *s2);

//Test main method
main(void){
  
  int element, choice;  
  Stack stack1;
  Stack stack2;
  stack1.top = 0;
  stack2.top = 0;  
    
    
    //Main menu excepts user input one element at a time
    while(1){
    printf("Queue Operations.\n");
    printf("1. Insert into Queue (Inqueue operation)\n");
    printf("2. Remove from Queue (Dequeue operation)\n");
    printf("3. Print element in Queue.\n");
    printf("4. Exit.\n");
    scanf("%d", &choice);

        switch(choice)
        {
          case 1:
          //Insert element into the Queue
          printf("Enter value to insert.\n");
          scanf("%d", &element);
          enqueue(&stack1, element); 
          break;
          
          case 2:
          //Removes the first item in the Queue   
          printf("Dequeue the following element:%d\n\n", dequeue(&stack1, &stack2));
          break;    

          case 3:
          //List all the elements in the Queue
          printf("Current elements in the Queue.\n");
          traverse(&stack1, &stack2);
          break;    
         
          case 4:
          //End Program
          return EXIT_SUCCESS;
          break;    

        }  
   }
}

//---------FUNCTION DEFINTIONS-------------

/**
 *  This function is used for the Queue functions.
 *  @param *s   is a pointer to a Stack object
 *  @param x    is an integer element 
 */
void push(Stack *s, int x){
 s->stack[s->top] = x;
 s->top++;
}

/**
 *  This function is used for the Queue functions.
 *  @param *s   is a pointer to a Stack object
 *  @return     an element removed from popping
 */
int pop(Stack *s){
  s->top--;
  return s->stack[s->top];
}

void enqueue(Stack *s1, int x){
  push(s1, x);

}

/**
 *  Function uses two Stack objects to simulate a Queue Data Structure
 *  @param *s1   is a pointer to a Stack object
 *  @param *s2   is a pointer to a Stack object
 *  @return      the first element in the Queue
 */
int dequeue(Stack *s1, Stack *s2){
  
  int i;
  for(i = s1->top - 1; i >= 0; i--){
    push(s2, pop(s1));
  }
  
  int firstDequeue = pop(s2);
  
  int y;
  int x = s2->top;
  for(i = 0; i < x; i++){
    y = pop(s2);
    push(s1, y);
  }

  return firstDequeue;

}

/**
 *  Function print all the elements in the Queue
 *  @param *s1   is a pointer to a Stack object
 *  @param *s2   is a pointer to a Stack object
 */
void traverse(Stack *s1, Stack *s2){
  
  int i;
  for(i = s1->top - 1; i >= 0; i--){
    push(s2, pop(s1));
  }
  
  int y;
  int x = s2->top;
  for(i = 0; i < x; i++){
    y = pop(s2);
    printf("%d ", y);
    push(s1, y);
  }
  printf("\n\n");

}