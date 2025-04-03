#include "queue.h"
#include "tile_game.h"

bool searchVisited(struct queue *q, struct game_state state)
{
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
    serialize(newState);

    if (!searchVisited(visited, newState)) {enqueue(q, newState);}
    newState = state;

    // Repeat for node below
    move_down(&newState);
    enqueue(visited, newState);

    if (!(searchVisited(visited, newState))) {enqueue(q, newState);}
    newState = state;

    // Repeat for node left
    move_left(&newState);
    enqueue(visited, newState);

    if (!searchVisited(visited, newState)) {enqueue(q, newState);}
    newState = state;

    // Repeat for node right
    move_right(&newState);
    enqueue(visited, newState);

    if (!searchVisited(visited, newState)) {enqueue(q, newState);}
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
    bool solved = true;   

    while (q.data.head->next != NULL)
    {
        state = dequeue(&q);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (state.tiles[i][j] == (i * 4 + j + 1)) 
                {
                    continue;
                }
                else if (state.tiles[3][3] == 0)
                {
                    continue;
                }
                else {solved = false;}
            }
        }


        if (solved == true) {break;}

        else 
        {
            struct game_state newState = state;
            // Call to put the children of the current state into the queue
            getChildren(&q, &visited, newState);

        }
    }
    
    if (state.num_steps == 0) {return state.num_steps;}

    free_list(q.data);
    free_list(visited.data);
    return state.num_steps; 
}
