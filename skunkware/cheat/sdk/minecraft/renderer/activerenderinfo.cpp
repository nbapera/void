#include "activerenderinfo.h"





c_activerenderinfo::c_activerenderinfo(JNIEnv* env, std::unordered_map<std::string, jclass> klasses)
{
	this->env = env;
	this->klasses = klasses;
}

c_activerenderinfo::~c_activerenderinfo()
{

}

jclass c_activerenderinfo::klass()
{
	return findClass("net.minecraft.client.renderer.ActiveRenderInfo");
}

matrix c_activerenderinfo::model_view_matrix() {


	jfieldID modelViewField = env->GetStaticFieldID(klass(), "modelview", "Ljava/nio/FloatBuffer;");

	jobject modelView = env->GetStaticObjectField(klass(), modelViewField);
}