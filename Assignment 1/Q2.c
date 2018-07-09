/* CS261- Assignment 1 - Q.2*/
/* Name:
 * Date:
 * Solution description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    int * temp = a;
    a = b;
    b = a;
    
    /*Decrement the value of integer variable c*/
    (* c)--;
    /*Return c*/
    return (* c);
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x, y, z, returnVal;
    
    /*Print the values of x, y and z*/
    printf("x: %d\ty: %d\tz: %d", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    returnVal = foo(&x, &y, &z);
    /*Print the values of x, y and z*/
    printf("x: %d\ty: %d\tz: %d", x, y, z);
    /*Print the value returned by foo*/
    printf("foo return value: %d", returnVal);
 
    
    return 0;
}

/*
    a) Is the return value different than the value of integer z? Why or why not?
        This question is rather vague. foo() takes z as a reference parameter, and
        returns an int value. While in the function, it decrements (* c), so in this
        use case it effectively decrements z (by function call c = z). So although
        if you compare z and returnValue they will be equal to one another, they
        are distinct variables, and if you alter the values further, they may no
        longer be equal. This is evident because returnVal and z both have
        separate initializations, and thus have unique addresses from one another.
    b) Are the values of integers x and y different before and after calling the 
    function foo(..)? Why or why not?
        No, the values are not changed. Within the scope of foo() a and b swap
        what they are pointed to HOWEVER you are only swapping what these values 
        are actively pointing to, and not dereferencing and THEN swapping values.
*/
    
    


