#include "movingobject.hpp"
#include "../../minecraft/minecraft.hpp"

c_movingobject::c_movingobject()
{
}


c_movingobject::~c_movingobject()
{
	env->DeleteLocalRef(entity);
}


c_movingobject::c_movingobject(JNIEnv* env, jobject entity)
{
	this->env = env;
	this->entity = entity;
}

bool c_movingobject::is_type_of_block()
{
	jobject typeOfHit = instance->getMovingObject();
	if (!typeOfHit) return false;

	jclass movingObjectType = java::env->GetObjectClass(typeOfHit);
	if (!movingObjectType) return false;
	jfieldID block = java::env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	if (!block) return false;
	jobject object = java::env->GetStaticObjectField(movingObjectType, block);
	if (!object) return false;

	return java::env->IsSameObject(object, typeOfHit);
}