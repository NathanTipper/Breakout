#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture2D.h"
#include "GameObject.hpp"

#define MAX_PARTICLES 1000

struct Particle {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class ParticleGenerator
{
public:
    ParticleGenerator();
	void Init(ShaderProgram shader, Texture2D texture, unsigned int numParticles);
    void Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    void Draw();
private:
    Particle m_particles[MAX_PARTICLES];
    ShaderProgram m_shaderProgram;
    Texture2D m_texture;
	unsigned int m_numParticles;
    unsigned int m_VAO;
    unsigned int firstUnusedParticle();
    void respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif // PARTICLEGENERATOR_H
