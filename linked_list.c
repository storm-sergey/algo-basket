#include <stdlib.h>
#include <stdio.h>

// TODO: I have a trouble with freeing memo when I use rm_list()...

typedef struct __Linked_list_item {
    int value;
    struct __Linked_list_item *next, *prev;
} __item;

typedef struct Meta_linked_list {
    int amount, current_index, err;
    __item *first, *last, *current, *buff;
} list;

list* create_linked_list()
{
    list *meta = (list*) malloc(sizeof(list));
    meta->amount = 0;
    meta->first = NULL;
    meta->last = NULL;
    meta->current = NULL;
    meta->buff = NULL;
    meta->current_index = -1;
    meta->err = 0;
    return meta;
}

int error(list *meta)
{
    if (meta->err != 0) {
        printf("linked_list throw exception");
        return 1;
    } else {
        return 0;
    }
}

void add_first(list *meta, int value)
{
    __item *new_item = (__item*) malloc(sizeof(__item));
    new_item->value = value;
    new_item->prev = NULL;
    new_item->next = meta->first;
    if (meta->first != NULL) meta->first->prev = new_item;
    meta->first = new_item;
    meta->current = new_item;
    if (meta->amount == 0) meta->last = new_item;
    meta->current_index = 0;
    meta->amount++;
}

void add_last(list *meta, int value)
{
    __item *new_item = (__item*) malloc(sizeof(__item));
    new_item->value = value;
    new_item->next = NULL;
    new_item->prev = meta->last;
    if (meta->last != NULL) meta->last->next = new_item;
    meta->last = new_item;
    meta->current = new_item;
    if (meta->amount == 0) meta->first = new_item;
    meta->current_index = meta->amount;
    meta->amount++;
}

void take_the_position(list *meta, int index)
{
    if (index < 0 || index > meta->amount - 1) {
        printf("take_the_position(): ");
        printf("the index is out of the linked list scope\n");
        return;
    }
    if (meta->amount == 0 || meta->current_index == index) return;
    // looking for the nearest valid index
    const int FORWARD = 1;
    const int BACKWARD = -1;
    int i, step_dir, to_first, to_curr, to_last;
    to_first = index;
    to_curr = abs(index - meta->current_index);
    to_last = abs(index - (meta->amount - 1));
    if (to_curr <= to_first && to_curr <= to_last) {
        i = meta->current_index;
        step_dir = (index - meta->current_index) > 0 ?
            FORWARD : BACKWARD;
    } else if (to_first <= to_last && to_first <= to_curr) {
        i = 0;
        step_dir = FORWARD;
        meta->current = meta->first;
    } else if (to_last <= to_first && to_last <= to_curr) {
        i = meta->amount - 1;
        step_dir = BACKWARD;
        meta->current = meta->last;
    } else {
        meta->err = 1;
        printf("Searching the nearest valid index in the meta is failed\n");
        printf("index = %d;\n", index);
        printf("list:\n  last_index = %d;\n", meta->amount - 1);
        printf("  current_index = %d;\n", meta->current_index);
        i = 0;
        step_dir = FORWARD;
        meta->current = meta->first;
    }
    // coming to the looked for linked list item
    while (i != index) {
        if (step_dir == FORWARD) {
            meta->current = meta->current->next;
        }
        if (step_dir == BACKWARD) {
            meta->current = meta->current->prev;
        }
        i += step_dir;
    }
    meta->current_index = index;
}

void insert(list *meta, int index, int value)
{
    if (index < 0 || index > meta->amount) {
        meta->err = 1;
        printf("insert(): the index is out of the linked list scope\n");
        return;
    }
    if (index == 0) {
        add_first(meta, value);
    } else if (index == meta->amount) {
        add_last(meta, value);
    } else {
        take_the_position(meta, index);
        // creating a new __item
        __item *new_item = (__item*) malloc(sizeof(__item));
        new_item->value = value;
        // linking the previous __item and the new one
        meta->current->prev->next = new_item;
        new_item->prev = meta->current->prev;
        // linking the new __item and the next one
        new_item->next = meta->current;
        meta->current->prev = new_item;
        // saving meta
        meta->current = new_item;
        meta->amount++;
    }
}

int get_item(list *meta, int index)
{
    if (index < 0 || index > meta->amount) {
        meta->err = 1;
        printf("get_item(): the index is out of the linked list scope\n");
        return 0;
    }
    take_the_position(meta, index);
    return meta->current->value;
}

int have_next(list *meta)
{
    if (meta->current != NULL) {
        return (meta->current->next != NULL ? 1 : 0);
    }
    return 0;
}

int have_prev(list *meta)
{
    if (meta->current != NULL) {
        return (meta->current->prev != NULL ? 1 : 0);
    }
    return 0;
}

int get_next(list *meta)
{
    if (have_next(meta)) {
        meta->current = meta->current->next;
        meta->current_index++;
        return meta->current->value;
    }
    meta->err = 1;
    printf("get_next(): the current item has no next\n");
    return 0;
}

int get_prev(list *meta)
{
    if (have_prev(meta)) {
        meta->current = meta->current->prev;
        meta->current_index--;
        return meta->current->value;
    }
    meta->err = 1;
    printf("get_prev(): the current item has no prev\n");
    return 0;
}

int get_first(list *meta)
{
    if (meta->first != NULL) {
        meta->current = meta->first;
        meta->current_index = 0;
        return meta->current->value;
    }
    meta->err = 1;
    printf("get_first(): list is empty\n");
    return 0;
}

int get_last(list *meta)
{
    if (meta->last != NULL) {
        meta->current = meta->last;
        meta->current_index = meta->amount - 1;
        return meta->current->value;
    }
    meta->err = 1;
    printf("get_last(): list is empty\n");
    return 0;
}

void rm_first(list *meta)
{
    if (meta->first != NULL) {
        meta->current = meta->first;
        meta->current_index = 0;
        if (have_next(meta)) {
            meta->current = meta->current->next;
            meta->current->prev = NULL;
            free(meta->first);
            meta->first = meta->current;
        } else {
            free(meta->first);
            meta->first = NULL;
            meta->current = NULL;
            meta->last = NULL;
            meta->current_index = -1;
        }
        meta->amount--;
    } else {
        meta->err = 1;
        printf("rm_first(): the linked list has no elements\n");
    }
}

void rm_last(list *meta)
{
    if (meta->last != NULL) {
        meta->current = meta->last;
        meta->current_index = meta->amount - 1;
        if (have_prev(meta)) {
            meta->current = meta->current->prev;
            meta->current->next = NULL;
            free(meta->last);
            meta->last = meta->current;
        } else {
            free(meta->last);
            meta->first = NULL;
            meta->current = NULL;
            meta->last = NULL;
            meta->current_index = -1;
        }
        meta->amount--;
    } else {
        meta->err = 1;
        printf("rm_last(): the linked list has no elements\n");
    }
}

void rm_item(list *meta, int index)
{
    if (index < 0 || index > meta->amount - 1) {
        meta->err = 1;
        printf("rm_item(): ");
        printf("the index is out of the linked list scope\n");
        return;
    }
    if (index == 0) {
        rm_first(meta);
    } else if (index == meta->amount - 1) {
        rm_last(meta);
    } else {
        take_the_position(meta, index);
        meta->current->next->prev = meta->current->prev;
        meta->current->prev->next = meta->current->next;
        meta->buff = meta->current->next;
        free(meta->current);
        meta->current = meta->buff;
        meta->buff = NULL;
        meta->amount--;
    }
}

void rm_list(list *meta)
{
    if (meta->first != NULL) {
        while(have_next(meta)) {
            meta->buff = meta->current->next;
            free(meta->current);
            meta->current = meta->buff;
        }
        free(meta->current);
    }
    free(meta);
}

void print_list(list *meta)
{
    if (meta->first != NULL) { 
        printf("linked list values: [%d", get_first(meta));
        while(have_next(meta)) {
            printf(", %d", get_next(meta));
        }
        printf("]\n");
    } else {
        meta->err = 1;
    }
}

// test
int main()
{
    list *linked_list = create_linked_list();
    for (int i = 2; i < 5; i++) {
        add_first(linked_list, i);
        add_last(linked_list, i);
    }
    print_list(linked_list);
    printf("----------------\n");
    insert(linked_list, 4, 1);
    print_list(linked_list);
    insert(linked_list, 0, 1);
    print_list(linked_list);
    insert(linked_list, 8, 1);
    print_list(linked_list);
    printf("----------------\n");
    insert(linked_list, 11, 0);
    insert(linked_list, -1, 0);
    printf("----------------\n");
    printf("get_item(linked_list, 5) return: %d\n", get_item(linked_list, 5));
    printf("get_last() return: %d\n", get_last(linked_list));
    printf("get_prev() return: %d\n", get_prev(linked_list));
    printf("get_first() return: %d\n", get_first(linked_list));
    printf("get_next() return: %d\n", get_next(linked_list));
    printf("----------------\n");
    get_item(linked_list, -1);
    get_item(linked_list, 100);
    get_first(linked_list);
    get_prev(linked_list);
    get_last(linked_list);
    get_next(linked_list);
    printf("----------------\n");
    rm_first(linked_list);
    rm_last(linked_list);
    rm_item(linked_list, 4);
    rm_item(linked_list, -1);
    print_list(linked_list);
    printf("----------------\n");
    printf("err: %d\n", error(linked_list));
    rm_list(linked_list);
    print_list(linked_list);
    printf("----------------\n");
    return 0;
}

