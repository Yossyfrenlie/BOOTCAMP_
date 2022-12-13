#include <stdio.h>
#include <stdlib.h>

struct Node{
  int value;
  Node *next, *prev;
} *top;

Node *createNode(int value){
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

void pushStack(int value){
  Node *newNode = createNode(value);

  if (!top){
    top = newNode;
  }
  else{                      
    top->next = newNode;
    newNode->prev = top; 
    top = newNode;
  }
}

void removeStack(){
  if (!top){
    return;
  }
  else if (!top->prev){
    free(top);  
    top = NULL; 
  }
  else{
    Node *newTop = top->prev;
    top->prev = newTop->next = NULL;
    free(top);
    top = newTop;
  }
}

int topStack(struct Node *top){
	return top->value;
}

int main(){
	
	pushStack(1);
	pushStack(2);
	pushStack(3);
	removeStack();
	pushStack(4);
	pushStack(5);
	pushStack(6);
	removeStack();
	pushStack(7);
	removeStack();
	pushStack(8);
	pushStack(9);
	pushStack(10);
	pushStack(11);
	removeStack(); 
	
	
	struct Node *display;
	display = top;

//	print semua data di stack dari atas ke bawah
	if(!top){
		printf("Stack is empty.\n");
	}else{
		printf("Stack\n");
		while(display!=NULL){
			printf("%d\n", display->value);
			display = display->prev;
		}
	}
	printf("\n");
	
//	print top value
	printf("Top value : %d\n", top->value);
	
	return 0;
}
