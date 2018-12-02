struct DirectionalLight
{
	float4 AmbientColor;
	float4 DirColor;
	float3 Direction;
};

cbuffer externalData : register(b0)
{
	DirectionalLight light;
};


Texture2D wallTexture  : register(t0);
SamplerState basicSampler : register(s0);



struct VertexToPixel
{
	float4 position		: SV_POSITION;	// XYZW position (System Value Position)
	float4 color		: COLOR;        // RGBA color
	float3 normal		: NORMAL;
	float  pad2			: PAD2;
	float2 uv			: TEXCOORD;
	float2 pad3			: PAD3;
};






float4 main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal);

	float4 surfaceColor = wallTexture.Sample(basicSampler, input.uv);
	
	// DIFFUSE (Lambert) DIRECTIONAL LIGHT


	float3 lightDirection = -normalize(light.Direction);
	float lightAmount = dot(input.normal, lightDirection);
	lightAmount = saturate(lightAmount);
	float4 finalColor = surfaceColor * (light.DirColor * lightAmount + light.AmbientColor);
	//float4 finalColor = lightAmount * light.DirColor + light.AmbientColor;
		// Just return the input color
		// - This color (like most values passing through the rasterizer) is 
		//   interpolated for each pixel between the corresponding vertices 
		//   of the triangle we're rendering
	return float4(finalColor.xyz,1);
	//return float4(1, 1, 1, 1);
	//return input.color;
}