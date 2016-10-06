#include "Swarm.h"

namespace sdlProgram{
Swarm::Swarm():lastTime(0)
{
    m_Particles= new Particle[NPARTICLES];
}

// Updating each particle
void Swarm::update(int elapsed){
    int interval=elapsed-lastTime;

    for(int i=0;i<Swarm::NPARTICLES;i++){
            m_Particles[i].update(interval);
    }
    lastTime=elapsed;
}

// destructor and deleting all the particles in buffer
Swarm::~Swarm()
{
    delete [] m_Particles;
}

}
