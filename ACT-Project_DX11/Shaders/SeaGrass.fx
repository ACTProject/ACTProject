#include "00. Global.fx"
#include "00. Light.fx"
#include "00. Render.fx"

RasterizerState NoCull
{
    CullMode = None; // Back Face Culling 비활성화
    FillMode = Solid; // Solid 모드
    FrontCounterClockwise = false; // 기본 설정
};
float4 PS_Collision() : SV_TARGET
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
MeshOutput VS_SeaGrassInstancing(InstancingVertexModel input)
{
    MeshOutput output;

    float4 worldPos = mul(input.position, BoneTransforms[BoneIndex]);

    worldPos = mul(worldPos, input.world);

    
    float waveOffset = sin(worldPos.y * (3.0) + gameTime * 3.0) * (0.5); // sin내부 커질수록 간격 좁아짐, 밖 커질수록 진폭 커짐
    worldPos.x += waveOffset;
    worldPos.z += waveOffset;
    
    
    
    output.worldPosition = worldPos;
    output.position = mul(worldPos, VP);

    output.uv = input.uv;
    output.normal = input.normal;

    return output;
}

MeshOutput VS_SeaGrass(VertexTextureNormalTangent input)
{
    MeshOutput output;

    output.position = mul(input.position, BoneTransforms[BoneIndex]); // Model Global
    output.position = mul(output.position, W); // W
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    
    output.uv = input.uv;
    output.normal = input.normal;

    return output;
}
float4 PS(MeshOutput input) : SV_TARGET
{
	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);

    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
	
    float distance = length(input.worldPosition - CameraPosition());
	
    float start = 50.f;
    float end = 70.f;
    float fogFactor = saturate((end - distance) / (end - start));
	
    float4 fogColor = float4(0.1, 0.6, 0.9, 1.0);
    float maxFog = 0.0;
    
    color.rgb = float3(0.42, 0.65, 0.17);
    
    if (fogFactor <= maxFog)
    {
        color.rgb = lerp(fogColor.rgb, color.rgb, maxFog);
    }
    else
    {
        color.rgb = lerp(fogColor.rgb, color.rgb, fogFactor);
    }
    
    return color;
}

technique11 T0 // 인스턴싱 렌더링
{
    PASS_RS_VP(P0_NoCull, NoCull, VS_InstancingMesh, PS)
    PASS_RS_VP(P1_NoCull, NoCull, VS_SeaGrassInstancing, PS)
    PASS_RS_VP(P2_NoCull, NoCull, VS_InstancingAnimation, PS)
};

technique11 T1 // 싱글 렌더링
{
    PASS_RS_VP(P0_NoCull, NoCull, VS_Mesh, PS)
    PASS_RS_VP(P1_NoCull, NoCull, VS_SeaGrass, PS)
    PASS_RS_VP(P2_NoCull, NoCull, VS_Animation, PS)
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
};