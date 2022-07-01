/*
while  developing a new web browser it feels that back, forward and refreshes buttonsare too boring, 
it feels that  showing the URL of the website which they point to would be a better approach, 

So inorder to implement this idea we use a Doubly Linked List on which

Following operations are possible
V <URL> : Visit the input URL
B <N> : Back N steps, in case not possible print “m back not possible”, then print as stated
F <N> : Forwards N steps print “m forward not possible”, then print as stated
Q <N> : Shows URL N step from the present URL (N is positive for forward and negative for
backward, in case N is out of bound print None)
D <N> : Delete Nth step URL from the present URL (N is positive for forward and negative for
backward, in case N is out of bound print None)
E : Exit
With each operation print (except Q and D) the URL of one step back, present (refresh) and one
step forward.



Assumptions and Clarifications:
1 - Browser has only 1 tab
3 - Back and Forward take place one step at a time, for example, if you want to go back 3 steps,
it would mean going back 2 steps then taking one more step backwards and so on.
4 - If no URL is present while front or back, we display “None”






Input is provided as:

V facebook.com
V google.com
V twitter.com
B 2
F 1
D 2
Q 1
B 1
D 2
F 3
E


Output We recieve :

none facebook.com none
facebook.com google.com none
google.com twitter.com none
none facebook.com google.com
facebook.com google.com twitter.com
none
twitter.com
none facebook.com google.com
2 forward not possible
facebook.com google.com none


*/


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <limits.h>
typedef struct node{
    char data[1000];
    struct node *next;
    struct node *prev;
}Node;
void print(Node *curr){
    if(curr==NULL){
        printf("none none none\n");
        return;
    }
    if(curr->prev!=NULL){
        printf("%s ",curr->prev->data);
        printf(curr->data);
        if(curr->next!=NULL){
            printf(" %s\n",curr->next->data);
        }
        else{
            printf(" none\n");
        }
    }
    else{
        printf("none ");
        printf(curr->data);
        if(curr->next!=NULL){
            printf(" %s\n",curr->next->data);
        }
        else{
            printf(" none\n");
        }
    }
}
int main(){
    char s[1000];
    gets(s);
    Node *head = NULL;
    Node *curr = NULL;
    while(s[0]!='E'){
        char ch = s[0];
        if(ch=='V'){
            Node *newnode = (Node*)malloc(sizeof(Node));
            newnode->next = NULL;
            newnode->prev = NULL;
            int i=2;
            for(;i<strlen(s);i++){
                newnode->data[i-2] = s[i];
            }
            newnode->data[i-2]='\0';
            if(head==NULL){
                head = newnode;
                curr = newnode;
            }
            else if(curr->next==NULL){
                curr->next = newnode;
                curr->next->prev = curr;
                curr = curr->next;
            }
            else{
                Node *temp = curr->next;
                curr->next = newnode;
                curr->next->prev = curr;
                curr = curr->next;
                Node *temp1 = NULL;
                while(temp!=NULL){
                    temp1 = temp;
                    temp = temp->next;
                    free(temp);
                }
                free(temp);
            }
            print(curr);
        }
        if(ch=='B'){
            int back_num = s[2] - '0';
            if(curr==NULL){
                printf("%d back not possible\n",back_num);
                print(curr);
            }
            else{
                while(back_num>0 && curr->prev !=NULL){
                    curr = curr->prev;
                    back_num--;
                }
                if(back_num>0){
                    printf("%d back not possible\n",back_num);
                    print(curr);
                }
                else{
                    print(curr);
                }
            }
        }
        if(ch=='F'){
            int front_num = s[2] - '0';
            if(curr==NULL){
                printf("%d forward not possible\n",front_num);
                print(curr);
            }
            else{
                while(front_num>0 && curr->next !=NULL){
                    curr = curr->next;
                    front_num--;
                }
                if(front_num>0){
                    printf("%d forward not possible\n",front_num);
                    print(curr);
                }
                else{
                    print(curr);
                }
            }
        }
        if(ch=='Q'){
            Node *temp =curr;
            if(s[2]=='-'){
                int back_num = s[3] - '0';
                if(temp==NULL){
                    printf("none\n");
                }
                else{
                    while(back_num>0 && temp->prev !=NULL){
                        temp = temp->prev;
                        back_num--;
                    }
                    if(back_num>0){
                        printf("none\n");
                    }
                    else{
                        printf("%s\n",temp->data);
                    }
                }
            }
            else{
                int front_num = s[2] - '0';
                if(temp==NULL){
                    printf("none\n");
                }
                else{
                    while(front_num>0 && temp->next !=NULL){
                        temp = temp->next;
                        front_num--;
                    }
                    if(front_num>0){
                        printf("none\n");
                    }
                    else{
                        printf("%s\n",temp->data);
                    }
                }
            }
        }
        if(ch=='D'){
            Node *temp =curr;
            if(s[2]=='-'){
                int back_num = s[3] - '0';
                if(temp==NULL){
                    printf("none\n");
                }
                else{
                    while(back_num>0 && temp->prev !=NULL){
                        temp = temp->prev;
                        back_num--;
                    }
                    if(back_num>0){
                        printf("none\n");
                    }
                    else{
                        if(temp->prev!=NULL){
                            temp->prev->next = temp->next;
                            if(temp->next!=NULL){
                                temp->next->prev = temp->prev;
                            }
                            free(temp);
                        }
                        else{
                            if(temp->next!=NULL){
                                temp->next->prev = temp->prev;
                            }
                            head = temp->next;
                            free(temp);
                        }
                    }
                }
            }
            else{
                int front_num = s[2] - '0';
                if(temp==NULL){
                    printf("none\n");
                }
                else{
                    while(front_num>0 && temp->next !=NULL){
                        temp = temp->next;
                        front_num--;
                    }
                    if(front_num>0){
                        printf("none\n");
                    }
                    else{
                        if(temp->prev!=NULL){
                            temp->prev->next = temp->next;
                            if(temp->next!=NULL){
                                temp->next->prev = temp->prev;
                            }
                            temp->prev = NULL;
                            free(temp);
                        }
                        else{
                            if(temp->next!=NULL){
                                temp->next->prev = temp->prev;
                            }
                            free(temp);
                        }
                    }
                }
            }
        }
    gets(s);   
    }
}