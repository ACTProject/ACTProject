#include "pch.h"
#include "Skybox.h"
#include "MeshRenderer.h"
#include "Camera.h"

Skybox::Skybox() : Super(ComponentType::Skybox)
{

}

Skybox::~Skybox()
{

}

void Skybox::Create(int32 i, shared_ptr<Material> material)
{

	auto go = _gameObject.lock();

	go->GetOrAddTransform();

	if (go->GetMeshRenderer() == nullptr)
		go->AddComponent(make_shared<MeshRenderer>());

	_mesh = make_shared<Mesh>();
	_mesh->CreateCubeMap(i);

	go->GetMeshRenderer()->SetMesh(_mesh);
	go->GetMeshRenderer()->SetPass(0);
	go->GetMeshRenderer()->SetMaterial(material);
}
