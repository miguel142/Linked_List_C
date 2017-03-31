#include <stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

struct node {
    int data;
    char* str;
    struct node* next;
    struct node* prev;
};

/*These are the print stats functions*/

int getlength(struct node* head) { // gets the length if the list
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }

    return length;
}

int getMinNum(struct node* head){ // gets the lowest number on the list
    int minNum;
    while(head->next != NULL){
        head = head->next;
    }
    minNum = head->data;

    return minNum;
}

float getAverage(struct node* head){ // adds all the list and calculates the average
    float length = 0;
    float total = 0;
    float average;

    while(head != NULL){
        length++;
        total = total + head->data;
        head = head->next;
    }

    average = total/length;
    return average;

}

void printStats(struct node** headRef){ // the main function to print out all the stats
    struct node* head = *headRef;
    int nodeNum;
    int maxNum;
    int minNum;
    float aveNum;

    nodeNum = getlength(head);
    printf("No. of nodes = %d\n",nodeNum); fflush(stdout);

    maxNum = head->data;
    printf("Max. count = %d\n", maxNum); fflush(stdout);

    minNum = getMinNum(head);
    printf("Min. count = %d\n", minNum); fflush(stdout);

    aveNum = getAverage(head);
    printf("Avg. count =%6.2f\n", aveNum); fflush(stdout);

}

/*These are the insert node function*/

void print_list(struct node** headRef){ // This prints the list

    struct node* head = *headRef;
    if(head == NULL ){
        printf("its empty"); fflush(stdout);
    }

   while (head != NULL){
        printf("%d  %s\n", head->data, head->str); fflush(stdout);
        head = head->next;
   }

    return;
}

void append_data(struct node** headRef, char* str){ //This creates the node and adds it at the end of the list
    assert(headRef != NULL);
    int data = 1;

    if (*headRef == NULL) {
        *headRef = (struct node*)malloc(sizeof(struct node));
        (*headRef)->data = data;
        (*headRef)->str = str;
        (*headRef)->next = NULL;
        (*headRef)->prev = NULL;
        return;
    }

    struct node* head = *headRef;
    while (head->next != NULL) {
        head = head->next;
    }

    head->next = (struct node*)malloc(sizeof(struct node));
    head->next->data = data;
    head->next->str = str;
    head->next->next = NULL;
    head->next->prev = head;
}

void compareNode(struct node** headRef, char* str){ //This compares the added string with the list and it increments
                                                    // the number.
    assert(headRef != NULL);
    if(*headRef == NULL){
        append_data(headRef, str);
        return;
    }

    struct node* head = *headRef;

    while(head != NULL){

        if(strcmp(head->str, str) == 0){
            head->data++;

           while(head->prev != NULL) {

               if(head->data > head->prev->data) {
                   int temp = head->data;
                   int temp2 = head->prev->data;
                   head->data = temp2;
                   head->prev->data = temp;

                   char* temp3 = head->str;
                   char* temp4 = head->prev->str;
                   head->prev->str = temp3;
                   head->str = temp4;

               }
               head = head->prev;
           }
            return;
        }
        head = head->next;

    }

    append_data(headRef, str);
    return;
}

/*these are the delete functions*/

void deleteNode(struct node** headRef, char* str) { //This decrements the number of the node and deletes if 0
    assert(headRef != NULL);

    struct node* head = *headRef;
    while (head != NULL && strcmp(head->str, str) != 0) {
        head = head->next;
    }

    if (head == NULL) {
        return;
    }

    head->data--;

    if(head->data == 0) {
        if (head->prev != NULL) {
            head->prev->next = head->next;
        } else {
            *headRef = head->next;
        }

        if (head->next != NULL) {
            head->next->prev = head->prev;
        }

        head->prev = NULL;
        head->next = NULL;
        free(head);
        return;
    }

    if(head->data < head->next->data){
        while(head->next != NULL){
            int temp = head->data;
            int temp2 = head->next->data;
            head->data = temp2;
            head->next->data = temp;

            char *temp3 = head->str;
            char *temp4 = head->next->str;
            head->str = temp4;
            head->next->str = temp3;

            head = head->next;
        }
    }
    return;
}

void forceDelete(struct node** headRef, int num){ //this force deletes all the nodes less than the number
    struct node* head = *headRef;
    struct node* temp = NULL;

    while(head != NULL && head->data > num){
        head = head->next;
    }

    if(head != NULL){
        while(head!=NULL){
            temp = head->next;
            head->prev->next = NULL;
            head->next = NULL;
            head->prev = NULL;
            free(head);

            head = temp;
        }
    }
}


/*These are the fix functions*/

void countRange(struct node** headRef, int r1, int r2){ // this prints the nodes this range
    struct node* head = *headRef;

    if(head == NULL){
        printf("Ths list is empty");
    }

    if(r1 > r2) {

        while (head != NULL) {
            if (head->data > r1 || head->data < r2) {
                head = head->next;
            } else {
                printf("%d  %s\n", head->data, head->str); fflush(stdout);
                head = head->next;
            }
        }
    }

    else{
        while (head != NULL) {
            if (head->data < r1 || head->data > r2) {
                head = head->next;
            } else {
                printf("%d  %s\n", head->data, head->str); fflush(stdout);
                head = head->next;
            }
        }
    }
}

void printPrefix(struct node** headRef, char* str){ // this prints the nodes with the same prefix
    assert(headRef != NULL);
    struct node* head = *headRef;

    if(head == NULL){
        printf("The list is empty.");
        return;
    }

    int len;
    len = strlen(str);

    while(head != NULL){
        if(strncmp(head->str, str, len-1) == 0){
            printf("%d  %s\n",head->data, head->str); fflush(stdout);
        }
        head = head->next;
    }
}

void printSufix(struct node** headRef, char* str){ // this prints the nodes with the same suffix
    struct node* head = *headRef;

    if(head == NULL){
        printf("The list is empty.");
        return;
    }

    int len;
    len = strlen(str);


    while(head != NULL){
        int headLen;
        headLen = strlen(head->str);
        headLen = headLen - len;
        if(strncmp(head->str+headLen, str, len) == 0){
            printf("%d  %s\n",head->data, head->str); fflush(stdout);
        }
        head = head->next;
    }
}

/*This is the main that ask the user for the inputs and instructions to do with the list*/

int main() {
    struct node *head = NULL;
    int stop = 0;

    while(stop != 1){

        char* str1;

        str1 = malloc(50);

        printf("Please enter a command: \n"); fflush(stdout);
        fgets(str1, 50, stdin);

        char* str2 = strdup(str1+4);

        if(strncmp("ins", str1, 3)== 0){
          compareNode(&head, str2);
        }

        if(strncmp("prl", str1, 3)==0){
          print_list(&head);
        }

        if(strncmp("del", str1, 3)==0){
            deleteNode(&head, str2);
        }

        if(strncmp("pst", str1, 3)==0){
            printStats(&head);
        }

        if(strncmp("pcr", str1, 3)==0){
            int num1;
            int num2;

            num1 = str1[4]-'0';
            num2 = str1[6]-'0';

            countRange(&head, num1, num2);

        }

        if(strncmp("ppr", str1, 3)==0){
            printPrefix(&head, str2);
        }

        if(strncmp("psu", str1, 3)==0){
            printSufix(&head, str2);
        }

        if(strncmp("fde", str1, 3)==0){
            int num3;
            num3 = str1[4]-'0';

            forceDelete(&head, num3);
        }

        if(strncmp("end", str1, 3)==0){
          stop++;
        }
   }

    return 0;

}



