/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link item to free
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map ADT to modify
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map ADT to modify
 */
void hashMapCleanUp(HashMap* map)
{
   assert(map);
   HashLink * deleteMe;
   HashLink * curr;
   // Loop through the hash, clearing up all items
   for (int i = 0; i < map->capacity; i++) {
      // As long as links are present in that hash, delete
      curr = map->table[i];
      while(curr) {
         deleteMe = curr;
         curr = curr->next;
         hashLinkDelete(deleteMe);
      }
   }
   free(map->table);
   map->size = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map item to modify
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map ADT to search
 * @param key what to lookup
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
   assert(map);
   assert(key);
   // Find location/bin where key is hashed to
   int loc = HASH_FUNCTION(key) % map->capacity;
   HashLink * cur = map->table[loc];
   
   // Look through all links, checking if key is present
   while (cur != NULL) {
      // If present, return value
      if (strcmp(cur->key, key) == 0)
         return &cur->value;
      // Progress to next link
      cur = cur->next;
   }
   
   // Checked all links within correct bin, not present
   return NULL;

}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map map to modify
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
   assert(map);
   assert(capacity >= map->capacity);
   HashMap * newMap = hashMapNew(capacity);
   
   // Loop through all buckets
   for (int i = 0; i < map->capacity; i++) {
      // Loop through each item within each bucket
      for (HashLink * cur = map->table[i]; cur != NULL;) {
         // Add to newMap
         hashMapPut(newMap, cur->key, cur->value);
         cur = cur->next;
      }
   }
   
   // Free up old map, and set to new value
   hashMapCleanUp(map);
   map->size = newMap->size;
   map->table = newMap->table;
   map->capacity = newMap->capacity;
   
   newMap->table = NULL;
   free(newMap);
   
   
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map map to modify
 * @param key key to enter
 * @param value value to enter
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
   assert(map);
   assert(key);

   // Find location/bin where key is hashed to
   int loc = HASH_FUNCTION(key);
   // Mod in order to be within size
   loc = loc  % map->capacity;
   int * overWrite;                 // To update value
   
   if (loc < 0) {
      loc += map->capacity;
   }
   
   // Look through all links, checking if key is present
   if (hashMapContainsKey(map, key)) {
      overWrite = hashMapGet(map, key);
      (*overWrite) += value;
   }
   else {
      map->table[loc] = hashLinkNew(key, value, map->table[loc]);
      map->size++;
      
   }
   
   if (hashMapTableLoad(map) >= (float) MAX_TABLE_LOAD)
      resizeTable(map, map->capacity * 2);
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map ADT to modify
 * @param key key to add
 */
void hashMapRemove(HashMap* map, const char* key)
{
   assert(map);
   assert(key);
   
   // Find location/bin where key is hashed to
   int loc = HASH_FUNCTION(key) % map->capacity;
   HashLink * cur = map->table[loc];
   HashLink * prev = NULL;
   
   // If not present, return false
   if (!hashMapContainsKey(map, key))
      return;


   
   // Look through all links, when exiting current
   // will be equal to the link before hand.
   while (strcmp(cur->key,key) != 0) {
      prev = cur;
      cur = cur->next;
   }
   
   // Remove from map
   if (prev)                           // If first, update next
      prev->next = cur->next;          // Link to delete
   // Special case where you're removing first item in map
   else
      map->table[loc] = cur->next;
   
   hashLinkDelete(cur);
   map->size--;
   
   
   
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map ADT to modify
 * @param key key to search for
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
   assert(map);
   assert(key);
   // Find location/bin where key is hashed to
   int loc = HASH_FUNCTION(key) % map->capacity;
   HashLink * cur = map->table[loc];
   
   // Look through all links, checking if key is present
   while (cur != NULL) {
      // If present, return 1
      if (strcmp(cur->key, key) == 0)
         return 1;
      // Progress to next link
      cur = cur->next;
   }
   
   // Checked all links within correct bin, not present
   return 0;
}

/**
 * Returns the number of links in the table.
 * @param map ADT to modify
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
   return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map ADT to modify
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
   return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map ADT to modify
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
   assert(map);
   int emptyBuckets = 0;
   for (int i = 0; i < map->capacity; i++) {
      if (map->table[i] == NULL)
         emptyBuckets++;
   }
   
   // Return # of empty buckets
    return emptyBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map ADT to modify
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
   // Cast to float and return
   return ((float) map->size)/((float) map->capacity);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map ADT to modify
 */
void hashMapPrint(HashMap* map)
{
   // Loop through the hash, printing all items
   for (int i = 0; i < map->capacity; i++) {
      // print all items
      printf("Bucket #%d:\n", i);
      for(HashLink * curr = map->table[i];
          curr != NULL;) {
         printf("%d\n", curr->value);
         curr = curr->next;
      }
   }

   
}
