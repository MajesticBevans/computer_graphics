#include "agent.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Agent::Agent()
{
    srand(time(NULL));
    int randx = rand() % this->WORLD_SIZE, randy = rand() % this->WORLD_SIZE;
    this->setPosition(randx, randy);
}

int* Agent::getPosition()
{
    return this->position;
}

void Agent::setPosition( int x, int y )
{
    this->position[0] = x;
    this->position[1] = y;
}

void Agent::takeRandomAction()
{
    bool valid = false;
    while (!valid)
    {
        int random = rand() % 5;
        int* action = this->actions[random];
        int newPos[2] = {this->getPosition()[0] + action[0], this->getPosition()[1] + action[1]};

        if (newPos[0] < this->WORLD_SIZE && newPos[1] < this->WORLD_SIZE && newPos[0] >= 0 and newPos[1] >= 0)
        {
            this->setPosition(newPos[0], newPos[1]);
            valid = true;
        }
    }
}

void Agent::takePlannedAction()
{
}

int Agent::getHealth()
{
    return this->health;
}

int Agent::getLoot()
{
    return this->loot;
}

void Agent::eat( )
{
    this->health += 5;
}

void Agent::mine( )
{
    this->loot += 1;
}