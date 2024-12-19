#include "00. Global.fx"
#include "00. Light.fx"
#include "00. Render.fx"

//MeshOutput vs(MeshOutput input)
//{
//    MeshOutput output = (MeshOutput) 0;
//    output.p = mul(float4(input.position.xyz, 1.0f),W);
//    output.p = mul(output.p, V);
//    output.p = mul(output.p, P);
//    output.d = output.p.zw;
//    return output;
//}

//float4 ps(MeshOutput input) : SV_TARGET
//{
//    float shadow = input.d.x / input.d.y;
//    return float4(shadow, shadow, shadow, 1.0f);
//}

//technique11 T0
//{
//    PASS_SHADOW(P0, AlphaBlend, SlopeScaledDepthBias, vs, ps)
//    //PASS_SHADOW(P1, AlphaBlend, SlopeScaledDepthBias, VS_ShadowMesh, SHADOW_HEIGHTMAP_PS)
//};
