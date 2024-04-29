#include "header.h"

List* create_list(){
    List* li = (List*) malloc(sizeof(List));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

int insert_list_ordered(List* li, Node data){
    if(li == NULL){
        return ERROR;
    }

    Elem *no = (Elem*) malloc(sizeof(Elem));
    
    no->node = data;
    if((*li) == NULL){ //lista vazia: insere início
        no->next = NULL;
        *li = no;
        return OK;
    }

    else{
        Elem *before, *now = *li;
        while((now != NULL) && (now->node.ef < data.ef)){
            before = now;
            now = now->next;
        }
        
        if(now == *li){ //insere início
            no->next = (*li);
            *li = no;
        }
        
        else{
            no->next = now;
            before->next = no;
        }
        return OK;
    }
}

int remove_list_ini(List* li){
    if(li == NULL){
        return ERROR;
    }

    if(*li == NULL){
        return ERROR;
    }

    Elem* no = *li;
    no = no->next;
    *li = no;

    return OK;
}

void release_list(List* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->next;
            free(no);
        }
        free(li);
    }
}

int insert_list_end(List* li, Node data){
    if(li == NULL){
        return ERROR;
    }

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL){
        return ERROR;
    }

    no->node = data;
    if((*li) == NULL){ //lista vazia: insere início
        no->next = NULL;
        *li = no;
        return OK;
    }

    else{
        Elem *before, *now = *li;
        while(now != NULL){
            before = now;
            now = now->next;
        }
        no->next = now;
        before->next = no;
        return OK;
    }
}



Way* create_way_list(){
    Way* wa = (Way*) malloc(sizeof(Way));
    if(wa != NULL){
        *wa = NULL;
    }
    return wa;
}

int insert_way_list_end(Way* li, char direc){
    if(li == NULL){
        return ERROR;
    }

    WaySt *no;
    no = (WaySt*) malloc(sizeof(WaySt));
    if(no == NULL){
        return ERROR;
    }

    no->direction = direc;
    no->next = NULL;
    if((*li) == NULL){ //lista vazia: insere início
        *li = no;
    }
    
    else{
        WaySt *aux;
        aux = *li;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = no;
    }
    return OK;
}

void imprime_way_list(Way* li){
    if ((li == NULL) || (*li) == NULL){
        return;
    }
    
    WaySt* no = *li;
    printf("Movimentos: ");
    while (no->next != NULL){
        printf("%d ", no->direction);
        no = no->next;
    }
    printf("%d\n", no->direction);
}

Way* clone_way_list_end(Way* li2, int new_direc){
    Way* li = create_way_list();
    if((li2 == NULL) || ((*li2) == NULL) || (li == NULL)){
        return ERROR;
    }

    WaySt *no = *li2;
    while(no != NULL){
        insert_way_list_end(li, (no->direction));
        no = no->next;
    }
    
    insert_way_list_end(li, new_direc);

    imprime_way_list(li);
    
    return li;
}

void release_way_list(Way* li){
    if(li != NULL){
        WaySt* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->next;
            free(no);
        }
        free(li);
    }
}