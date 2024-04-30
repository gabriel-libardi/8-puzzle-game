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
        Elem *before = NULL, *now = *li;
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

void removeNode(Elem* no){
    no->node.ef = 0;
    no->node.hn = 0;
    //free_matrix(&(no->node.matrix));
    //free(no->node.wa);
}

int remove_list_ini(List* li){
    if(li == NULL){
        return ERROR;
    }

    if(*li == NULL){
        return ERROR;
    }

    Elem* no = *li;
    //removeNode(no);
    *li = no->next;
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