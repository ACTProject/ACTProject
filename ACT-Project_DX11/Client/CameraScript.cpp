#include "pch.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Transform.h"

void CameraScript::Start()
{

}

void CameraScript::Update()
{
	ProcessInput();	
}

void CameraScript::ProcessInput()
{
	if (INPUT->GetButtonDown(KEY_TYPE::KEY_F1)) // F1 Ű�� ����� ��� ON/OFF
	{
		Camera::S_IsWireFrame = false;
	}

	if (INPUT->GetButton(KEY_TYPE::KEY_2))
	{
		Camera::S_IsWireFrame = true;
	}
}
