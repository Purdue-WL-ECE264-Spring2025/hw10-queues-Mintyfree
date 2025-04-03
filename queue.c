#include "queue.h"
#include "tile_game.h"

void getChildren(struct queue *q, struct game_state state)
{

}

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
    struct queue *q;
    struct queue *visted;


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
            if (*(*(state.tiles + i) + counter % 4) != i + 1) {counter++; continue;}

            else {solved = true;}
        }


        if (solved == true) {break;}

        else 
        {
            struct game_state newState = state;

            // Grouping of trying to move to find the child nodes 
            // Reset and try to go the other directions
            struct list_node searchNode;
            uint64_t searchSerial;

            move_up(&newState);
            serialize(newState);
            enqueue(visted, newState);
            enqueue(q, newState);
            newState = state;

            move_down(&newState);
            enqueue(visted, newState);
            enqueue(q, newState);
            newState = state;

            move_left(&newState);
            enqueue(visted, newState);
            enqueue(q, newState);
            newState = state;

            move_right(&newState);
            enqueue(visted, newState);
            enqueue(q, newState);
            newState = state;
        }
    }
    
    free_list(q->data);
    free_list(visted->data);
    return state.num_steps; 
}
