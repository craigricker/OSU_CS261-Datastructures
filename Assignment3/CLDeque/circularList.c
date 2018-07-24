/*
 * This is the file in which you'll write the functions required to
 * implement
 * a circular list.  Make sure to add your name and
 @oregonstate.edu
 * email address below:
 *
 * Name: Craig Ricker
 * Email: rickercr@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
    list->size = 0;
    // Allocate space for sentinel, and point to itself
    list->sentinel = (struct Link *) malloc(sizeof(struct Link));
    list->sentinel->next = list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
    // Allocate space, set next/prev to null and then update with value
    struct Link * newLink = (struct Link *) malloc(sizeof(struct Link));
    newLink->next = newLink->prev = NULL;
    newLink->value = value;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
    // First create link
    struct Link * newLink =createLink(value);
    
    // Update newLink pointers
    newLink->prev = link;
    newLink->next = link->next;
    
    // Insert into linked list
    link->next->prev = newLink;
    link->next = newLink;
    
    // Update size
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	struct Link * currentLink = list->sentinel;
    
    // Find the link before link to be removed
    while (currentLink->next != link) {
        currentLink = currentLink->next;
    }
    
    // Remove the link from the space.
    link->next->prev = currentLink;
    currentLink->next = link->next;
    
    // Free & decrement size of list
    free(link);
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
    // Loop through array deleting all nodes until "empty"
    while (!circularListIsEmpty(list)) {
        circularListRemoveFront(list);
    }
    // Free up remaining elements of list
    free(list->sentinel);       // Remove authority
    list->sentinel = NULL;      // Remove access
    free(list);                 // Remove authority
    list = NULL;                // Remove access
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{   
    assert(!circularListIsEmpty(list));
    return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
    assert(!circularListIsEmpty(list));
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
    assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
    if (list->size == 0)
        return 1;
    else
        return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
    assert(!circularListIsEmpty(list));
    struct Link * current = list->sentinel->next;
    while (current != list->sentinel) {
        printf("%g\n", current->value);
        current = current->next;
    }
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// Assert list is not null
	assert(list != NULL);
	// If list is empty, don't need to reverse
	if (circularListIsEmpty(list))
		return;

	struct Link *reverse = list->sentinel;
	struct Link *drive = list->sentinel->next;

	for (int i = 0; i <= list->size; i++) {
		reverse->next = reverse->prev;
		reverse->prev = drive;

		reverse = drive;
		drive = drive->next;
	}

}
