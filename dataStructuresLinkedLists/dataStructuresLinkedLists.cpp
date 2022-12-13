#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};
struct Node* head = NULL;

int isEmpty();
void add(int);
void remove();
void insert(int);
void eliminate();
int countList();
void printList();

int main()
{
	int choice;
	int number;
	while (1)
	{
		printf("1. Add item\n");
		printf("2. Remove item\n");
		printf("3. Insert item\n");
		printf("4. Eliminate item\n");
		printf("5. Print list\n");
		printf("6. Clear the console\n");
		printf("7. Exit program\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Enter a number to add: ");
			scanf("%d", &number);
			add(number);
			break;
		case 2:
			remove();
			break;
		case 3:
			printf("Enter a number to insert: ");
			scanf("%d", &number);
			insert(number);
			break;
		case 4:
			eliminate();
			break;
		case 5:
			printList();
			break;
		case 6:
			system("cls");
			break;
		case 7:
			return 0;
		default:
			printf("Wrong input!\n");
			break;
		}
	}
}

int isEmpty() // this function checks if the list is empty or not
{
	if (head == NULL)
	{
		return 1; // since there is no boolean data type in C, we take 1 as true,
	}
	return 0; // and 0 as false.
}

void add(int item) // adding an item to the list
{
	struct Node* newItem = NULL;							// creating a variable called newItem as a Node pointer.
	newItem = (struct Node*)malloc(sizeof(struct Node));	// creating some space in the memory for the variable that is as large as the size of our Node structure but assigning this as a Node pointer.
	newItem->data = item;									// assigning the value to the data of our new item.
	newItem->next = NULL;
	if (isEmpty())											// if the link is empty we can only assign head, there is no tail right now.
	{
		head = (struct Node*)malloc(sizeof(struct Node));
		head = newItem;
		return;
	}
	struct Node* tail = NULL;
	tail = (struct Node*)malloc(sizeof(struct Node));
	tail = head;			   // our tail now points to head but this will change now:
	while (tail->next != NULL) // with every step of this while loop our tail goes 1 item forward until there is no item next.
	{
		tail = tail->next;
	}
	tail->next = newItem; // after the loop is over we now have the tail in our hands. we want our newItem to be the tail now.
	tail = newItem;		  // so we assign new item to current tails next item and then assign our new item to current tail.
}

void remove() // removing the last item from list
{
	if (isEmpty()) // if the list is empty
	{
		printf("List is empty!\n"); // we print that on screen and return from the function.
		return;						// if this block runs, next lines in this function won't run because of the return;
	}
	int len = countList();
	if (len == 1)					//if the length is 1, there is only head in the list.
	{								// so we can just remove that.
		head = NULL;
		return;
	}
	struct Node* tail = NULL;
	tail = (struct Node*)malloc(sizeof(struct Node));
	tail = head;
	while (tail->next->next != NULL) // this while loop is slightly different because it doesn't check the current
	{								 // tail's next item, it checks the next item's next item.
		tail = tail->next;			 // after this while loop ends our tail variable will be the previous item of the actual tail of the list.
	}
	tail->next = NULL; // our tail variable was the item before the actual tail. we made the next item NULL so the tail variable is now actual tail.
}

void insert(int item) // inserting an item after the n th item to the list
{
	if (isEmpty()) // if the list is empty we can't insert an item to somewhere in the list.
	{			   // so we'll just add the item and it will be the head.
		printf("List is empty! Adding the item instead of inserting.\n");
		add(item);
		return;
	}
	struct Node* newItem = NULL;
	newItem = (struct Node*)malloc(sizeof(struct Node));
	newItem->data = item;
	int len = countList(); // we assigned the length of the list to len variable.
	int n;
	printf("After which item would you like to add the new item?\n");
	scanf("%d", &n);
	if (n > len)
	{
		printf("Number cannot be greater than the length of the list!\n");
		return;
	}
	if (n == len) // if number is equal to length it means that we are adding the item to the end of the list.
	{			  // so we can use the add() function which does the thing we want.
		add(item);
		return;
	}
	if (n == 0) // if number is 0 it means that we want to add the item in the beggining of the list.
	{
		newItem->next = head; // so we take our new item and assign our current head to it's next item
		head = newItem;		  // then we'll assign our new item as the current head.
		return;
	}
	struct Node* temp = NULL;
	temp = (struct Node*)malloc(sizeof(struct Node));
	temp = head;
	for (int i = 1; i < n; i++) // our first item is head and because of that the for loop starts with i as 1 not 0.
	{							// until we reach n th item temp keeps going 1 item forward.
		temp = temp->next;
	}
	newItem->next = temp->next; // after the loop ends our temp is our n th item.
	temp->next = newItem;		// since we want the new item come after the n th item we have to make these changes:
}								// new item's next item should be n th item's next item, n th item's next item should be new item.

void eliminate() // eliminating the n th item from the list
{
	if (isEmpty())
	{
		printf("List is empty!\n");
		return;
	}
	int len = countList();
	int n;
	printf("Which item would you like to remove?\n");
	scanf("%d", &n);
	if (n > len)
	{
		return;
	}
	if (n == 0)
	{
		printf("Number cannot be 0!\n");
		return;
	}
	if (n == len)
	{
		remove();
		return;
	}

	struct Node* temp = NULL;
	temp = (struct Node*)malloc(sizeof(struct Node));
	temp = head;
	for (int i = 1; i < n - 1; i++) // same thing goes here with 1 difference: the loop continues 1 step less.
	{								// this is because if we want to remove n th item we should make the n-1th item's next item, the n+1th item.
		temp = temp->next;			// so after the loop ends, temp becomes the n-1th item.
	}
	temp->next = temp->next->next;
}

int countList() // counting the list
{
	int counter = 0;
	if (isEmpty())
	{
		return counter;
	}
	struct Node* temp = NULL;
	temp = (struct Node*)malloc(sizeof(struct Node));
	temp = head;
	while (temp != NULL) // this loop checks if the temp is NULL or not instead of temp's next item is NULL or not.
	{					 // this is because if the temp's next item is NULL the loop would end and we would count 1 item less.
		temp = temp->next;
		counter++;
	}
	return counter;
	/*
		another solution to this would be:
		while (temp->next != NULL)
		{
			temp = temp->next;
			counter++;
		}
		counter++;
	*/
}

void printList() // printing the list
{
	if (isEmpty())
	{
		printf("List is empty!\n");
		return;
	}
	struct Node* temp = NULL;
	temp = (struct Node*)malloc(sizeof(struct Node));
	temp = head;
	while (temp != NULL) // same thing goes here.
	{
		printf("%d<==", temp->data);
		temp = temp->next;
	}
	printf("\n");
}