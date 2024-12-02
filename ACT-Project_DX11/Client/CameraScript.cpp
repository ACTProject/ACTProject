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
	if (INPUT->GetButtonDown(KEY_TYPE::KEY_F1)) // F1 디버그 모드 on/off
	{
		bool currentState = DEBUG->IsDebugEnabled();
		DEBUG->EnableDebug(!currentState);
	}
}
