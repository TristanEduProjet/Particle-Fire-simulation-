#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

namespace sdlProgram{
class Swarm
{
    public:
        const static int NPARTICLES=5000;  //Number of particles used for explosion

    public:
        Swarm();
        virtual ~Swarm();
        void update(int elapsed);
        const Particle *const getParticles(){return m_Particles;};

    protected:

    private:
        Particle *m_Particles;
        int lastTime;
};
}
#endif // SWARM_H
