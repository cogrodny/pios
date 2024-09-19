//list.c file
// Tried my best, couldn't figure it out due to lack of time and just honest bad time management. Will do better next time. ¯\_(ツ)_/¯

#include <stdlib.h>
#include "list.h"

void list_add(struct list_element *list_head, struct list_element *new_element) { //this may be right though I don't know for sure
    new_element->next = list_head->next;
    list_head->next = new_element;
}

void list_remove(struct list_element *element) { //most likely wrong tried to find answer but could not

    struct list_element *current = element;

    while (current->next != element) {
	    current = current->next;
    }
    current->next = element->next;

}
