#pragma once
#include "Ui.h"


class Button : public Component
{
	using Super = Component;

public:
	Button();
	virtual ~Button();

	bool Picked(POINT screenPos);

	void Create(Vec3 screenPos, Vec2 size, shared_ptr<class Material> material);
	void AddOnClickedEvent(std::function<void(void)> func);
	void InvokeOnClicked();

    void AddOnHoverEvent(std::function<void(void)> func);
    void AddOnHoverEndEvent(std::function<void(void)> func);
    void CheckHover(POINT screenPos);

private:
	std::function<void(void)> _onClicked;
    std::function<void(void)> _onHover;
    std::function<void(void)> _onHoverEnd;
    bool _isHoverd = false;
	RECT _rect;
};

