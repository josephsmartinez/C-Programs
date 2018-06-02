<h1>Introduction to C & Functions in C</h1>
<h4>1 Remainder of Dividing by Three</h4>
<p>The easiest way to nd the remainder of a given integer like 235 when dividing by three is to
calculate the remainder of 2+3+5 instead. Use this idea to implement a recursive function
that calculates the remainder of any given non-negative integer when dividing by three.
Your function must obey the following signature:<br>
int nMOD3 (int n[ ], int size)<br>
where array n species the input integer by storing each digit in one cell and size determines
how many digits the input integer has. For example, nMOD3 (f2, 3, 5g, 3) is a valid function
call. The remainder of n when dividing by three has to be returned by the nMOD3 function
as its output.<br></p>

<h4>2 Constructing a Queue</h4>
<p>Queue is a data collection in which the entities in the collection are kept in order and the
operations on the collection are the addition of entities to the rear terminal position, known
as enqueue, and removal of entities from the front terminal position, known as dequeue. This
makes the queue a First-In-First-Out (FIFO) data structure. As we mentioned in the class,
stack is a similar data collection that adds/removes entities in a First-In-Last-Out (FILO)
manner.<br>
  
In this assignment, you need to construct a queue of integers by implementing its enqueue
and dequeue operations using two stacks in the following way (implementation of a stack
and its push & pop operations in C can be found in the textbook and in slides).<br>

<strong> void enqueue(int entity):</strong> The enqueue operation can be done by simply pushing the
entity in the frist stack.<br>

<strong> int dequeue():</strong> In order to implement dequeue operation, you need to rst transfer all
of the entities stored in the rst stack to the second one using a sequence of alternating
pop and push operations on the rst and second stacks respectively (i.e. popping an
integer from the rst stack and pushing it back to the second one). After emptying the
first stack, you simply pop from the second stack to complete the dequeue operation.
