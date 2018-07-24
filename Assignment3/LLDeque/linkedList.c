/*
 * This is the file in which you'll write the functions required to
 * implement
 * a linked list deque.  Make sure to add your name and
 @oregonstate.edu
 * email address below:
 *
 * Name: Craig Ricker
 * Email: rickercr@oregonstate.edu
 */
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
   list->size = 0;
   list->frontSentinel = (struct Link *) malloc(sizeof(struct Link));
   list->backSentinel = (struct Link *) malloc(sizeof(struct Link));
   // Make sure sentinel's point "inwards"
   list->frontSentinel->next = list->backSentinel;
   list->backSentinel->prev = list->frontSentinel;
   // Not circular list, point outside to "null"
   list->frontSentinel->prev = list->backSentinel->next = NULL;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
   // Allocate space, and store pointer to
   struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));
   
   // Update newLink to point at correct links
   newLink->next = link;
   newLink->prev = link->prev;
   
   // Insert newLink into linkedList
   link->prev->next = newLink;
   link->prev = newLink;
   newLink->value = value;
   
   // Increase size of linked list
   list->size++;
   
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
   assert(!linkedListIsEmpty(list));   // Ensure list isn’t empty
   link->prev->next = link->next;      // Update link before’s “next”, to point to next
   link->next->prev = link->prev;      // Update next’s previus
   free(link);                         // Remove authority
   link = NULL;                        // Remove access
   list->size--;                       // Decrease size
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
   addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
   assert(!linkedListIsEmpty(list));         // Ensure list isn’t empty
   return list->frontSentinel->next->value;

}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
   assert(!linkedListIsEmpty(list));         // Ensure list isn’t empty
   return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
   assert(!linkedListIsEmpty(list));         // Ensure list isn’t empty
   removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(!linkedListIsEmpty(list));         // Ensure list isn’t empty
   removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
   // If size != 0 list is empty
   if (list->size != 0)
      return 0;
   else
      return 1;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
   struct Link * current = list->frontSentinel;
   while (current->next != NULL) {
      printf("%d\n", current->value);
      current = current->next;
   }
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
   struct Link * current = list->frontSentinel;
   while (current->next != NULL) {
      if (current->value == value)
         return 1;               // Item found
      current = current->next;
   }
   return 0;                     // Item never found
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
   struct Link * current = list->frontSentinel;
   while (current->next != NULL) {
      if (current->value == value) {
         removeLink(list, current);
         return;
      }
      current = current->next;
   }
}
