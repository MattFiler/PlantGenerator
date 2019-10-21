Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
}

struct VS_OUTPUT_DEBUG
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

//Debug Vertex Shader
VS_OUTPUT_DEBUG VSDebug( float4 Pos : POSITION, float4 Color : COLOR )
{
    VS_OUTPUT_DEBUG output = (VS_OUTPUT_DEBUG)0;
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Color = Color;
    return output;
}

//Debug Pixel Shader
float4 PSDebug( VS_OUTPUT_DEBUG input ) : SV_Target
{
    return input.Color;
}