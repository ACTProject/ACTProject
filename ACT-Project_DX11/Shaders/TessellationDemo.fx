//#include "00. Global.fx"
//#include "00. Light.fx"
//#include "00. Render.fx"
//
//// Hull Shader : 공간분할 단계, 폴리곤을 어떻게, 얼마나 분할 할지 정함
//// 헐쉐이더에서 정한 거에 따라 Vertex들이 새로 생김
//// 이 Vertex에 대해 Domain Shader에서 로직 실행
//// 정점 = 컨트롤 포인트, 패치 = 컨트롤 포인트로 만들어낸 다각형 전체
//
//struct VertexIn
//{
//    float3 position : POSITIONT;
//    float2 uv : TESCOORD0;
//};
//
//struct VertexOut
//{
//    float3 position : POSITIONT;
//    float2 uv : TESCOORD0;
//};
//
//Texture2D heightMap;
//
//float heightScale = 10.0f;
//
//VertexOut VS(VertexIn input)
//{
//    VertexOut output;
//
//    output.position = mul(float4(input.position, 1.0f), W).xyz;
//    output.uv = input.uv;
//
//    return output;
//}
//
//struct PatchTess
//{
//    float edge[4] : SV_TessFactor; //변을 4개로 세분화 함 ex) ------O------O------O-------
//    float inside[2] : SV_InsideTessFactor; // 내부 분할
//};
//
//PatchTess ConstantHS(InputPatch<VertexOut, 4> p, uint patchId : SV_PrimitiveID)
//{
//    PatchTess tess;
//
//    // 네 변의 텍셀레이션 팩터
//    tess.edge[0] = 8.0f;//클수록 많이 나눔 64까지
//    tess.edge[1] = 8.0f;
//    tess.edge[2] = 8.0f;
//    tess.edge[3] = 8.0f;
//
//    // 내부
//    tess.inside[0] = 8.0f;
//    tess.inside[1] = 8.0f;
//
//    return tess;
//}
//
//struct HullOut
//{
//    float3 position : POSITIONT; // 컨트롤 포인트 위치
//};
//
//
//[domain("quad")]//패치의 종류
//[partitioning("integer")]// 분할 유형 (integer : 1..64 )
//[outputtopology("triangle_cw")]// 테셀레이터의 출력 기본 형식 정의 : 삼각형 시계방향으로 (clock_wise)
//[outputcontrolpoints(4)] // 입력된 컨트롤 포인트 수
//[patchconstantfunc("ConstantHS")] // 함수의 이름
//[maxtessfactor(64.0f)] // 모든 테셀레이션 계수에 대해 헐 쉐이더가 반환할 최댓값
//HullOut HS(InputPatch<VertexOut, 4> p,
//    uint i : SV_OutputControlPointID,
//    uint patchId : SV_PrimitiveID)
//{
//    HullOut output;
//    output.position = p[i].position; // 입력 컨트롤 포인트를 그대로 출력
//
//    return output;
//}
//
//struct DomainOUt
//{
//    float4 position : SV_Position; // 최종 좌표
//    float2 uv : TEXCOORD0;
//};
//
////[domain("quad")]
////DomainOUt DS(PatchTess patchTess,
////    float2 uv : SV_DomainLocation,
////    const OutputPatch<HullOut, 4> quad)
////{
////    DomainOUt output;
////
////    // 이중 선형 보간을 이용해 사각형 위치 계산
////    float3 position = lerp(lerp(quad[0].position, quad[1].position, uv.x), // Linear Interpolation : 두 값을 선형보간한다.
////        lerp(quad[3].position, quad[2].position, uv.x), uv.y);
////
////    float height = heightMap.Sample(LinearSampler, uv).r * heightScale;
////    position.y += height;
////
////    output.position = mul(float4(position, 1.0f), VP);
////    output.uv = uv;
////
////    return output;
////}
//
//[domain("quad")]
//DomainOUt DS(PatchTess patchTess,
//    float2 uv : SV_DomainLocation,
//    const OutputPatch<HullOut, 4> quad)
//{
//    DomainOUt output;
//
//    // 이중 선형 보간을 이용해 사각형 위치 계산
//    float3 position = lerp(lerp(quad[0].position, quad[1].position, uv.x),
//        lerp(quad[3].position, quad[2].position, uv.x), uv.y);
//
//    // UV 범위 확인 및 클램핑
//    float2 clampedUV = clamp(uv, 0.0f, 1.0f);
//
//    // 높이맵 샘플링
//    float height = clamp(heightMap.Sample(LinearSampler, clampedUV).r * heightScale, 0.0f, 10.0f);
//    position.y += height;
//
//    // 최종 출력
//    output.position = mul(float4(position, 1.0f), VP);
//    output.uv = clampedUV;
//
//    return output;
//}
//float4 PS(MeshOutput input) : SV_TARGET
//{
//    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
//    return color;
//}
//
//technique T0
//{
//    pass P0
//    {
//        SetVertexShader(CompileShader(vs_5_0, VS()));
//        SetHullShader(CompileShader(hs_5_0, HS()));
//        SetDomainShader(CompileShader(ds_5_0, DS()));
//        SetPixelShader(CompileShader(ps_5_0, PS()));
//    }
//}

// TessellationDemo.fx

#ifndef _TESSELLATION_DEMO_FX_
#define _TESSELLATION_DEMO_FX_

#include "00. Global.fx"
#include "00. Light.fx"

///////////////
// Constant Buffers
///////////////
cbuffer TessellationBuffer
{
    float tessellationFactor; // 기본 테셀레이션 강도
    float minDistance;        // 최소 거리
    float maxDistance;        // 최대 거리
    float padding;
};

///////////////
// Vertex Shader
///////////////
struct TessVertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct TessControlPoint
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

TessControlPoint VS_Tess(TessVertexInput input)
{
    TessControlPoint output;
    output.position = mul(input.position, W); // 월드 좌표 변환
    output.uv = input.uv;
    return output;
}

///////////////
// Hull Shader
///////////////
struct HullOutput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};
struct PatchConstants
{
    float TessellationFactor[3] : SV_TessFactor;        // 삼각형의 각 변에 대한 테셀레이션 강도
    float InsideTessellationFactor : SV_InsideTessFactor; // 삼각형 내부 테셀레이션 강도
};

// 카메라 위치 추출 함수
float3 GetCameraPosition()
{
    return float3(VInv._41, VInv._42, VInv._43); // VInv 매트릭스의 위치 정보 사용
}

PatchConstants HS_CalculatePatchConstants(InputPatch<TessControlPoint, 3> patch)
{
    float3 cameraPosition = GetCameraPosition();

    // 패치의 중심 좌표 계산
    float3 worldPosition = (patch[0].position.xyz + patch[1].position.xyz + patch[2].position.xyz) / 3.0f;
    float distance = length(worldPosition - cameraPosition);

    // 거리 기반 테셀레이션 강도 계산
    float tessFactor = saturate(1.0f - (distance - minDistance) / (maxDistance - minDistance)) * tessellationFactor;

    PatchConstants output;
    output.TessellationFactor[0] = tessFactor; // 삼각형의 첫 번째 변
    output.TessellationFactor[1] = tessFactor; // 삼각형의 두 번째 변
    output.TessellationFactor[2] = tessFactor; // 삼각형의 세 번째 변
    output.InsideTessellationFactor = tessFactor; // 삼각형 내부 강도
    return output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("HS_CalculatePatchConstants")]
HullOutput HS_Tess(InputPatch<TessControlPoint, 3> patch, uint i : SV_OutputControlPointID)
{
    HullOutput output;
    output.position = patch[i].position;
    output.uv = patch[i].uv;
    return output;
}

///////////////
// Domain Shader
///////////////
struct DomainOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

[domain("tri")]
DomainOutput DS_Tess(PatchConstants patch, float3 bary : SV_DomainLocation, const OutputPatch<HullOutput, 3> controlPoints)
{
    float4 pos = bary.x * controlPoints[0].position + bary.y * controlPoints[1].position + bary.z * controlPoints[2].position;

    DomainOutput output;
    output.position = mul(pos, VP); // VP 변환
    output.worldPosition = pos.xyz; // 월드 좌표
    output.uv = bary.x * controlPoints[0].uv + bary.y * controlPoints[1].uv + bary.z * controlPoints[2].uv;
    output.normal = float3(0, 1, 0); // 기본 법선
    return output;
}

///////////////
// Pixel Shader
///////////////
float4 PS_Tess(DomainOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

technique11 T_Tessellation
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS_Tess()));
        SetHullShader(CompileShader(hs_5_0, HS_Tess()));
        SetDomainShader(CompileShader(ds_5_0, DS_Tess()));
        SetPixelShader(CompileShader(ps_5_0, PS_Tess()));
    }
};

#endif
