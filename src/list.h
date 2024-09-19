//list.h file
//Not sure if this is structured properly either ¯\_(ツ)_/¯

//define general purpose struct for a linked list element

struct list element {
    struct list element ∗next;
    int data;
} ;

struct list element c = {NULL, 0}; //next ptr is NULL, end of list
struct list element b = {&c , 0}; //next ptr points to c
struct list element a = {&b , 0}; //next ptr points to a
struct list element ∗head = &a;

//prototypes
list_add(struct list_element *list_head, struct list_element *new_element);
list_remove(struct list_element *element);
