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
	if (INPUT->GetButton(KEY_TYPE::KEY_F1)) // F1 디버그 모드 ON/OFF
	{
		bool currentState = DEBUG->IsDebugEnabled();
		DEBUG->EnableDebug(!currentState);
	}
}
