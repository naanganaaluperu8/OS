#include<stdio.h>
#include<string.h>

char files[10][20];
int fcount = 0;

struct Dir{
    char name[20];
    int file[10];
    int count;
};

struct Dir d[5];
int dcount = 0;

int addDir(char name[]){

    strcpy(d[dcount].name, name);

    d[dcount].count = 0;

    dcount++;

    return dcount - 1;
}

int addFile(char name[]){

    strcpy(files[fcount], name);

    fcount++;

    return fcount - 1;
}

void linkFile(int dir, int file){

    d[dir].file[d[dir].count] = file;

    d[dir].count++;
}

void display(){

    int i, j;

    printf("\nDAG Directory Structure:\n");

    for(i = 0; i < dcount; i++){

        printf("%s:\n", d[i].name);

        for(j = 0; j < d[i].count; j++){

            printf("  %s\n",
                   files[d[i].file[j]]);
        }
    }
}

int main(){

    int alice, bob;
    int shared, notes;

    alice = addDir("alice");

    bob = addDir("bob");

    shared = addFile("shared.pdf");

    notes = addFile("notes.txt");

    linkFile(alice, shared);

    linkFile(bob, shared);

    linkFile(alice, notes);

    display();

    return 0;
}
