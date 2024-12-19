#include "00. Global.fx"
#include "00. Light.fx"
#include "00. Render.fx"

float4 PS_Collision() : SV_TARGET
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

float4 PS_Octree() : SV_TARGET
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}

float4 PS(MeshOutput input) : SV_TARGET
{
	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);

    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
   // ///Shadow
    float4 shadow = input.TexShadow;
    float2 shadowPos = shadow.xy / shadow.w;
    float texDepth = ShadowDepthTexture.Sample(LinearSampler, shadowPos.xy) + 0.005f;
    float depth = shadow.z / shadow.w;
    
    float4 Finalcolor = color; // 기본값은 diffuse color로 설정
    if (texDepth < depth)
    {
       Finalcolor = float4(0.0f, 0.0f, 0.0f, 1.f);
    }
    
    ///
    //float distance = length(input.worldPosition - CameraPosition());
	
    //float start = 60.f;
    //float end = 140.f;
    //float fogFactor = saturate((end - distance) / (end - start));
	
    //float4 fogColor = float4(0.1, 0.6, 0.9, 1.0);
    //float maxFog = 0.0;
    //if (fogFactor <= maxFog)
    //{
    //    color.rgb = lerp(fogColor.rgb, color.rgb, maxFog);
    //}
    //else
    //{
    //    color.rgb = lerp(fogColor.rgb, color.rgb, fogFactor);
    //}
    
    //if (color.a < 0.3f)
    //    discard;
    return Finalcolor;
    
    
}


technique11 T0 // 인스턴싱 렌더링
{
	PASS_VP(P0, VS_InstancingMesh, PS)
	PASS_VP(P1, VS_InstancingModel, PS)
	PASS_VP(P2, VS_InstancingAnimation, PS)
};

technique11 T1 // 싱글 렌더링
{
	PASS_VP(P0, VS_Mesh, PS)
	PASS_VP(P1, VS_Model, PS)
	PASS_VP(P2, VS_Animation, PS)
	//PASS_VP(P3, VS_MeshColor, PS)
};

technique11 T2 // 와이어프레임 인스턴싱
{
	PASS_RS_VP(P0, FillModeWireFrame, VS_InstancingMesh, PS)
	PASS_RS_VP(P1, FillModeWireFrame, VS_InstancingModel, PS)
	PASS_RS_VP(P2, FillModeWireFrame, VS_InstancingAnimation, PS)
};

technique11 T3 // 와이어프레임 싱글
{
	PASS_RS_VP(P0, FillModeWireFrame, VS_Mesh, PS)
	PASS_RS_VP(P1, FillModeWireFrame, VS_Model, PS)
	PASS_RS_VP(P2, FillModeWireFrame, VS_Animation, PS)
	//PASS_RS_VP(P3, FillModeWireFrame, VS_MeshColor, PS)
};

technique11 T4 // 매쉬 알파블렌딩
{
	PASS_BS_VP(P0, AlphaBlend, VS_Mesh, PS) // 기본적인 알파 블렌딩
	PASS_BS_VP(P1, AlphaBlendAlphaToCoverageEnable, VS_Mesh, PS) // 멀티샘플링 환경 알파블렌딩
	PASS_BS_VP(P2, AdditiveBlend, VS_Mesh, PS) // 애드블렌딩
	PASS_BS_VP(P3, AdditiveBlendAlphaToCoverageEnable, VS_Mesh, PS) // 멀티샘플링 환경 애드블렌딩
};

technique11 T5 // Debug Collider Rendering
{
	PASS_VP(P0, VS_Collision, PS_Collision)
    PASS_VP(P1, VS_Octree, PS_Octree)
};