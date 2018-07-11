/* CS261- Assignment 1 - Q.3*/
/* Name: Craig Ricker
 * Date: July 10, 2018
 * Solution description:
 * The user is prompted to enter a string, this is then converted
 * to camelCase - if it is an invalid string as defined by project
 * a message is printed, and program ends.
 */

#include <stdio.h>
#include <stdlib.h>

#define ASCII_OFFSET 32         // Difference between cases
#define BUFFER_SIZE 80          // Buffer size of acceptable input

/*********************************************************************
** Function: isLower
** Description: Checks if input is lower case
** Parameters: char ch: character to check
** Pre-Conditions: None
** Post-Conditions: Returns bool value on if input is lower case 
*********************************************************************/ 
int isLower(char ch){
   return ((ch >= 97) && (ch <= 122));
}


/*********************************************************************
** Function: isUpper
** Description: Checks if input is upper case
** Parameters: char ch: character to check
** Pre-Conditions: None
** Post-Conditions: Returns bool value on if input is upper case 
*********************************************************************/ 
int isUpper(char ch){
   return ((ch >= 65) && (ch <= 90));
}

/*********************************************************************
** Function: isLetter
** Description: Checks if input is a "letter" from the alphabet
** Parameters: char ch: char to be checked
** Pre-Conditions: None
** Post-Conditions: Returns bool value on if input is a letter
*********************************************************************/ 
int isLetter(char ch) {
   /* If the character is either upper or lower character
   ** then it is in fact a "letter" digit
   */
   if (isLower(ch) || isUpper(ch))
      return 1;
   else
      return 0;
}


/*********************************************************************
** Function: toUpperCase
** Description: Converts character to upperCase
** Parameters:  char ch: value to be converted
** Pre-Conditions: input is valid "letter" char
** Post-Conditions: ch is assured to be upperCase
*********************************************************************/ 
char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
   if (isUpper(ch))
      return ch;
   else
      return (ch - ASCII_OFFSET);
}

/*********************************************************************
** Function: toLowerCase
** Description: Converts input to lower case
** Parameters: char ch: character to convert
** Pre-Conditions: input is valid "letter" char
** Post-Conditions: Returns ch in lowercase
*********************************************************************/ 
char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
   if (isLower(ch))
      return ch;
   else
      return (ch + ASCII_OFFSET);
}


/*********************************************************************
** Function: String length
** Description: Counts digits in input until NULL is found
** Parameters: char s[]: input string
** Pre-Conditions: None
** Post-Conditions: returns length of input string
*********************************************************************/ 
int stringLength(char s[]) {
   /*Return the length of the string*/
   int strLen = 0;
   for (char * curCh = s; (* curCh) != '\0'; curCh++) {
      strLen++;
   }
   return strLen;
}

/*********************************************************************
** Function: camelValid
** Description: Checks if input is acceptable for camelCase
** Parameters: char * word: string to check
** Pre-Conditions: None
** Post-Conditions: Returns bool if acceptable or not
*********************************************************************/ 
int camelValid(char* word) {
    int inWord = 0;                           // Currently in a word?
    int wordCount = 0;                        // How many words?
    int wordLength = stringLength(word);      // Length of input word
   /* Loop through string, count # of words
   */
   for (int digit = 0; digit < wordLength; digit++) {
      if (isLetter((word[digit]))){
         if (inWord)
            continue;
         wordCount++;
         inWord = 1;
      }
      else {
         inWord = 0;
      }
   }
   
   /* if only one word, invalid */
   if (wordCount <= 1) {
      printf("invalid input string\n");
      return 0;
   }
  return 1;         // Valid
}



/*********************************************************************
** Function: camelCase
** Description: Converts input to camelCase 
** Parameters: char * word: word to be converted
** Pre-Conditions: None
** Post-Conditions: word is converted to camelCase 
*********************************************************************/ 
void camelCase(char* word){
	/*Convert to camelCase*/
   int wordLength = stringLength(word);      // Length of input word
   int prevLetter  = 0;                      // Check if previous was letter
   char buffer[BUFFER_SIZE] = "";                  // To store created output
   int bufferDigit = 0;                 // Location in output word

   
    /* Loop through input, and convert to camelCase as explained
    ** in assignment pdf.
    ** In this first loop, replace all non letters with _
    ** Remove leading/trailing, and reduce repeats
    ** If repeat is found, just continue without copying
    */
   for (int digit = 0; digit < wordLength; digit++) {
      if (isLetter((word[digit]))) {            // Letter found
         buffer[bufferDigit] = toLowerCase((word[digit]));
         /* You are now "in" a word, and successfully added
         ** character to buffer
         */
         prevLetter = 1;                        
         bufferDigit++;
      } 
      else {                                    // Non letter found
         if (prevLetter){
            buffer[bufferDigit] = '_';
            bufferDigit++;
         }
         prevLetter = 0;
      }
   }
   
   /* Similar logic to above
   ** Loop through, finding actual digits and print them out
    * if you encounter _ ignore it, and capitalize the next letter
   */
   wordLength = stringLength(buffer);
   prevLetter = 1;
   bufferDigit = 0;                 // Letter in output
   for (int digitN = 0; digitN < wordLength; digitN++) {
      if (isLetter(buffer[digitN])) {     // Digit is letter
         if (prevLetter) {                // Middle of word
            word[bufferDigit] = buffer[digitN];
         }
         else {                           // Begin of word
            word[bufferDigit] = toUpperCase(buffer[digitN]);
         }
         bufferDigit++;
         prevLetter = 1;                  // Now in middle of word
      }
      else
         prevLetter = 0;

   }
   word[bufferDigit] = '\0';              // Add terminating character
}

int main(){
    char input[BUFFER_SIZE];   // Container for user input
    
    
    /*Read the string from the keyboard*/
    printf("Please enter a value to be converted:");
    scanf ("%[^\n]%*c", input);
    
    /* If valid, convert and print */
    if (camelValid(input)){
        /*Call camelCase*/
        camelCase(input);


        /*Print the new string*/
        printf("%s\n", input);
    }


    return 0;
   
}

