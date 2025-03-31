#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) 
{

}

struct game_state dequeue(struct queue *q) 
{ 
    
    return (struct game_state){0}; 
}

int number_of_moves(struct game_state start) 
{
    struct queue *q;
    uint64_t newData = serialize(start);
    q->data.head->next = new_node(newData);
    enqueue(q, start);
    struct game_state state = start;
    int num = 1;

    while (q->data.head->next != NULL)
    {
        state = dequeue(q);
        if ((state.tiles[num]) == num)
        {
            num++;
            continue;
        }
        else
        {
            for ()
        }
    }
    
    
    return state.num_steps; 
}
