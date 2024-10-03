#pragma once
#include "../../java.hpp"

struct c_movingobject
{
protected:
	JNIEnv* env;
	jobject entity;
public:
	c_movingobject();
	c_movingobject(JNIEnv* env, jobject entity);
	~c_movingobject();

	jclass get_class();
	jobject get_instance();

	//CVec3 GetBlockPosition();
	bool is_type_of_block();
};