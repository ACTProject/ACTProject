#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Light.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::RenderInstancing(shared_ptr<class InstancingBuffer>& buffer)
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	auto shader = _material->GetShader();
	if (shader == nullptr)
		return;

	// GlobalData
	shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	// Light
	auto lightObj = SCENE->GetCurrentScene()->GetLight();
	if (lightObj)
		shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	// Light
	_material->Update();

	// IA
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();

	buffer->PushData();

	if (Camera::S_IsWireFrame)
		_technique = 2;
	else
		_technique = 0;

	shader->DrawIndexedInstanced(_technique, _pass, _mesh->GetIndexBuffer()->GetCount(), buffer->GetCount());
}

void MeshRenderer::RenderSingle()
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	auto shader = _material->GetShader();
	if (shader == nullptr)
		return;


	// GlobalData
	shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	// Light
	auto lightObj = SCENE->GetCurrentScene()->GetLight();
	if (lightObj)
		shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	// Light
	_material->Update();

	// Transform
	auto world = GetTransform()->GetWorldMatrix();
	shader->PushTransformData(TransformDesc{ world });

	// IA
	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();

	if (_isAlphaBlend)
		_technique = 4;
	if (Camera::S_IsWireFrame)
		_technique = 3;
	else
		_technique = 1;

	shader->DrawIndexed(_technique, _pass, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}

InstanceID MeshRenderer::GetInstanceID()
{
	return make_pair((uint64)_mesh.get(), (uint64)_material.get());
}