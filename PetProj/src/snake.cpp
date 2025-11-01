#include "/workspaces/C++/PetProj/include/snake.h/"
#include <iostream>
#include <vector>


Snake::Snake(int start_x, int start_y, int initial_length = 3){
    direction = 1;
    alive = true;

    for (int i = 0; i < initial_length; i++){
        body.push_back({start_x - i, start_y});
    }
}