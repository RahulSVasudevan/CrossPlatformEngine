

// Defines the input to this pixel shader
// - Should match the output of our corresponding vertex shader
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 sampleDir	: TEXCOORD;
};


// Texture-related variables
TextureCube wallTexture		: register(t0);
SamplerState basicSampler	: register(s0);


// Entry point for this pixel shader
float4 main(VertexToPixel input) : SV_TARGET
{
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	return wallTexture.Sample(basicSampler, input.sampleDir);
}