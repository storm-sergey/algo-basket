#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Stack
{
    int size, i;
    int *_stack;
} stack;

stack init_stack_char(char*);
stack init_stack_int(int);
void freestack(stack*);
void push(stack*, int);
int is_empty(stack*);
int pop(stack*);

// overloading
#define init_stack(size)     \
    _Generic((size),         \
    char*: init_stack_char,  \
    int: init_stack_int,     \
    default: init_stack_char \
    )(size)

int main(int argc, char *argv[])
{
    // init
    stack s = init_stack(argv[1]);

    // filling the stack
    printf("push nums to stack:\n");
    for (int i = 0; i < atoi(argv[1]); i++)
    {
        printf("%d\n", i);
        push(&s, i);
    }
    printf("\n");

    // printing the stack
    printf("pop all from stack:\n");
    while(!is_empty(&s)) printf("%d\n", pop(&s));
    
    // releasing
    freestack(&s);
    return 0;
}


stack init_stack_int(int size)
{
    stack s;   
    s.size = size;
    s.i = -1;
    s._stack = (int*) malloc(s.size * sizeof(int));
    return s;
}

stack init_stack_char(char *size)
{
    return init_stack(atoi(size));
}

void freestack(stack *this)
{
    free(this->_stack);
}

void push(stack *this, int x)
{
    if (this->i < (this->size))
    {
        (this->i)++;
        this->_stack[this->i] = x;
    }
    else
    {
        printf("%d size stack is full\n", this->size);
    }
}

int is_empty(stack *this)
{
    if(this->i < 0) return 1;
    else return 0;
}

int pop(stack *this)
{
    if (!is_empty(this))
    {
        return this->_stack[(this->i)--];
    }
    else
    {   
        printf("%d size stack is empty\n", this->size);
        return 0;
    }
}

