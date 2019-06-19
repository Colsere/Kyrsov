#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct na{
    char second[50];
    char first[50];
} nam;

 typedef struct camps{
    nam *name;
    nam *parent;
    char tp[11];
    int group;
    int shift;

} camp;

typedef struct LNode{
    camp* data;
    struct LNode* next;
}LN;

void(*func[2])(LN* l, int N);

camp *getP(FILE *input){
    camp* result;
    result = (camp*)malloc(sizeof(camp));
    if(result!=NULL){
        fscanf(input, "%d %d %s %s %s %s %s",
                &result->shift, &result->group, &result->name->second, &result->name->first, &result->parent->second, &result->parent->first, &result->tp);

    }
    return result;
}

LN* getL(FILE* f){
    LN* l;
    l = (LN*)malloc(sizeof(LN));
    if(l!=NULL){
        l->data = getP(f);
        l->next = NULL;
    }
    return l;
}

LN* createnewNode(){
    LN* newNode;
    camp* result;
    result = (camp*)malloc(sizeof(camp));
    if(result!=NULL){
        printf("Enter second name and the first one of the child: ");
        scanf("%s %s", &result->name->second, &result->name->first);
        printf("Enter his/her camping shift (1->4) and group(1->5): ");
        scanf("%d %d", &result->shift, &result->group);
        printf("Enter second and first name of his/her parent and then number of telephone: ");
        scanf("%s %s %s", &result->parent->second, &result->parent->first, &result->tp);
    newNode = (LN*)malloc(sizeof(LN));
    if(newNode!=NULL){
        newNode->data = result;
        newNode->next = NULL;
    }}
    return newNode;
}


void printP(camp* child){
    printf("%d: %d | %s %s | %s %s: %s");
    for(int i = 0; i< 120; i++){
        printf("-");
    }
    printf("%s %s from group number: %d %d camping shift", child->name->second, child->name->first, child->group, child->shift);
    for(int i = 0; i< 120; i++){
        printf("-");
    }
    printf("\nParents: %s %s\t|%d", child->parent->second, child->parent->first, child->tp);
    for(int i = 0; i< 120; i++){
        printf("-");
    }

}

void fprintP(FILE* f, camp* p){

    fprintf(f, "%d %d %s %s %s %s %s", p->shift, p->group, p->name->second,
                p->name->first, p->parent->second, p->parent->first, p->tp);
}

void printNode(LN* l){
    printP(l->data);
}

void fprintNode(FILE* f, LN* l){
    fprintP(f, l->data);
}

void deleteNode(LN* l, int ID, int N){
    LN* prew, *tmp;
    LN* now = l;
    if(ID == N){
        for(int i = 0; i < N-2; i++){
            now = now->next;
        }
        free(now->next->data);
        free(now->next);
        now->next = NULL;
    }
    else if(ID == 1){
        free(now->data);
        now->data = NULL;
        for(int i = 0; i< N-1; i++){
            now->data = now->next->data;
            now = now->next;
        }
        now->next = NULL;
    }
    else if(ID < N){
        for(int i = 1 ; i < ID; i++){
            prew = now;
            now = now->next;
        }
        prew->next = now->next;
        free(now->data);
        free(now);
    }
}

int comperison(char* a, char* b){
    int result;
    int i = 0, flag = 1;
    while(a[i]!='\0' && b[i]!='\0' && flag == 1){
        if(a[i] > b[i]){
            result = 1;
            flag = 0;
        }
        else if(a[i] < b[i]){
            result = 2;
            flag = 0;
        }
        else{
            result = 0;
            i++;
        }
    }
    return result;
}


void swap(LN* l, LN* n){
    camp* tmp;
    tmp = l->data;
    l->data = n->data;
    n->data = tmp;
}



LN* copy(LN* n){
    LN* l;
    l = (LN*)malloc(sizeof(LN));
    l->data = n->data;
    l->next = NULL;
    return l;
}

void reading(LN* l, int N){
    int flag = 1;
    if(N>0){
        int id = 1;
        int t = 1;
        LN* now = l;
        system("cls");
            for (int i = 0; i < N; i++){
            printNode(now);
            now->next;
            }

            }else{

        printf("You have no one character!!!Pres any key to back to menu!!!");
        scanf("%d", &flag);
    }
}

void addLast(LN* l, LN* n){
    LN* now = l;
    while(now->next!=NULL){
        now = now->next;
    }
    now->next = copy(n);
}

void editNode(LN* l, int ID){
    LN* now = l;
    for(int i = 0; i < ID; i++){
        now = now->next;
    }
    int flag = 1, t = 0;
    while(flag == 1){
        system("cls");
        printNode(now);
        printf("What do you want to edit:\n1 - Child's name (first or second)\n2 - Child's camping shift\n3 - Child's group\n4 - Parent's name and telephone number\n5 - exit");
        scanf("%d", &t);
         switch(t){
                    case 1:
                        printf("Enter new name (second name, first name)\n");
                        scanf("%s %s", &now->data->name->second, &now->data->name->first);
                        break;
                    case 2:
                        printf("Enter new camping shift (1->4)\n");
                        scanf("%d", &now->data->shift);
                        break;
                    case 3:
                        printf("Enter new group\n");
                        scanf("%d", &now->data->group);
                        break;
                    case 4:
                        printf("Enter new parent's name (second and then first name) and then telephone number\n");
                        scanf("%s %s %s", &now->data->parent->second, &now->data->parent->first, &now->data->tp);
                    case 5:
                        flag = 0;
                        break;
                }
        }
}

int findName(LN* l, char* str, int N){
    LN* result;
    result = (LN*)malloc(sizeof(result));
    result->next = NULL;
    LN* now = l;
    LN* now2 = result;
    int count = 0, ent = 0;
    int i = 0;
    while (i < N){
        if(strstr(&now->data->name->second, str) != NULL){
            return i;
        }
    }
    return -1;
}


void findStr(LN* l, char* str, int N){
    LN* result;
    result = (LN*)malloc(sizeof(result));
    result->next = NULL;
    LN* now = l;
    LN* now2 = result;
    int count = 0, ent = 0;
    for(int i = 0; i < N; i++){
        ent = 0;
        if(strstr(&now->data->name->second, str) != NULL){
            ent = 1;
        }
        else if(strstr(&now->data->parent->second, str) != NULL){
            ent = 1;
        }
        else if(strstr(&now->data->tp, str) != NULL){
            ent = 1;
        }
        if(ent == 1){
            if(count == 0){
                result = copy(now);
            }
            else{
                addLast(result, now);
            }
            count++;
        }
        now = now->next;
    }
    system("cls");
    reading(result, count);
}


void sortName(LN* l, int N){
    LN* now  = l;
    for(int i = 0; i < N; i++){
        LN* now  = l;
        for(int j = 0; j < N - 1; j++){
            if(comperison(&now->data->name->second, &now->next->data->name->second) == 1)
            {
                swap(now, now->next);
            }
            now = now->next;
        }
    }
}

void sortParent(LN* l, int N){
    LN* now  = l;
    for(int i = 0; i < N; i++){
        LN* now  = l;
        for(int j = 0; j < N - 1; j++){
            if(comperison(&now->data->parent->second, &now->next->data->parent->second) == 2)
            {
                swap(now, now->next);
            }
            now = now->next;
        }
    }
}

void sortShift(LN* l, int N){
    LN* now  = l;
    for(int i = 0; i < N; i++){
        LN* now  = l;
        for(int j = 0; j < N-1; j++){
            if(now->data->shift > now->next->data->shift)
            {
                swap(now, now->next);
            }
            now = now->next;
        }
    }
}


void sortGroup(LN* l, int N){
    LN* now  = l;
    for(int i = 0; i < N; i++){
        LN* now  = l;
        for(int j = 0; j < N - 1; j++){
            if(now->data->group < now->next->data->group);
            {
                swap(now, now->next);
            }
            now = now->next;
        }
    }
}


void sort(LN* l, int N){
    printf("Choose:\n1 - sort by child's name\n2 - sort by parent's name\n3 - sort by shift\n4 - sort by group\n5 - back to menu\n");
    int t = 0, flag = 1;;
    while((t < 1) || (t > 5)){
        scanf("%d", &t);
        if(t < 5){
            func[t-1](l , N);
        }
    }
}


void entryintheend(LN* header, LN* node, int N){
    int t;
    LN* now = header;
    for(int i = 0; i < N-1; i++) now = now->next;
    printNode(now);
    now->next = node;
}

int menu(LN* l, int N){
    int flag = 1;
    int flag2 = 1;
    char str[50];
    printf("Tuliandin Egor. 8307\n");
    printf("You'r welcome to file cabinet of children, who will go to the camp.");
    system("pause");
    while(flag){
        system("cls");
        printf("Now you have %d children!\nWhat we should do:\n1 - read\n2 - delete one\n3 - create one\n4 - sort\n5 - search\n6 - edit one\n7 - close\n", N);
        int ch;
        int ki;
        char k[50];
        scanf("%d", &ch);
        switch(ch){
    case 1:
        reading(l, N);
        break;
    case 2:
        system("cls");
        printf("Please, write second name of child, which you want to delete:\n ");
        scanf("%s", &k);
        ki = findName(l, k, N);
        if((ki <= N)&&(ki != -1)){
            deleteNode(l, ki, N);
            N--;
        }
        break;
    case 3:
        system("cls");
        entryintheend(l, createnewNode(), N);
        N++;
        break;
    case 4:
        system("cls");
        sort(l, N);
        break;
    case 5:
        flag2 = 1;
        while(flag2>0){
            system("cls");
            printf("Please enter request: ");
            scanf("%s", &str);
            findStr(l, str, N);
            system("cls");
            printf("0 - exit to menu\nAnother one - try again\n");
            scanf("%d", &flag2);
        }
        break;
    case 6:
        system("cls");
        printf("Please enter second name of child: ");
        scanf("%d", &k);
        ki = findName(l, k, N);
        if((ki <= N)&&(ki != -1)){
            editNode(l, ki);
        }
        break;
    case 7:
        flag = 0;
        system("cls");
        printf("Thank you for using our programm!");
        break;
    default:
        system("cls");
        break;
        }
    }
    return N;
}

void reWrite(FILE* f, LN* l, int N){
    LN* now = l;
    fprintf(f, "%d\n", N);
    for(int i = 0; i< N; i++){
        fprintNode(f, now);
        now = now->next;
    }
}



int main()
{
    func[0] = sortName;
    func[1] = sortParent;
    func[2] = sortShift;
    func[3] = sortGroup;
    FILE* input;
    input = fopen("input.txt", "r");
    int N;
    fscanf(input, "%d", &N);
    LN* header;
    LN* now;
    header = getL(input);
    if(header!=NULL){
        now = header;
        for(int i = 1; i< N; i++){
            now->next = getL(input);
            now = now->next;
        }
        N = menu(header, N);
    }
    fclose(input);
    input = fopen("input.txt", "w");
    reWrite(input, header, N);
    fclose(input);
    free(header);
    free(now);
    return 0;
}

