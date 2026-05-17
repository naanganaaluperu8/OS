#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node{
    char name[20];
    int dir;
    struct Node* child;
    struct Node* next;
};

struct Node* create(char name[], int dir){

    struct Node *n;

    n = malloc(sizeof(struct Node));

    strcpy(n->name, name);

    n->dir = dir;

    n->child = NULL;
    n->next = NULL;

    return n;
}

void add(struct Node* p, struct Node* c){

    if(p->child == NULL){

        p->child = c;
    }
    else{

        struct Node* t = p->child;

        while(t->next != NULL){

            t = t->next;
        }

        t->next = c;
    }
}

void display(struct Node *r, int d){

    if(r == NULL){
        return;
    }

    for(int i = 0; i < d; i++){
        printf("  ");
    }

    if(r->dir == 1)
        printf("[DIR] %s\n", r->name);
    else
        printf("[FILE] %s\n", r->name);

    display(r->child, d + 1);

    display(r->next, d);
}

int main(){

    struct Node* root;
    struct Node* home;
    struct Node* file1;
    struct Node* file2;

    root = create("root",1);

    home = create("home",1);

    file1 = create("notes.txt",0);

    file2 = create("photo.txt",0);

    add(root,home);

    add(home,file1);

    add(home,file2);

    printf("Directory Structure:\n");

    display(root,0);

    return 0;
}
