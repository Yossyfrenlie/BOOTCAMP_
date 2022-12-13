#include<stdio.h>
#include<stdlib.h>

struct Node{
  int value;
  int priority;
  Node *next;
}*front, *front2, *rear, *rear2;

Node *createNode(int value){
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

Node *createNode2(int value, int priority){
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;
  newNode->priority = priority;
  newNode->next = NULL;
  return newNode;
}

void pushQueue(int value){
	Node *newNode = createNode(value);
	
	if(!front){
		front = rear = newNode;
	}
	else{
		rear->next = newNode;
		rear = rear->next;
	}
}

void removeQueue(){
	if(!front){
		return;
	}else{
		Node *newFront = front->next;
		front->next = NULL;
		free(front);
		front = newFront;
	}
}

void pushPriority(int value, int priority){
	Node *newNode = createNode2(value, priority);
	
	if(!front2){
		front2 = rear2 = newNode;
	}
	else if(newNode->priority > front2->priority){
		newNode->next = front2;
		front2 = newNode;
	}
	else if(newNode->priority < rear2->priority){
		rear2->next = newNode;
		rear2 = newNode;
	}
	else{
		struct Node *temp;
		temp = front2;
		
		while(temp->next != NULL && temp->next->priority > newNode->priority){
			temp = temp->next;
		}
		newNode->next = temp->next; 
		temp->next = newNode;
	}
}

void display(){	// print semua data queue
	struct Node *display;
	display = front;
	
	if(!front){
		printf("Queue is empty.\n");
	}else{
		printf("Queue\n");
		
		while(display!=NULL){
			printf("%d\n", display->value);
			display = display->next;
		}
	}
	printf("\n");
}

void display2(){	// print priority queue
	struct Node *display;
	display = front2;
	
	if(!front2){
		printf("Priority Queue is empty.\n");
	}else{
		printf("Priority Queue\n");
		
		while(display!=NULL){
			printf("Value : %d; Priority : %d\n", display->value, display->priority);
			display = display->next;
		}
	}
	printf("\n");
}


int main(){
	
	pushQueue(1);
	pushQueue(2);
	pushQueue(3);
	pushQueue(4);
	pushQueue(5);
	pushQueue(6);
	pushQueue(7);
	pushQueue(8);
	pushQueue(9);
	pushQueue(10);
	pushQueue(11);
	
	removeQueue();
	removeQueue();
	removeQueue();
	removeQueue();
	removeQueue();
	
	// print semua data queue
	display();
	
	printf("Front of the queue : %d\n", front->value);
	printf("\n");
	
	pushPriority(1, 5);
	pushPriority(1, 6);
	pushPriority(1, 8);
	pushPriority(1, 10);
	pushPriority(1, 7);
	pushPriority(1, 9);
	
	// print priority queue
	display2();
	
	printf("Priority : %d\n", front2->priority);

	return 0;
}
