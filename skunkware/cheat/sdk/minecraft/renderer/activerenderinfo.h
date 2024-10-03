#pragma once
#include "../../java.hpp"
#include "../../matrix.hpp"
#include <unordered_map>
#include <memory>
#include <string>


class c_activerenderinfo
{
protected:
	JNIEnv* env;
	std::unordered_map<std::string, jclass> klasses;
public:
	c_activerenderinfo(JNIEnv* env, std::unordered_map<std::string, jclass> klasses);
	~c_activerenderinfo();

	jclass klass();

	jclass findClass(std::string klassName) { return klasses[klassName]; }

	matrix projection_matrix();
	matrix model_view_matrix();
};

