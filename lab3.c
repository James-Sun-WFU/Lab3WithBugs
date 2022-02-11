/**
 * This program reads a text file and prints the top 5 most frequent letters (upper or lower case)
 * and the top 5 most frequent digits that are in the file. If the file has less than 5 unique letters
 * and/or digits the top list is adjusted accordingly. The file name is provided using command line 
 * arguments. If the file name is not provided or the file is not readable, the program will exit
 * and provide an error message.
 *
 * @author James Sun {@literal sunh19@wfu.edu}
 * @date Feb.7th, 2022
 * @assignment Lab 2
 * @course CSC 250
 **/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_STRING_SIZE 20

/* a struct created for character frequency */  
struct WordFreq {
    char* word;
    int count;
};
 
/* function declarations here */
int processCharacters(struct WordFreq** wordListPtr, int* numWordsPtr,char filename[]);
void display(int alphaNum);
int search(char newWord[] , struct WordFreq** list, int *nPtr);
void add_word(char newWord[], struct WordFreq **listPtr, int *nPtr);

int main(int argc, char* argv[]){
    struct WordFreq* wordListPtr = NULL;
    int numWords = 0;
    int i;
    int fileOK = 1;
    

    if(argc < 3){
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }

    fileOK = processCharacters(&wordListPtr,&numWords,argv[1]);
    if(!fileOK){
        printf("%s could not be opened, and AJ is nice \n", argv[1]);
        return 1;
    }


     /* print the list to the screen */


    for(i = 0; i < numWords+1; i++)
        printf("list[%d] = %s, count %d \n", i, wordListPtr[i].word, wordListPtr[i].count);

    
     /* for(i = 0; i < n; i++) 
       if(wordList[i].word) free(wordList[i].word);
       if(wordlist) free(wordlist);
   */
    return 0;
}

/*this function processes characters by adding one to the count of the character proceeded if it was encountered before,      
*or it creates a new character in the array to store the count of it
*/
int processCharacters(struct WordFreq** wordListPtr, int* numWordsPtr,char filename[]) {

    FILE *filePtr = fopen(filename, "rie");
    char str[MAX_STRING_SIZE]; /*my only static array*/
    char ch;
    int i;
    int n=0;
    str[0] = '\0';  
    
    if(filePtr == 0){
        return 0;
    }

    printf("file name is %s \n", filename);

    

    ch = fgetc(filePtr);
    while(ch != EOF) {
        if(isalpha(ch)){
            
            ch = tolower(ch);
            str[n]=ch;
            n++;
            str[n] = '\0'; /*null terminator*/
            }else{
            if(n>0){ /*?*/
                printf("words[%s]\n",str);
                /*save to array? maybe?*/
                add_word(str,wordListPtr,numWordsPtr); 
                }
                n=0;
                str[n] = '\0';
            }
        ch = fgetc(filePtr);
    }

    fclose(filePtr);
    return 1;
}


/*this function displays the top five characters&digits and their counts. If there are less than five detected, 
*the display will be adjusted accordingly   */
void display(int alphaNum){
    
}

/*this function returns the location of the character searched in the list*/


int search(char newWord[] , struct WordFreq** list, int *nPtr){
    int i;
    for(i=0;i<*nPtr;i++){
        int judge = strcmp(newWord, list[i]->word);
        printf("judge is %d\n",judge);

        if(judge == 0){
            printf("search returns %d\n",i);
            return i;
        }
    }
    printf("search returns null\n");
    return (-1);
} 


void add_word(char newWord[], struct WordFreq**listPtr, int *nPtr) {
    struct WordFreq *tempList = NULL; /* temp list for copying */
    int i;
    printf("the size of the list before adding is %d\n",*nPtr);
    printf("The word added is %s\n",newWord);

    /*for(i=0;i<*nPtr;i++){
        printf("index %d is %s\n",i,listPtr[i]->word);
    }
    if(*nPtr == 0){
        tempList = (struct WordFreq *)malloc((*nPtr + 1) * sizeof(struct WordFreq));

    }*/

    int index = search(newWord,listPtr,nPtr);
    printf("index is %d\n",index);
    if(index > -1 && listPtr[index]->word != NULL){
        printf("the original count is %d\n",listPtr[index]->count);
        listPtr[index]->count++;
        printf("the updated count is %d\n",listPtr[index]->count);
        printf("words added\n \n");
    }else{
    /* create a temp list that is can store one more element */
    printf("new list made!\n");
    tempList = (struct WordFreq *)malloc((*nPtr + 1) * sizeof(struct WordFreq));

    /* copy the old list to temp_list */
    for(i = 0; i < *nPtr; i++) {
        tempList[i] = (*listPtr)[i];
    }

    /* let's add a new word to the end of the new list */
    /* make space to store the new word */
    tempList[i].word = (char *) malloc(strlen(newWord) + 1);
    /* copy the word over */
    strcpy(tempList[i].word, newWord);
    tempList[i].count = 1;

    

    /* let's free the old list (no memory leaks) */
    if(*listPtr) free(*listPtr);
    /* let's point to the new, larger list */
    *listPtr = tempList;
    /* added one more word, increase the count */
    (*nPtr)++;
    printf("the  size of the list after adding is %d\n",*nPtr);
    printf("words addition done\n \n");
    /*print the listptr*/
    
    }
}

/*why is there 33 null? */
/*free pointer problem? */
