#pragma once
#include "Component.h"

class Skybox : public Component
{
	using Super = Component;

public:
	Skybox();
	~Skybox();

	shared_ptr<Mesh> GetMesh() { return _mesh; }

	void Create(int32 i, shared_ptr<Material> material);

private:
	shared_ptr<Mesh> _mesh;
};

