#pragma once

struct float2
{
	float x;
	float y;

	float2() { x = 0;y = 0;}
	float2(float a, float b) { x = a;y = b;}
};

struct float3
{
	float x;
	float y;
	float z;

	float3() { x = 0;y = 0;z = 0; }
	float3(float a, float b, float c) { x = a;y = b;z = c; }
};

struct float4
{
	float r;
	float g;
	float b;
	float a;

	float4() { r = 0;g = 0;b = 0;a = 0; }
	float4(float w, float x, float y, float z) { r = w;g = x;b = y;a = z; }
};