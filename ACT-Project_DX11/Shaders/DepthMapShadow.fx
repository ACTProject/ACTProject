#include "00. Global.fx"
#include "00. Light.fx"
#include "00. Render.fx"



struct ShadowDebugPS
{
    float4 p : SV_POSITION;
    float4 TexShadow : TEXCOORD1;
};

//MeshOutput VS_ShadowMesh(VertexTextureNormalTangent input)
//{
//    MeshOutput output;

//    output.position = mul(input.position, W); // W
//    output.worldPosition = output.position;
//    output.position = mul(output.position, VP);
//    output.uv = input.uv;
//    output.normal = input.normal;

//    return output;
//}

ShadowDebugPS VS_ShadowModel(VertexTextureNormalTangentBlend input)
{
    ShadowDebugPS output = (ShadowDebugPS)0;
    output.p = mul(float4(input.position.xyz, 1.0f), W);
    output.p = mul(output.p, V);
    output.p = mul(output.p, P);
    output.TexShadow = mul(float4(input.position.xyz, 1.0f), Shadow);
    return output;
}

//float4 SHADOW_HEIGHTMAP_PS(ShadowDebugPS input) : SV_TARGET
//{
//    return float4(shadow, shadow, shadow, 1.0f);
//}

technique11 T0
{
    PASS_SHADOW(P0, AlphaBlend, SlopeScaledDepthBias, VS_ShadowModel)
    //PASS_SHADOW(P1, AlphaBlend, SlopeScaledDepthBias, VS_ShadowMesh, SHADOW_HEIGHTMAP_PS)
};
