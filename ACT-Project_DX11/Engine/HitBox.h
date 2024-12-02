#pragma once
#include "Component.h"

class HitBox : public Component
{
	using Super = Component;
public:
	HitBox();
	virtual ~HitBox();

	void Craete(shared_ptr<GameObject> target, Vec3 size, Vec3 offset);
};

