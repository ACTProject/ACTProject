#include "pch.h"
#include "Shadow.h"
#include "ModelRenderer.h"
#include "MeshRenderer.h"
#include "Material.h"

void Shadow::Init()
{
    shadowShader = make_shared<Shader>(_shaderName);

    float widthLength = 512 * 512;
    float heightLength = 512 * 512;
    float maxViewDistance = std::sqrt(widthLength + heightLength);
    
    _lookVec = { maxViewDistance / 2,0,maxViewDistance / 2 };
    _lightPos = { maxViewDistance / 2 + 100, 100, maxViewDistance / 2 };
    _upVec = { 0,1,0 };
    // 쉐도우 행렬 초기화
    _shadowViewMat = ::XMMatrixLookAtLH(_lightPos, _lookVec, _upVec);

    _shadowProjMat = ::XMMatrixOrthographicOffCenterLH(-maxViewDistance / 2, maxViewDistance / 2, -maxViewDistance / 2, maxViewDistance / 2, 0, 10000.0f);

    _texture = Matrix(0.5f, 0.0f, 0.0f, 0.0f
        , 0.0f, -0.5f, 0.0f, 0.0f
        , 0.0f, 0.0f, 1.0f, 0.0f
        , 0.5f, 0.5f, 0.0f, 1.0f);

    _shadowDesc.Shadow = _shadowViewMat * _shadowProjMat * _texture;
}

void Shadow::Update()
{
    // 맵 오브젝트들 가져오고, 그림자맵 텍스처에 그리기.
    RenderShadow();
}

void Shadow::RenderShadow()
{
    unordered_set<shared_ptr<GameObject>> _gameObject = CUR_SCENE->GetObjects();
    for (auto& obj : _gameObject)
    {
        if (obj->GetLayerIndex() == LayerMask::Layer_UI)
            continue;
        if (obj->GetBillboard() != nullptr)
            continue;
        if (obj->GetObjectType() == ObjectType::Player)
            continue;
        if (obj->GetSkybox() != nullptr)
            continue;
    
        // 게임오브젝트를 그림자맵에 렌더링
        if (obj->GetModelRenderer() != nullptr)
        {
            shared_ptr<Shader> shader = obj->GetModelRenderer()->GetShader();
            uint8 pass = obj->GetModelRenderer()->GetPass();
            uint8 tech = obj->GetModelRenderer()->GetTechnique();

            // 섀도우 쉐이더와 패스로 변경
            obj->GetModelRenderer()->SetShader(shadowShader);
            obj->GetModelRenderer()->SetTechnique(0);
            obj->GetModelRenderer()->SetPass(0);

            // 그림자 뎁스버퍼에 z값 기입
            obj->GetModelRenderer()->RenderShadowMap(_shadowViewMat, _shadowProjMat);

            
            // 다시 기존 쉐이더와 패스로 변경.
            obj->GetModelRenderer()->SetShader(shader);
            obj->GetModelRenderer()->SetPass(pass);
            obj->GetModelRenderer()->SetTechnique(tech);
        }
    }
       /* if (obj->GetMeshRenderer() != nullptr)
        {
            shader = obj->GetMeshRenderer()->GetShader();

            
            obj->GetMeshRenderer()->GetMaterial()->SetShader(shader);
            obj->GetMeshRenderer()->SetTechnique(0);
            obj->GetMeshRenderer()->SetPass(1);

            obj->GetMeshRenderer()->RenderShadowMap(_shadowViewMat, _shadowProjMat);
            obj->GetModelRenderer()->SetShader(shader);
        }*/
}


