#pragma once
#include "../../jni/jni.h"

#include "../../matrix.hpp"

class floatbuffer
{
protected:
	JNIEnv* env;
	std::unordered_map<std::string, jclass> klasses;
public:
	floatbuffer(JNIEnv* env, std::unordered_map<std::string, jclass> klasses);
	~floatbuffer();

	jclass klass();

	jclass findClass(std::string klassName) { return klasses[klassName]; }

	matrix projection_matrix();
	matrix model_view_matrix();
};

