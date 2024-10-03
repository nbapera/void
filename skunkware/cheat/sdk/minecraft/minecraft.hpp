#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../jni/jni.h"

#include "renderer/activerenderinfo.h"

class c_minecraft {
private:
	JNIEnv* env;
	std::unordered_map<std::string, jclass> klasses;

public:
	c_minecraft(JNIEnv* env, std::unordered_map<std::string, jclass> klasses);
	~c_minecraft();

	jclass findClass(std::string klassName) { return klasses[klassName]; }

	jclass klass();
	jobject getMinecraft();
	jobject getPlayer();
	jobject getAxis();
	jobject getWorld();
	jobject getMovingObject();
	jobject getGameSettings();
	c_activerenderinfo* getActiveRenderInfo();

	bool is_in_gui_state();


};

extern std::unique_ptr<c_minecraft> instance;
extern std::unique_ptr<c_activerenderinfo> renderinfo;