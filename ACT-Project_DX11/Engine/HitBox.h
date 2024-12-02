#pragma once
#include "Component.h"

class HitBox : public Component
{
	using Super = Component;
public:
	HitBox();
	virtual ~HitBox();

	void Craete(shared_ptr<class GameObject> player);

private:

};

