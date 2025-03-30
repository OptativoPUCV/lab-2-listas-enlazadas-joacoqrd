#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *lista = (List *) malloc (sizeof(List));
    if (lista == NULL ){
        return NULL;
    }
    lista -> head = NULL;
    lista -> tail = NULL;
    lista -> current = NULL;    
     return lista;
}

void * firstList(List * list) {
    if (list == NULL || list -> head == NULL){
        return NULL;
    } 
    list -> current = list -> head;
    return list -> current -> data;
}

void * nextList(List * list) {
    if (list == NULL || list -> head == NULL || list -> current == NULL){
        return NULL;
    }
    list -> current =  list -> current -> next; 
    if (list -> current == NULL){
        return NULL;
    }
    return list -> current -> data;
}

void * lastList(List * list) {
    if (list == NULL || list -> head == NULL || list -> current == NULL){
        return NULL;
    }
    while (list -> current -> next != NULL){
        list -> current = list -> current -> next;
    }
    return list -> current -> data;
}

void * prevList(List * list) {
    if (list == NULL || list -> head == NULL || list -> current == NULL){
        return NULL;
    }
    if (list -> current -> prev == NULL){
        return NULL;
    }
    list -> current = list -> current -> prev;
    if (list -> current == NULL){
        return NULL;
    }
    return list -> current -> data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;
    Node *nodo = createNode (data);
    if (list -> head == NULL){
        list -> head = nodo;
        list -> tail = nodo;
    }
    else{
        nodo -> next = list -> head;
        list -> head -> prev = nodo;
        list -> head = nodo;
    }
    return;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL) return;

    Node *nodo = createNode (data);

    if (list -> head == NULL){
        list -> head = nodo;
        list -> tail = nodo; 
        return;
    }
    if (list -> current == NULL) return;
    if (list -> current -> next != NULL){
        nodo -> next = list -> current -> next;
        nodo -> prev = list -> current;
        list -> current -> next -> prev = nodo;
        list -> current -> next = nodo;
    }
    else{
        list -> current -> next = nodo;
        nodo -> prev = list -> current ;
        list -> tail = nodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list -> current == NULL) return NULL;
    Node *nodo = list -> current;
    void *dato = nodo -> data;
    
    if (nodo -> prev != NULL){
        nodo -> prev -> next = nodo -> prev;
    }
    else{
        list -> head = nodo -> next;
    }

    if (nodo -> next != NULL){
        nodo -> next -> prev = nodo -> next;
    }
    else{
        list -> tail = nodo -> prev;
    }

    if (list -> head == NULL ){
        list -> tail = NULL;
    }

    free (nodo);

    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}