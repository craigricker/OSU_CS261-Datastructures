/* CS261- Assignment 1 - Q.1*/
/* Name:    Craig Ricker
 * Date:    July 10, 2018
 * Solution description:
 * This program is an exploration of how to properly use 
 * structures, and create object specific functions as a 
 * type of "member function".
 * In this, we produce 10 students with random but unique IDs,
 * give them a test score, print out the student information and
 * an aggregation of the max/min/average scores.
 */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TEST_LOW_LIM 0
#define TEST_HI_LIM 101
#define ID_LO_LIM 1
#define ID_HI_LIM 10
#define STUDENT_NUMB 10

struct student{
	int id;
	int score;
};

/*********************************************************************
** Function:        allocate
** Description:     Allocate memory for STUDENT_NUMB of students,
**                  returns pointer to allocated space
** Parameters:      None
** Pre-Conditions:  None
** Post-Conditions: Space is allocated for an array of students
*********************************************************************/ 
struct student* allocate(){
     /*Allocate memory for ten students*/
     return malloc(sizeof(struct student) * STUDENT_NUMB);
     /*Return the pointer*/
}


/*********************************************************************
** Function:        isStudentUnique
** Description:     Loops through students, checks if newId has 
**                  yet been used.
** Parameters:      struct student * students: students to checks
**                  int newId: potential id
** Pre-Conditions:  None
** Post-Conditions: Bool return if newId is used yet or not.
*********************************************************************/ 
int isStudentUnique(struct student * students, int newId) {
   for (int studN = 0; studN < STUDENT_NUMB; studN++) {
      //printf("Potential is %d, current id is %d on loop %d\n", newId, students[studN].id, studN);
      if (newId == students[studN].id)
         return 0;
   }
   return 1;
}


/*********************************************************************
** Function:        generate
** Description:     Produces random but unique 
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/ 
void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/
   int potentialID;     // Number to potentially assign to student
    /* Loop through STUDENT_NUMB of students, generating a unique
    ** id for each student. Do this by not assigning ID until
    ** a uniqueID is located, by a call to isStudentUnique
    */
    for (int studN = 0; studN < STUDENT_NUMB; studN++){
        
       do {
         potentialID = rand() % ID_HI_LIM;
         potentialID += ID_LO_LIM;
       }while (!isStudentUnique(students, potentialID));
       
       // Assign values when unique ID found
       students[studN].id = potentialID;
       students[studN].score = rand() % TEST_HI_LIM;
       students[studN].score+= TEST_LOW_LIM;
    }
     
}


/*********************************************************************
** Function:        output()
** Description:     Loops through students, and prints out id and
**                  test score
** Parameters:      student * students: array of students
** Pre-Conditions:  None
** Post-Conditions: None
*********************************************************************/ 
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    for (int studN = 0; studN < STUDENT_NUMB; studN++) {
       printf("%d\t%d\n", students[studN].id, \
              students[studN].score);
    }
}


/*********************************************************************
** Function:        summary
** Description:     Loops through students, calculates min, max and
**                  average score
** Parameters:      student * students: array of students
** Pre-Conditions:  None
** Post-Conditions: None
*********************************************************************/ 
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
    float averageScore;                     // Rolling sum for average
    int minScore, maxScore, currentScore;   // Store found values
    maxScore = averageScore = 0;
    minScore = TEST_HI_LIM;
    
    /* Loop through all students, updating min, max if
    ** a value is found to replase these.
    ** calculates the rolling sum with averageScore,
    ** which will then be used to calculate average at end of loop
    */
    for (int studN = 0; studN < STUDENT_NUMB; studN++) {
       currentScore = students[studN].score;
        if (currentScore < minScore)
            minScore = currentScore;
        if (currentScore > maxScore)
            maxScore = currentScore;
        averageScore += currentScore;
    }
    
    // Calculate average and print all values
    averageScore = averageScore / STUDENT_NUMB;
    printf("Minimum: %d\nMaximum: %d\nAverage: %f\n",
        minScore, maxScore, averageScore);
}

/*********************************************************************
** Function:            deallocate
** Description:         Free memory at input location, and update 
**                      pointer to null to remove access
** Parameters:          student * stud: memory to free
** Pre-Conditions:      stud* point to memory dynamically allocated
** Post-Conditions:     memory at stud is destroyed, and pointer 
**                      now points to null.
*********************************************************************/ 
void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free(stud);
     stud = NULL;
}

int main(){
   /* Seed srand using time */
    srand((unsigned int) time(NULL));
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

