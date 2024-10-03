#pragma once
#include "../../java.hpp"


class c_gamesettings
{
protected:
	JNIEnv* env;
	jobject gs;
public:
	c_gamesettings();
	c_gamesettings(JNIEnv* env, jobject gs);
	~c_gamesettings();

	float get_fov();
};