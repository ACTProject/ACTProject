#pragma once
#include "Component.h"
class Slider :
	public Component
{
	using Super = Component;
public:
	Slider();
	virtual ~Slider();
	virtual void Update() override;
	void Create(Vec2 screenPos, Vec2 size, shared_ptr<class Material> material);
private:
	float _maxRatio = 0.0f;
	float _uvRatio = 1.0f;
};
