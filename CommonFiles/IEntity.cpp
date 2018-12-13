#include "IEntity.h"

IEntity::IEntity()
{
}

IEntity::IEntity(IMesh* m, IMaterial* mat)  
{
}

IEntity::~IEntity()
{
	rigidbody = nullptr;
}

//void IEntity::InitializeMaterial()
//{
//}
//
//Material * IEntity::getMaterial()
//{
//	return 0;
//}
