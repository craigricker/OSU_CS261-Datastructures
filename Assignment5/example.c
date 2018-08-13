//
//  example.c
//  CS271
//
//  Created by Craig Ricker on 7/18/18.
//  Copyright © 2018 RICKERCR. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct DynArr
{
   int *data;      /* pointer to the data array */
   int size;      /* Number of elements in the array */
   int capacity;   /* capacity ofthe array */
};

int exampleFunction(struct DynArr * v) {
   struct DynArr * newArray = malloc(sizeof( DynArr));
   return 0;
}

int main() {
   struct DynArray * v = malloc(sizeof( DynArr));
   return 1;
}
