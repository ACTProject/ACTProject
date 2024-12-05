#include "pch.h"
#include "Ui.h"

void Ui::SetOwner(shared_ptr<GameObject> obj)
{
    _owner = obj;

    _isVisible = false;
}

void Ui::PreUpdate()
{
    ImGui::Checkbox("visible", &_isVisible);
}
