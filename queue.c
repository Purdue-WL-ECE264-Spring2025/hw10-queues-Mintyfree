#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) 
{
    uint64_t newData = serialize(state);
    insert_at_tail(q, newData);
}

struct game_state dequeue(struct queue *q) 
{ 
    struct game_state curr_state = deserialize(q);

    return (struct game_state);
}

int number_of_moves(struct game_state start) 
{
    struct queue *q;
    uint64_t newData = serialize(start);
    q->data.head->next = new_node(newData);
    enqueue(q, start);
    struct game_state state = start;
    int rowCounter = 0;
    int colCounter = 0;
    int num = 1;

    while (q->data.head->next != NULL)
    {
        state = dequeue(q);
        if ((state.tiles[rowCounter][colCounter]) == num)
        {
            num++;
            rowCounter++;
            colCounter++;
            continue;
        }
        else
        {
        }
    }
    
    
    return state.num_steps; 
}
