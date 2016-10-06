#include "Particle.h"
#include <stdlib.h>
#include<math.h>


namespace sdlProgram{
Particle::Particle():m_x(0),m_y(0)
{
   init();

}
//Initialising variable direction and speed
void Particle::init(){
    m_x=0;
    m_y=0;
    m_direction=(2*M_PI*rand())/RAND_MAX; // random direction  with particle move
    m_speed=(0.04*rand())/RAND_MAX;       // speed with which the particles move
    m_speed*=m_speed;



}
// updating particle speed and direction
void Particle::update(int interval){
    m_direction+=interval*0.0003;

    double xspeed=m_speed*cos(m_direction);
    double yspeed=m_speed*sin(m_direction);

    m_x+=xspeed*interval;
    m_y+=yspeed*interval;

    if(m_x<-1 ||m_x>1 ||m_y<-1|| m_y>1){
        init();
    }
    if(rand()<RAND_MAX/100){
        init();
    }


}
// destructor for deleting all the variables generated
Particle::~Particle()
{
    //dtor
}



}
