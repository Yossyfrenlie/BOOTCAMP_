#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Menu{
    char name[255];
    int quantity;
    int price;
    Menu *next, *prev;
}*head, *tail;

Menu *createMenu(const char *name, int quantity, int price){
    Menu *newMenu = (Menu *)malloc(sizeof(Menu));
    strcpy(newMenu->name, name);
    newMenu->quantity = quantity;
    newMenu->price = price;
    newMenu->next = newMenu->prev = NULL;
    return newMenu;
}

struct Order{
    int amount;
    char name[10][255];
    int quantity[10];
};

struct Customer{
    char name[255];
    Customer *next;
    struct Order ord;
}*head2[20], *tail2[20];

Customer *createCustomer(const char *name) {
  Customer *newCustomer = (Customer*)malloc(sizeof(Customer));
  strcpy(newCustomer->name, name);
  newCustomer->next = NULL;
  return newCustomer;
}

void mainMenu(){
    time_t waktu = time(NULL);
    printf("%s\n", ctime(&waktu));
    printf("1. Add Dish\n");
    printf("2. Remove Dish\n");
    printf("3. Add Customer\n");
    printf("4. Search Customer\n");
    printf("5. View Warteg\n");
    printf("6. Order\n");
    printf("7. Payment\n");
    printf("8. Exit Warteg\n");
    printf(">> ");
}

void addDish(const char *name, int price, int quantity){
    Menu *temp = createMenu(name, quantity, price);
	if(!head || quantity < head->quantity){
        //Push Head
        if (!head){
            head = tail = temp;
        }
        else{
            temp->next = head; 
            head->prev = temp;
            head = temp; 
        }
	}
	else if(quantity > tail->quantity){
        //Push Tail
        tail->next = temp; 
        temp->prev = tail; 
        tail = temp;
	}
	else{
        //Push Mid
		Menu *current = head;
    	
		while(current->next->quantity < quantity){
      		current = current->next;
    	}

		temp->prev = current;
		temp->next = current->next;
		current->next->prev = temp;
		current->next = temp;
	}

    printf("The dish has been added!\n");
    printf("Press enter to continue..."); getchar();
}

void removeDish(const char *name){
    if (!head){
        return;
    }
    //POP HEAD
    else if (strcmp(head->name, name) == 0){
        if (head == tail){
            free(head);
            head = tail = NULL;
        }
        else{
            Menu *newHead = head->next;
            head->next = newHead->prev = NULL;
            free(head);
            head = newHead;
        }
    }
    //POP TAIL
    else if (strcmp(tail->name, name) == 0){
            Menu *newTail = tail->prev;
            newTail->next = tail->prev = NULL; 
            free(tail);                        
            tail = newTail;
    }
    //POP MID
    else{
        Menu *current = head;
        while (current && strcmp(current->name, name) == 0){
        current = current->next;
        }
        current->prev->next = current->next;  
        current->next->prev = current->prev; 
        current->prev = current->next = NULL;
        free(current);
        current = NULL;
    }
    printf("The dish has been removed!\n");
    printf("Press enter to continue..."); getchar();
}

void displayMenu(int jmlh){
    Menu *temp = head;
    printf("Bude's Menu\n");
    printf("=========================================================================================\n");
    printf("No.\t Name\t\t Quantity\t Price\n");
    for(int i=1; i<=jmlh; i++){
        printf("%d.\t %s\t\t %d\t\t Rp%d\n", i, temp->name, temp->quantity, temp->price);
        temp = temp->next;
    }
    printf("=========================================================================================\n");
}

int compare(const char* deldish, int jmlh){
    Menu *temp = head;
    int flag = -1;
    for(int i=0; i<jmlh; i++){
        if(strcmp(deldish, temp->name) == 0){
            flag = 0;
        }
        else{
            flag = 1;
        }
    }
    return flag;
}

unsigned long djb2(const char *str) {
  unsigned long key = 5381;

  for(int i = 0; str[i] != '\0'; i++) {
    int ascii = int(str[i]);
    key = (key << 5) + key + ascii;
  }

  return key % 20;
}

void insert(const char *str) {
    Customer *newCustomer = createCustomer(str);
    int index = djb2(str);

    if(!head2[index]){
        head2[index] = tail2[index] = newCustomer;
    } 
    else{
        tail2[index]->next = newCustomer;
        tail2[index] = newCustomer;
    }
    printf("Customer has been added!\n");
    printf("Press enter to continue..."); getchar();
}

void traverseLL(int i){
    Customer *curr = head2[i];
    while(curr){
        printf("%s -> ", curr->name);
        curr = curr->next;
    }
    puts("NULL"); 
}

void read(){
    printf("Customer's List\n");
    for(int i=0; i<20; i++){
        // printf("%ld. ", djb2(head2[i]));
    if(head2[i]){
      traverseLL(i);
    }
    else{
      puts("NULL");
    }
  }
  printf("Press Enter to continue..."); getchar();
}

int search(const char *name){
    int index = djb2(name);

    Customer *temp = head2[index];

    while(temp != NULL && strcmp(name, temp->name) != 0){
        temp = temp->next;
    }

    if(temp == NULL){
        return 0;
    }

    return 1;
}

int main(){
    int inputMainMenu;

    struct Menu dish;
    int jmlh= 0;

    do{
        mainMenu();
        scanf("%d", &inputMainMenu); getchar();

        if(inputMainMenu == 1){
            int count;
            do{
                printf("Insert the name of the dish [Lowercase letters]:");
                scanf(" %[^\n]", dish.name); getchar();
                int temp = strlen(dish.name)-1;
                count = 0;
                for(int i=0; i<=temp; i++){
                    if(dish.name[i] < 97 || dish.name[i] > 122){
                        if(dish.name[i] == 32){
                            break;
                        }
                        else{
                            count = 1;
                        }
                    }
                }
            }while(count == 1);

            do{
                printf("Insert the price of the dish [1000..500000]:");
                scanf("%d", &dish.price); getchar;
            }while(dish.price < 1000 || dish.price > 50000);

            do{
                printf("Insert the quantity of the dish [1..999]:");
                scanf("%d", &dish.quantity); getchar();
            }while(dish.quantity < 1 || dish.quantity > 999);

            addDish(dish.name, dish.price, dish.quantity);
            jmlh++;
        }
        if(inputMainMenu == 2){
            displayMenu(jmlh);
            char deldish[255];
            do{
                printf("Insert dish's name to be deleted:");
                scanf("%[^\n]", deldish);
                if(compare(deldish, jmlh) == 1){
                    removeDish(deldish);
                    jmlh--;
                    break;
                }
            }while(true);
        }
        struct Customer cust;
        if(inputMainMenu == 3){
            int count2;
            do{
                printf("Insert the customer's name [Without space]: ");
                scanf(" %[^\n]", cust.name); getchar();
                int temp = strlen(cust.name)-1;
                count2 = 0;
                for(int i=0; i<=temp; i++){
                    if(cust.name[i] == 32){
                        count2 = 1;
                        break;
                    }
                }
            }while(count2 == 1);
            insert(cust.name);
        }
        if(inputMainMenu == 4){
            printf("Insert the customer's name to be search: ");
            scanf(" %[^\n]", cust.name); getchar();
            if(search(cust.name) == 1){
                printf("%s is present\n", cust.name);
            }
            else if(search(cust.name) == 0){
                printf("%s is not present\n", cust.name);
            }
            printf("Press Enter to continue..."); getchar();
        }
        // if(inputMainMenu == 5){
        //     read();
        // }
        // int amount;
        // char dishname[amount+3];
        // int dishquantity[amount+3];

        // if(inputMainMenu == 6){

        //     do{
        //         printf("Insert the customer's name to be search: ");
        //         scanf(" %[^\n]", cust.name); getchar();
        //     }while(search(cust.name) == 0);
            
        //     do{
        //         printf("Insert the amount of dish: ");
        //         scanf("%d", &cust.ord.amount); getchar();
        //     }while(cust.ord.amount < 1 || cust.ord.amount > jmlh);

        //     int flag = -1;
        //     for(int i = 1; i <= cust.ord.amount; i++){
        //         do{
        //             printf("[%d] Insert the dish's name and quantity: ", i);
        //             scanf("%[^\n]", cust.ord.name[i]);getchar();
        //             scanf(" x%d", &cust.ord.quantity[i]);getchar();
        //             if(search(cust.ord.name[i]) == 0){
        //                 flag = 0;
        //             }
        //         }while(flag = -1);
        //     }
        //     printf("Order success!\n");
        //     printf("Press enter to continue...\n");
        // }
        // if(inputMainMenu == 7){
        //     int index;
        //     do{
        //         printf("Insert the customer's index: ");
        //         scanf("%d", &index);
        //     }while();
            
        //     printf("%s\n", );
        //     for(int i=1; i< ; i++){
        //        printf("[%d] %s x%d");
        //     }
        //     printf("Total: Rp%d\n");
        //     printf("Press enter to continue...\n");
        // }
        if(inputMainMenu == 8){
            printf("Please expand your terminal to full screen!\n");
            printf("Press enter to continue...");getchar();
        }
    }while(inputMainMenu != 8);

    return 0;
}
