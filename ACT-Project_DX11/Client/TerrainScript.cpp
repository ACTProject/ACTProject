#include "pch.h"
#include "Camera.h"
#include "TerrainScript.h"
#include "Transform.h"

void TerrainScript::Start()
{

}

void TerrainScript::Update()
{
	float dt = TIME->GetDeltaTime();

	Vec3 cameraPos = GetTransform()->GetPosition();
}
