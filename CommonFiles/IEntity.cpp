#include "IEntity.h"

IEntity::IEntity()
{
}

IEntity::IEntity(IMesh* m, IRenderer* renderer)
{
}

IEntity::~IEntity()
{
}

void IEntity::InitializeMaterial()
{
}

Material * IEntity::getMaterial()
{
	return nullptr;
}
