/* CS261- Assignment 1 - Q.1*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TEST_LOW_LIM 0
#define TEST_HI_LIM 101
#define ID_LO_LIM 1
#define ID_HI_LIM 11
#define STUDENT_NUMB 10

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     return malloc(sizeof(student) * STUDENT_NUMB);
     /*Return the pointer*/
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/

    for (int studN = 0; studN < STUDENT_NUMB; studN++){
        students[studN]->id = rand() % ID_HI_LIM;
        students[studN]->id+= ID_LO_LIM;
        ENSURE THAT ID IS RANDOM< NOT COMMENT< PREVENT COMP
        
        students[studN]->score = rand() % TEST_HI_LIM;
        students[studN]->score+= TEST_LOW_LIM;
     
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    for (int studN = 0; studN < STUDENT_NUMB; studN++) {
        printf("%d\t%d", students[studN]->id, \
            students[studN]->score);
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
    int minScore, maxScore, averageScore, currentScore;
    minScore = maxScore = averageScore = 0;
    for (int studN = 0; studN < STUDENT_NUMB; studN++) {
        currentScore = students[studN]->score;
        if (currentScore < minScore):
            minScore = currentScore;
        if (currentScore > maxScore):
            maxScore = currentScore;
        averageScore += currentScore;
    }
    averageScore = averageScore / STUDENT_NUMB;
    printf("Minimum: %d\nMaximum: %d\nAverage: %d", 
        minScore, maxScore, averageScore);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free(stud);
     stud = 0;
}

int main(){
    struct student* stud = NULL;
    
    /*Call allocate*/
    stud = allocate();
    /*Call generate*/
    generate(stud);
    /*Call output*/
    output(stud);
    /*Call summary*/
    summary(stud);
    /*Call deallocate*/
    deallocate(stud);
    return 0;
}

