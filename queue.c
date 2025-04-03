#include "queue.h"
#include "tile_game.h"

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
    struct queue *q = NULL;
    struct queue *visted = NULL;

    uint64_t newData = serialize(start);
    insert_at_head(&q->data, newData);
    insert_at_head(&visted->data, newData);
    enqueue(q, start);


    struct game_state state = start;
    
    // Create the final game state 
    bool solved = false;   

    while (q->data.head->next != NULL)
    {
        state = dequeue(q);

        int counter = 0; 
        for (int i = 0; i < 16; i++)
        {
            if (*(*(state.tiles + i) + counter % 4) != i + 1) {continue;}

            else {solved = true;}
        }


        if (solved == true) {break;}

        else 
        {
            struct game_state newUp = state;
            struct game_state newDown = state;
            struct game_state newLeft = state;
            struct game_state newRight = state;

            for (int i = 0; i < 4; i++)
            {
                move_up(&newUp);
                move_down(&newDown);
                move_right(&newLeft);
                move_left(&newRight);

                enqueue(visted, newUp);
                enqueue(visted, newDown);
                enqueue(visted, newLeft);
                enqueue(visted, newRight);

                enqueue(q, newUp);
                enqueue(q, newDown);
                enqueue(q, newLeft);
                enqueue(q, newRight);
            }
        }
    }
    
    free_list(q->data);
    free_list(visted->data);
    return state.num_steps; 
}
