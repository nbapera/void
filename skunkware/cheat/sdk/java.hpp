#pragma once
#include "jni/jni.h"
#include "jni/jvmti.h"

#include <unordered_map>
#include <string>

namespace java {

	inline std::unordered_map<std::string, jclass> klasses;

	inline JNIEnv* env;
	inline jvmtiEnv* jvmtiEnv;
	inline JavaVM* vm;

	void get_klasses();
	bool attach();
}