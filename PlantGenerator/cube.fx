Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	int numOfLights;
	float3 lightPosition[10];
	float4 lightColour[10];
}

struct VS_INPUT
{
    float4 Pos : POSITION;
    //float2 Tex : TEXCOORD0;
    float3 Norm : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    //float2 Tex : TEXCOORD0;
    float3 Norm : NORMAL;
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
    //output.Tex = input.Tex;
    output.Norm = mul( float4( input.Norm, 1 ), World ).xyz;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{
    //float4 textureBase = txDiffuse.Sample( samLinear, input.Tex );
	float4 textureBase = 0;
	for (int i = 0; i < numOfLights; i++) {
        textureBase += saturate( dot( lightPosition[i],input.Norm) * lightColour[i] );
	}
    textureBase.a = 1;
    return textureBase;
}
