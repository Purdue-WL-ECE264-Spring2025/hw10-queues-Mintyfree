#include "queue.h"
#include "tile_game.h"

bool searchVisited(struct queue *q, struct game_state state)
{
    state.num_steps = 0;
    uint64_t checkData = serialize(state);

    struct list_node *delNode = q->data.head;
    while(delNode != NULL)
    {
        if (delNode->value == checkData) {return true;}
        delNode = delNode->next;
    }
    return false;
}

void getChildren(struct queue *q, struct queue *visited, struct game_state state)
{
    struct game_state newState = state;

    // Check if the node above has been searched, if not enqueue it
    move_up(&newState);

    if (!searchVisited(visited, newState)) 
    {
        enqueue(q, newState);
        newState.num_steps = 0;
        enqueue(visited, newState);
    }
    newState = state;

    // Repeat for node below
    move_down(&newState);

    if (!searchVisited(visited, newState)) 
    {
        enqueue(q, newState);
        newState.num_steps = 0;
        enqueue(visited, newState);
    }    
    newState = state;

    // Repeat for node left
    move_left(&newState);

    if (!searchVisited(visited, newState)) 
    {
        enqueue(q, newState);
        newState.num_steps = 0;
        enqueue(visited, newState);
    }    
    newState = state;

    // Repeat for node right
    move_right(&newState);

    if (!searchVisited(visited, newState)) 
    {
        enqueue(q, newState);
        newState.num_steps = 0;
        enqueue(visited, newState);
    }
}

void enqueue(struct queue *q, struct game_state state) 
{
    uint64_t newData = serialize(state);
    insert_at_tail(&q->data, newData);
}

struct game_state dequeue(struct queue *q) 
{ 
    struct game_state state = deserialize(q->data.head->value);
    struct game_state curr_state = state;


    remove_from_head(&q->data);
    return (curr_state);
}

int number_of_moves(struct game_state start) 
{
    // Initialization
    struct queue q = {0};
    struct queue visited = {0};

    q.data.head = NULL;
    visited.data.head = NULL;

    enqueue(&q, start);
    enqueue(&visited, start);


    struct game_state state = start;
    
    // Create the final game state 
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    while (q.data.head != NULL)
    {
        state = dequeue(&q);
        bool solved = true;
        counter1 = 0;
        counter2 = 0;
        counter3 = 0;
        while (counter3 < 15)
        {
            if((state.tiles[counter1 / 4][counter2 % 4]) != counter3 + 1) {solved = false;}
            counter1++;
            counter2++;
            counter3++;
        }


        if (solved == true) {break;}

        else 
        {
            // Call to put the children of the current state into the queue
            getChildren(&q, &visited, state);
        }
    }
    


    free_list(q.data);
    free_list(visited.data);
    return state.num_steps; 
}
