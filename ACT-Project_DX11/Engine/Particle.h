#pragma once
#include "Component.h"

struct ParticleType
{
    Vec3 position;
    Vec3 velocity;
    float lifetime;
    float age;
};

class Particle : public Component
{
	using Super = Component;

public:
    Particle();
	~Particle();

public:

    void Create(int32 count, shared_ptr<Material> material);
    void Update();
    void Render(shared_ptr<class InstancingBuffer>& buffer);

private:
    void ResetParticle(ParticleType& particle);

private:
    vector<ParticleType> _particles;
    shared_ptr<Mesh> _mesh;
    shared_ptr<Material> _material;
    shared_ptr<Shader> _shader;
    shared_ptr<InstancingBuffer> _instanceBuffer;
    int _particleCount;
};

