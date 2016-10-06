/*
Main file of particle explosion program
Particle Fire simulation program using Simple DirectMedia Layer (SDL) Library

*/

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL.h>
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include "screen.h"
#include "Particle.h"
#include "Swarm.h"

using namespace sdlProgram;


int main (int argc, char** argv)
{
    srand(time(NULL));
    Screen screen;
    Swarm swarm;

    if (screen.init()==false){
        std::cout<< "SDL_Init Error: " <<std::endl;
    }

    while(true){


        int elapsed=SDL_GetTicks();
        swarm.update(elapsed);


        unsigned char green=(1+sin(elapsed*0.0001))*128;
        unsigned char red=(1+sin(elapsed*0.0002))*128;
        unsigned char blue=(1+sin(elapsed*0.0003))*128;

        const Particle *const pParticles=swarm.getParticles();

        for (int i=0;i<Swarm::NPARTICLES;i++){
                Particle particle=pParticles[i];
                int x=(particle.m_x+1)*Screen::SCREEN_WIDTH/2;  // x and y coordinates of particle explosion
                int y=particle.m_y*Screen::SCREEN_WIDTH/2+Screen::SCREEN_HEIGHT/2;
                screen.setPixel(x,y,red,green,blue); // drawing particles on the screen

       }

        screen.boxBlur();
        screen.update();

        if (screen.processEvents()==false){
            break;
        }
   }

   SDL_Delay( 2000 );  // time for particle explosion appearing on the screen
   screen.close();  // closing the screen
    // Close and destroy the window
   //system("pause");

   return 0;
}
