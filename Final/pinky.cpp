#include "pinky.h"
#include "character.h"


Pinky::Pinky(int x, int y, QLabel *character, QGraphicsItem *parent) : Character(x, y, character, parent)
{
    //Start countdown for first created
    start = 244;

    animate = new QMovie("./res/pinky_left.gif");
    character->setMovie(animate);
    animate->setScaledSize(QSize(50, 50));
    animate -> start();
}

//Change the GIF picture according to the direction pacman moves.
void Pinky::pic_change(){

    //Stop the QMovie
    animate->stop();

    //Default picture
    animate -> setFileName("./res/pinky_left.gif");

    //Change the GIF file
    if(direction == X_NEGATIVE)
        animate -> setFileName("./res/pinky_left.gif");
    else if(direction == X_POSITIVE)
        animate -> setFileName("./res/pinky_right.gif");
    //frightened mode
    if(scared > 0)
        animate -> setFileName("./res/ghost_scared.gif");
    //reviving mode
    if(revive > 81)
        animate -> setFileName("./res/ghost_revive.gif");

    //Restart the QMovie
    animate->start();
}

bool Pinky::move(Character* pacman){

    //If through the map
    if(x >= 744) x -= 759;
    if(x <= -15) x += 759;

    //Animation before start to chase
    if(start != -1){
        if(start == 244){
            start--; return false;
        }
        else if(start > 203 && start <= 243){
            x--; start--; direction = X_NEGATIVE; pic_change(); return true;
        }
        else if(start > 122 && start <= 203){
            x++; start--; direction = X_POSITIVE; pic_change(); return true;
        }
        else if(start > 81 && start <= 122){
            x--; start--; direction = X_NEGATIVE; pic_change(); return true;
        }
        else if(start > 0 && start <= 81){
            y--; start--; return true;
        }
        else if(start == 0){
            start --; direction = X_NEGATIVE; pic_change();
        }
    }

    //Animation for reviving
    if(revive != -1){
        if(revive == 381){
            x = UNIT_DISTANCE*13+13; y = UNIT_DISTANCE*14; pic_change();
            revive--; scared = 0; return false;
        }
        else if(revive > 81 &&revive < 381){ revive--; return false;}
        else if(revive > 0 && revive <= 81){ revive--; y--; pic_change(); return true;}
        else if(revive == 0){ revive--; direction = X_NEGATIVE;}
    }

    //Count down for frightening
    if(scared > 0) scared--;

    //Change pic according to its direction and state
    pic_change();

    //(If scared, recheck for new direction)

    //If its stucking somewhere, try another way
    if(take_another_way && scared != 350){
        take_another_way = false;
        if(direction == X_POSITIVE){ x++; return true;}
        else if(direction == X_NEGATIVE){ x--; return true;}
        else if(direction == Y_POSITIVE){ y++; return true;}
        else if(direction == Y_NEGATIVE){ y--; return true;}
    }

    //If couldn't change direction, keep moving
    if(!direction_controlled('A', pacman) && scared != 350){
        if(direction == X_POSITIVE){ x++; return true;}
        else if(direction == X_NEGATIVE){ x--; return true;}
        else if(direction == Y_POSITIVE){ y++; return true;}
        else if(direction == Y_NEGATIVE){ y--; return true;}
    }

    //If frightening, reverse the order to chase, became escape
    if(scared > 0){
        int buffer_1, buffer_2;
        buffer_1 = order[0];
        buffer_2 = order[1];
        order[0] = order[3];
        order[1] = order[2];
        order[2] = buffer_2;
        order[3] = buffer_1;
    }

    //Try the four directions by order
    for(int i = 0; i < 4; i++){

        direction = order[i];
        pic_change();

        //If two direction to be closer to pacman are not availible, try another way.
        if(i == 2) take_another_way = true;

        //Check if the direction is availible ( boundary condition )
        if(direction == X_NEGATIVE){
            if(y == UNIT_DISTANCE*1){
                if(x != UNIT_DISTANCE*1 && x != UNIT_DISTANCE*15){ x--; return true;}
            }
            else if(y == UNIT_DISTANCE*5){
                if(x != UNIT_DISTANCE*1){ x--; return true;}
            }
            else if(y == UNIT_DISTANCE*8){
                if(x != UNIT_DISTANCE*1 && x != UNIT_DISTANCE*9 && x != UNIT_DISTANCE*15 && x != UNIT_DISTANCE*21){
                    x--; return true;
                }
            }
            else if(y == UNIT_DISTANCE*11){
                if(x != UNIT_DISTANCE*6 && x != UNIT_DISTANCE*9 && x != UNIT_DISTANCE*21){ x--; return true;}
            }
            else if(y == UNIT_DISTANCE*14){
                if(x != UNIT_DISTANCE*18){ x--; return true;}
            }
            else if(y ==UNIT_DISTANCE*17){
                if(x != UNIT_DISTANCE*6 && x != UNIT_DISTANCE*9 && x!= UNIT_DISTANCE*21){ x--; return true;}
            }
            else if(y == UNIT_DISTANCE*20){
                if(x != UNIT_DISTANCE*1 && x != UNIT_DISTANCE*15){ x--; return true;}
            }
            else if(y == UNIT_DISTANCE*23){
                if(x != UNIT_DISTANCE*1 && x != UNIT_DISTANCE*6 && x != UNIT_DISTANCE*24){ x--; return true;}
            }
            else if(y == UNIT_DISTANCE*26){
                if(x != UNIT_DISTANCE*1 && x != UNIT_DISTANCE*9 && x != UNIT_DISTANCE*15 && x != UNIT_DISTANCE*21){
                    x--; return true;
                }
            }
            else if(y == UNIT_DISTANCE*29){
                if(x != UNIT_DISTANCE*1){ x--; return true;}
            }
        }
        else if(direction == X_POSITIVE){
            if(y == UNIT_DISTANCE*1){
                if(x != UNIT_DISTANCE*12 && x != UNIT_DISTANCE*26){ x++; return true;}
            }
            else if(y == UNIT_DISTANCE*5){
                if(x != UNIT_DISTANCE*26){ x++; return true;}
            }
            else if(y == UNIT_DISTANCE*8){
                if(x != UNIT_DISTANCE*6 && x != UNIT_DISTANCE*12 && x != UNIT_DISTANCE*18 && x != UNIT_DISTANCE*26){
                    x++; return true;
                }
            }
            else if(y == UNIT_DISTANCE*11){
                if(x != UNIT_DISTANCE*6 && x != UNIT_DISTANCE*18 && x != UNIT_DISTANCE*21){ x++; return true;}
            }
            else if(y == UNIT_DISTANCE*14){
                if(x != UNIT_DISTANCE*9){ x++; return true;}
            }
            else if(y ==UNIT_DISTANCE*17){
                if(x != UNIT_DISTANCE*6 && x != UNIT_DISTANCE*18 && x!= UNIT_DISTANCE*21){ x++; return true;}
            }
            else if(y == UNIT_DISTANCE*20){
                if(x != UNIT_DISTANCE*12 && x != UNIT_DISTANCE*26){ x++; return true;}
            }
            else if(y == UNIT_DISTANCE*23){
                if(x != UNIT_DISTANCE*3 && x != UNIT_DISTANCE*21 && x != UNIT_DISTANCE*26){ x++; return true;}
            }
            else if(y == UNIT_DISTANCE*26){
                if(x != UNIT_DISTANCE*6 && x != UNIT_DISTANCE*12 && x != UNIT_DISTANCE*18 && x != UNIT_DISTANCE*26){
                    x++; return true;
                }
            }
            else if(y == UNIT_DISTANCE*29){
                if(x != UNIT_DISTANCE*26){ x++; return true;}
            }
        }
        else if(direction == Y_NEGATIVE){
            if(x == UNIT_DISTANCE*1 || x == UNIT_DISTANCE*26){
                if(y != UNIT_DISTANCE*1 && y != UNIT_DISTANCE*14 && y != UNIT_DISTANCE*20 && y != UNIT_DISTANCE*26){
                    y--; return true;
                }
            }
            else if(x == UNIT_DISTANCE*3 || x == UNIT_DISTANCE*24){
                if(y != UNIT_DISTANCE*1 && y != UNIT_DISTANCE*5 && y!= UNIT_DISTANCE*8 && y != UNIT_DISTANCE*14 && y != UNIT_DISTANCE*20 && y != UNIT_DISTANCE*23 && y != UNIT_DISTANCE*29){
                    y--; return true;
                }
            }
            else if(x == UNIT_DISTANCE*6 || x == UNIT_DISTANCE*21){
                if(y != UNIT_DISTANCE*1 && y != UNIT_DISTANCE*29){ y--; return true;}
            }
            else if(x == UNIT_DISTANCE*9 || x == UNIT_DISTANCE*18){
                if(y != UNIT_DISTANCE*1 && y != UNIT_DISTANCE*5 && y != UNIT_DISTANCE*11 && y != UNIT_DISTANCE*23 && y != UNIT_DISTANCE*29){
                    y--; return true;
                }
            }
            else if(x == UNIT_DISTANCE*12 || x == UNIT_DISTANCE*15){
                if(y != UNIT_DISTANCE*1 && y != UNIT_DISTANCE*8 && y != UNIT_DISTANCE*17 && y != UNIT_DISTANCE*20 && y != UNIT_DISTANCE*26){
                    y--; return true;
                }
            }
        }
        else if(direction == Y_POSITIVE){
            if(x == UNIT_DISTANCE*1 || x == UNIT_DISTANCE*26){
                if(y != UNIT_DISTANCE*8 && y != UNIT_DISTANCE*14 && y != UNIT_DISTANCE*23 && y != UNIT_DISTANCE*29){
                    y++; return true;
                }
            }
            else if(x == UNIT_DISTANCE*3 || x == UNIT_DISTANCE*24){
                if(y != UNIT_DISTANCE*1 && y != UNIT_DISTANCE*5 && y!= UNIT_DISTANCE*8 && y != UNIT_DISTANCE*14 && y != UNIT_DISTANCE*20 && y != UNIT_DISTANCE*26 && y != UNIT_DISTANCE*29){
                    y++; return true;
                }
            }
            else if(x == UNIT_DISTANCE*6 || x == UNIT_DISTANCE*21){
                if(y != UNIT_DISTANCE*26 && y != UNIT_DISTANCE*29){ y++; return true;}
            }
            else if(x == UNIT_DISTANCE*9 || x == UNIT_DISTANCE*18){
                if(y != UNIT_DISTANCE*1 && y != UNIT_DISTANCE*8 && y != UNIT_DISTANCE*20 && y != UNIT_DISTANCE*26 && y != UNIT_DISTANCE*29){
                    y++; return true;
                }
            }
            else if(x == UNIT_DISTANCE*12 || x == UNIT_DISTANCE*15){
                if(y != UNIT_DISTANCE*5 && y != UNIT_DISTANCE*11 && y != UNIT_DISTANCE*17 && y != UNIT_DISTANCE*23 && y != UNIT_DISTANCE*29){
                    y++; return true;
                }
            }
        }
    }

    return false;
}


//Change the direction of the pacman with buttons.
bool Pinky::direction_controlled(QChar _key, Character* pacman, Character* ghost){

    //Variable to decide if we need to change its direction
    bool check = false;

    //If it's at a corner, we should check for its new direction
    if(x == UNIT_DISTANCE*1 || x==UNIT_DISTANCE*26){
        if(y == UNIT_DISTANCE*1 || y == UNIT_DISTANCE*5 || y == UNIT_DISTANCE*8 || y == UNIT_DISTANCE*20 || y == UNIT_DISTANCE*23 || y == UNIT_DISTANCE*26 || y == UNIT_DISTANCE*29){
            check = true;
        }
    }
    else if(x == UNIT_DISTANCE*3 || x==UNIT_DISTANCE*24){
        if(y == UNIT_DISTANCE*23 || y == UNIT_DISTANCE*26){
            check = true;
        }
    }
    else if(x == UNIT_DISTANCE*6 || x==UNIT_DISTANCE*21){
        if(y == UNIT_DISTANCE*1 || y == UNIT_DISTANCE*5 || y == UNIT_DISTANCE*8 || y == UNIT_DISTANCE*14  || y == UNIT_DISTANCE*20 || y == UNIT_DISTANCE*23 || y == UNIT_DISTANCE*26){
            check = true;
        }
    }
    else if(x == UNIT_DISTANCE*9 || x==UNIT_DISTANCE*18){
        if(y == UNIT_DISTANCE*5 || y == UNIT_DISTANCE*8 || y == UNIT_DISTANCE*11 || y == UNIT_DISTANCE*14 || y == UNIT_DISTANCE*17 || y == UNIT_DISTANCE*20 || y == UNIT_DISTANCE*23 || y == UNIT_DISTANCE*26){
            check = true;
        }
    }
    else if(x == UNIT_DISTANCE*12 || x==UNIT_DISTANCE*15){
        if(y == UNIT_DISTANCE*1 || y == UNIT_DISTANCE*5 || y == UNIT_DISTANCE*8 || y == UNIT_DISTANCE*11 || y == UNIT_DISTANCE*20 || y == UNIT_DISTANCE*23 || y == UNIT_DISTANCE*26 || y == UNIT_DISTANCE*29){
            check = true;
        }
    }

    //If not, return.
    if(check == false) return false;

    //For pinky, it chase the point which is 3 times of unit_distance in front of the pacman.
    int x_distance, y_distance;
    int goal_x = pacman->x;
    int goal_y = pacman->y;

    if(pacman->direction == X_POSITIVE){
        goal_x += UNIT_DISTANCE*3;
    }
    else if(pacman->direction == X_NEGATIVE){
        goal_x -= UNIT_DISTANCE*3;
    }
    else if(pacman->direction == Y_POSITIVE){
        goal_y += UNIT_DISTANCE*3;
    }
    else if(pacman->direction == Y_NEGATIVE){
        goal_y -= UNIT_DISTANCE*3;
    }

    if(goal_x > x) x_distance = goal_x - x;
    else x_distance = x - goal_x;
    if(goal_y > y) y_distance = goal_y - y;
    else y_distance = y - goal_y;

    if(y_distance == 0){
        if(x > goal_x) order[0] = X_NEGATIVE;
        else order[0] = X_POSITIVE;
        if(y > goal_y) order[1] = Y_NEGATIVE;
        else order[1] = Y_POSITIVE;
        if(order[1] == Y_NEGATIVE) order[2] = Y_POSITIVE;
        else order[2] = Y_NEGATIVE;
        if(order[0] == X_NEGATIVE) order[3] = X_POSITIVE;
        else order[3] = X_NEGATIVE;
    }
    else if(x_distance == 0){
        if(y > goal_y) order[0] = Y_NEGATIVE;
        else order[0] = Y_POSITIVE;
        if(x > goal_x) order[1] = X_NEGATIVE;
        else order[1] = X_POSITIVE;
        if(order[1] == X_NEGATIVE) order[2] = X_POSITIVE;
        else order[2] = X_NEGATIVE;
        if(order[0] == Y_NEGATIVE) order[3] = Y_POSITIVE;
        else order[3] = Y_NEGATIVE;
    }
    else if(x_distance > y_distance){
        if(x > goal_x) order[0] = X_NEGATIVE;
        else order[0] = X_POSITIVE;
        if(y > goal_y) order[1] = Y_NEGATIVE;
        else order[1] = Y_POSITIVE;
        if(order[1] == Y_NEGATIVE) order[2] = Y_POSITIVE;
        else order[2] = Y_NEGATIVE;
        if(order[0] == X_NEGATIVE) order[3] = X_POSITIVE;
        else order[3] = X_NEGATIVE;

    }
    else{
        if(y > goal_y) order[0] = Y_NEGATIVE;
        else order[0] = Y_POSITIVE;
        if(x > goal_x) order[1] = X_NEGATIVE;
        else order[1] = X_POSITIVE;
        if(order[1] == X_NEGATIVE) order[2] = X_POSITIVE;
        else order[2] = X_NEGATIVE;
        if(order[0] == Y_NEGATIVE) order[3] = Y_POSITIVE;
        else order[3] = Y_NEGATIVE;
    }

    return true;
}
