#pragma once
#define NOMINMAX
#undef min
#undef max
#include"../CommonFiles/IMaterial.h"
#include "reactphysics3d.h"
using namespace glm;
class IEntity {
public:

	mat4x4 worldMatrix;
	vec3 wmTrans;
	vec3 wmScale;
	float wmRot;
	vec3 forward;

	rp3d::RigidBody* rigidbody;

	IEntity();
	IEntity(IMesh* m, IMaterial* mat);
	virtual void setTranslation(float, float, float) {};
	virtual void setScale(float, float, float) {};
	virtual void setRotation(float) {};
	virtual void moveForward(float speed) {};
	~IEntity();
};