#include "gamesettings.hpp"


c_gamesettings::c_gamesettings()
{

}

c_gamesettings::c_gamesettings(JNIEnv* env, jobject gs)
{
	this->env = env;
	this->gs = gs;
}

c_gamesettings::~c_gamesettings()
{
	env->DeleteLocalRef(gs);
}

float c_gamesettings::get_fov() {

	jclass gameSettingsClass = env->GetObjectClass(gs);

	jfieldID getFovField = env->GetFieldID(gameSettingsClass, "fovSetting", "F");

	return env->GetFloatField(gs, getFovField);
}
