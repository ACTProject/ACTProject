#pragma once


class Shadow
{
    DECLARE_SINGLE(Shadow);
public:
    void Init();
    void Update();

    ShadowDesc& GetShadowDesc() { return _shadowDesc; };

    void SetLight(Vec3 light) { _lightPos = light; };
private:
    void RenderShadow();
private:
    wstring _shaderName = L"DepthMapShadow.fx";
    //wstring _shaderName = L"23. RenderDemo.fx";

    shared_ptr<Shader> shadowShader;

    // lightPos 는 Client에서 얻어옴.
    Vec3 _lightPos = { 0,0,0 };
    Vec3 _lookVec = { 0,0,0 };
    Vec3 _upVec = {0,1,0};

    // 그림자 뷰,투영행렬
    Matrix _shadowViewMat;
    Matrix _shadowProjMat;
    Matrix _texture;

    // 그림자텍스처변환 행렬
    ShadowDesc _shadowDesc;
};
