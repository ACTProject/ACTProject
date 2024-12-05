#pragma once
#include "Ui.h"


class Button : public Ui
{
	using Super = Ui;

public:
	Button();
	virtual ~Button();

	bool Picked(POINT screenPos);

	virtual void Create(Vec3 screenPos, Vec2 size, shared_ptr<class Material> material) override;
	void AddOnClickedEvent(std::function<void(void)> func);
	void InvokeOnClicked();

private:
	std::function<void(void)> _onClicked;
	RECT _rect;
};

