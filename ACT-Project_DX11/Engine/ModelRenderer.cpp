#include "pch.h"
#include "ModelRenderer.h"
#include "Material.h"
#include "ModelMesh.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "BaseCollider.h"

ModelRenderer::ModelRenderer(shared_ptr<Shader> shader)
	: Super(ComponentType::ModelRenderer), _shader(shader)
{

}

ModelRenderer::~ModelRenderer()
{

}

void ModelRenderer::SetModel(shared_ptr<Model> model)
{
	_model = model;

	const auto& materials = _model->GetMaterials();
	for (auto& material : materials)
	{
		material->SetShader(_shader);
	}
}

void ModelRenderer::RenderInstancing(shared_ptr<class InstancingBuffer>& buffer)
{
	if (_model == nullptr)
		return;

	// GlobalData
	if (GetGameObject()->GetLayerIndex() == LayerMask::Layer_UI)
		_shader->PushGlobalData(Camera::S_UIMatView, Camera::S_UIMatProjection);
	else
		_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	// Light
	auto lightObj = SCENE->GetCurrentScene()->GetLight();
	if (lightObj)
		_shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	// Bones
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	_shader->PushBoneData(boneDesc);

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
			mesh->material->Update();

		// BoneIndex
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		// IA
		mesh->vertexBuffer->PushData();
		mesh->indexBuffer->PushData();

		buffer->PushData();

		if (Camera::S_IsWireFrame)
			_technique = 2;
		else
			_technique = 0;

		_shader->DrawIndexedInstanced(_technique, _pass, mesh->indexBuffer->GetCount(), buffer->GetCount());
	}

	RenderCollider();
}

void ModelRenderer::RenderSingle()
{
	if (_model == nullptr)
		return;

	// GlobalData
	if (GetGameObject()->GetLayerIndex() == LayerMask::Layer_UI)
		_shader->PushGlobalData(Camera::S_UIMatView, Camera::S_UIMatProjection);
	else
		_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	// Light
	auto lightObj = SCENE->GetCurrentScene()->GetLight();
	if (lightObj)
		_shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	// Bones
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	_shader->PushBoneData(boneDesc);

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
			mesh->material->Update();

		// BoneIndex
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		// Transform
		auto world = GetTransform()->GetWorldMatrix();
		_shader->PushTransformData(TransformDesc{ world });

		// IA
		mesh->vertexBuffer->PushData();
		mesh->indexBuffer->PushData();

		if (Camera::S_IsWireFrame)
			_technique = 3;
		else
			_technique = 1;

		_shader->DrawIndexed(_technique, _pass, mesh->indexBuffer->GetCount(), 0, 0);
	}

	RenderCollider();
}

void ModelRenderer::RenderCollider()
{
	if (DEBUG->IsDebugEnabled() || INPUT->GetButton(KEY_TYPE::CAPSLOCK))
	{
		shared_ptr<BaseCollider> collider = GetGameObject()->GetCollider();
		if (collider)
		{
			collider->RenderCollider(_shader);
			// 기본 토폴로지 복구
			DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}
	}
}

InstanceID ModelRenderer::GetInstanceID()
{
	return make_pair((uint64)_model.get(), (uint64)_shader.get());
}
