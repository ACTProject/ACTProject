#include "pch.h"
#include "Particle.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "material.h"
#include "InstancingManager.h"

Particle::Particle() : Super(ComponentType::Particle), _particleCount(0)
{

}

Particle::~Particle()
{

}

void Particle::Create(int32 count, shared_ptr<Material> material)
{
    _material = material;
    _particleCount = count;

    _particles.resize(count);
    for (auto& particle : _particles)
    {
        ResetParticle(particle);
    }

    auto go = _gameObject.lock();

    go->GetOrAddTransform();

    if (go->GetMeshRenderer() == nullptr)
        go->AddComponent(make_shared<MeshRenderer>());

    _mesh = make_shared<Mesh>();
    _mesh->CreateQuad();

    go->GetMeshRenderer()->SetMesh(_mesh);
    go->GetMeshRenderer()->SetPass(0);
    go->GetMeshRenderer()->SetMaterial(material);

    _instanceBuffer = make_shared<InstancingBuffer>();
    _instanceBuffer->CreateBuffer( _particleCount);
}

void Particle::Update()
{
    for (auto& particle : _particles)
    {
        particle.age += TIME->GetDeltaTime();

        if (particle.age >= particle.lifetime)
        {
            ResetParticle(particle);
        }
        else
        {
            particle.position += particle.velocity * TIME->GetDeltaTime();
        }
    }
}

void Particle::Render(shared_ptr<class InstancingBuffer>& buffer)
{
    if (!_mesh || !_material)
        return;

    _shader = _material->GetShader();
}

void Particle::ResetParticle(ParticleType& particle)
{
}

