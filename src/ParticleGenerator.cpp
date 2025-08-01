#include "ParticleGenerator.hpp"
#include <iostream>

ParticleGenerator::ParticleGenerator()
{ }

void ParticleGenerator::Update(float dt, GameObject &object, unsigned int newParticles, glm::vec2 offset)
{
    for (unsigned int i = 0; i < newParticles; ++i)
    {
        int unusedParticle = firstUnusedParticle();
        respawnParticle(m_particles[unusedParticle], object, offset);
    }

    for (unsigned int i = 0; i < m_numParticles; ++i)
    {
        Particle &p = m_particles[i];
        p.Life -= dt;
        if (p.Life > 0.0f)
        {
            p.Position -= p.Velocity * dt; 
            p.Color.a -= dt * 2.5f;
        }
    }
}

void ParticleGenerator::Draw()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    m_shaderProgram.Use();
    for (Particle particle : m_particles)
    {
        if (particle.Life > 0.0f)
        {
            m_shaderProgram.SetVec2("offset", particle.Position);
            m_shaderProgram.SetVec4("color", particle.Color);
            m_texture.Bind();
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::Init(ShaderProgram shader, Texture2D texture, unsigned int numParticles)
{
    m_shaderProgram = shader;
    m_texture = texture;
    if(numParticles > MAX_PARTICLES)
    {
        numParticles = MAX_PARTICLES;
    }
    m_numParticles = numParticles;

    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    }; 
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(m_VAO);
    // fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    // create amount default particle instances
    for (unsigned int i = 0; i < m_numParticles; ++i)
        m_particles[i] = Particle();
}

// stores the index of the last particle used (for quick access to next dead particle)
unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
    // first search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < m_numParticles; ++i){
        if (m_particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i){
        if (m_particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle.Position = object.GetPosition() + random + offset;
    particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.Life = 1.0f;
    particle.Velocity = object.GetVelocity() * 0.1f;
}
