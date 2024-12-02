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
	if (INPUT->GetButtonDown(KEY_TYPE::KEY_F1)) // F1 ?붾쾭洹?紐⑤뱶 ON/OFF
	{
		bool currentState = DEBUG->IsDebugEnabled();
		DEBUG->EnableDebug(!currentState);
	}
}
