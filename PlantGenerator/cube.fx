cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	float3 lightColour;
	float3 lightPosition;
}

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul( input.Pos, World );
	output.Pos = mul( output.Pos, View );
	output.Pos = mul( output.Pos, Projection );
    output.Norm = mul( float4( input.Norm, 1 ), World ).xyz;
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{
	return float4(saturate(dot(lightPosition,input.Norm) * lightColour), 1);
}