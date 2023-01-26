#include "world.h"
using namespace cv;

World::World( Agent* a )
{
    this->agent = a;
    srand(time(NULL));
}

void World::createWorld()
{
    for (int i = 0; i < this->WORLD_SIZE; i++)
    {
        for (int j = 0; j < this->WORLD_SIZE; j++)
        {
            this->world[i][j] = rand() % 3;
        } 
    } 
}

void World::checkAgent( )
{
    assert(this->agent->getPosition()[0] >= 0 && "Position Invalid.");
    assert(this->agent->getPosition()[0] < WORLD_SIZE && "Position Invalid.");
    assert(this->agent->getPosition()[1] >= 0 && "Position Invalid.");
    assert(this->agent->getPosition()[1] < WORLD_SIZE && "Position Invalid.");
}

void World::log(int step)
{
    int image_size = 512;
    Mat img(image_size, image_size, CV_8UC3, Scalar(255,255,255));
    int R, G, B;

    int rect_size = 8;                        

    Scalar color;
    for ( int i = 0; i < WORLD_SIZE; i++ )
    {
        for (int j = 0; j < WORLD_SIZE; j++ )
        {
            int cenx = ( 512 / WORLD_SIZE ) * i + ( 512 / WORLD_SIZE / 2 );
            int ceny = ( 512 / WORLD_SIZE ) * j + ( 512 / WORLD_SIZE / 2 );

            if ( this->agent->getPosition()[0] == i && this->agent->getPosition()[1] == j )
            {
                R = 0;
                G = 0;
                B = 255;
            }
            else
            {
                switch ( this->world[i][j])
                {
                    case FOOD:
                        R = 0;
                        G = 255;
                        B = 0;
                        break;
                    case GOLD:
                        R = 255;
                        G = 255;
                        B = 0;
                        break;
                    default:
                        R = 0;
                        G = 0;
                        B = 0;
                        break;
                }
            }
            const Point pt1(cenx-rect_size,ceny-rect_size), pt2(cenx+rect_size,ceny+rect_size);

            rectangle(img, pt1, pt2, Scalar(B, G, R), -1);
        }
    }
    imwrite( "log_" + std::to_string(step) + ".jpg", img );
}

void World::take_random_step()
{
    this->agent->takeRandomAction();
    int *location = &this->world[this->agent->getPosition()[0]][this->agent->getPosition()[1]];

    switch (*location)
    {
    case FOOD:
        this->agent->eat();
        *location = NOTHING;
        break;
    case GOLD:
        this->agent->mine();
        *location = NOTHING;
    default:
        break;
    }
}

void World::take_planned_step()
{
    this->agent->takePlannedAction();

    switch (this->world[this->agent->getPosition()[0]][this->agent->getPosition()[1]])
    {
    case FOOD:
        this->agent->eat();
        break;
    case GOLD:
        this->agent->mine();
    default:
        break;
    }
}

void World::run(int search_type)
{
    int steps = 0;
    int max_steps = WORLD_SIZE * WORLD_SIZE;

    while ( steps < max_steps )
    {
        switch( search_type )
        {
            case RANDOM:
                this->take_random_step();
                break;
            case PLANNED:
                this->take_planned_step();
                break;
            default:
                std::cout << "Invalid choice selected for search type\n";
                exit(-1);
        }

        this->log(steps);
        steps += 1;

        if ( this->agent->getHealth() <= 0 )
        {
            std::cout << "You starved to death!" << std::endl;
            std::cout << "You managed to collect " << this->agent->getLoot() << " loot!" << std::endl;
            return;
        }

    }
}