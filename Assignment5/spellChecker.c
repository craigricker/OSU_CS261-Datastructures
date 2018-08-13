#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define N_TO_PRINT 5
#define MAX_INT 10000


/**
 * Calculates the levenshtein distance of two strings
 * adapted from https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance
 *
 * @param s1 first string
 * @param s2 second string
 * @return levenshtein score between the two strings
 */
int levenshtein(char *s1, char *s2) {
   unsigned int s1len, s2len, x, y, lastdiag, olddiag;
   s1len = (unsigned int) strlen(s1);     // Length of string 1
   s2len = (unsigned int) strlen(s2);     // Length of string 2
   // loop through and calculate value
   unsigned int column[s1len+1];
   for (y = 1; y <= s1len; y++)
      column[y] = y;
   for (x = 1; x <= s2len; x++) {
      column[0] = x;
      for (y = 1, lastdiag = x-1; y <= s1len; y++) {
         olddiag = column[y];
         column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
         lastdiag = olddiag;
      }
   }
   return(column[s1len]);
}


/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file Filestream to return word from
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
   int maxLength = 16;
   int length = 0;
   char* word = malloc(sizeof(char) * maxLength);
   while (1)
   {
      char c = fgetc(file);
      c = tolower(c);
      if ((c >= '0' && c <= '9') ||
          (c >= 'A' && c <= 'Z') ||
          (c >= 'a' && c <= 'z') ||
          c == '\'')
      {
         if (length + 1 >= maxLength)
         {
            maxLength *= 2;
            word = realloc(word, maxLength);
         }
         word[length] = c;
         length++;
      }
      else if (length > 0 || c == EOF)
      {
         break;
      }
   }
   if (length == 0)
   {
      free(word);
      return NULL;
   }
   word[length] = '\0';
   return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
   char * curWord = nextWord(file);
   
   // Loop through, adding each word to the map
   while (curWord) {
      hashMapPut(map, curWord, 1);
      free(curWord);
      curWord = nextWord(file);
   }
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
   HashMap* map = hashMapNew(1000);       // Container for dictionary
   HashLink * cur;                        // To loop through dictionary
   int leviScore;                         // Score of current vs input
   char matches[N_TO_PRINT][256];         // Track lowest 5 scores
   int matchScores[N_TO_PRINT];           // corresponding words
   
   // Load dictionary into hash
   FILE* file = fopen("/Users/craig/Documents/OSU_CS261/CS271/dictionary.txt", "r");
   assert(file);                          // Assert file opened
   clock_t timer = clock();
   loadDictionary(file, map);
   timer = clock() - timer;
   printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
   fclose(file);
   
   
   
   char inputBuffer[256];
   int quit = 0;
   // Loop through until user quits
   while (!quit)
   {
      // Set all stored scores to MAX_INT
      for (int i = 0; i < N_TO_PRINT; i++)
         matchScores[i] = MAX_INT;
      
      // Read in word
      printf("Enter a word or \"quit\" to quit: ");
      scanf("%s", inputBuffer);
      
      // User quit
      if (strcmp(inputBuffer, "quit") == 0)
      {
         quit = 1;
         continue;
      }
      // Word is spelled correctly
      else if (hashMapContainsKey(map, inputBuffer)) {
         printf("%s is spelled correctly.\n", inputBuffer);
         continue;
      }
      
      
      // Compare to each bucket
      for (int i = 0; i < hashMapCapacity(map); i++) {
         cur = map->table[i];
         // Look at all links within current bin
         while (cur) {
            // Calculate score
            leviScore = levenshtein(cur->key, inputBuffer);
            // Check if lower score then current values
            // If it is, slide over all scores and
            // word one place to the right
            for (int j = 0; j < N_TO_PRINT; j++) {
               if (leviScore < matchScores[j]) {
                  for (int k = N_TO_PRINT; k > j; k--) {
                     matchScores[k] = matchScores[k-1];
                     strcpy(matches[k], matches[k-1]);
                  }
                  // Store the scores
                  matchScores[j] = leviScore;
                  strcpy(matches[j], cur->key);
                  break;
               }
            }
            // Go to next node
            cur = cur->next;
         }
      }
      
      
      // Not present, print five closest matches
      // Defined as 5 lowest levi distances
      printf("The word %s is spelled incorrectly, did you mean:\n", inputBuffer);
      for (int i = 0; i < N_TO_PRINT; i++) {
         printf("%s\n", matches[i]);
      }
      
      
   }
   
   hashMapDelete(map);
   return 0;
}
