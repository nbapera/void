#include "floatbuffer.hpp"
#include "../../java.hpp"

floatbuffer::floatbuffer(JNIEnv* env, std::unordered_map<std::string, jclass> klasses) {
	this->env = env;
	this->klasses = klasses;
}

floatbuffer::~floatbuffer()
{

}

jclass floatbuffer::klass()
{
	return findClass("net.minecraft.client.renderer.ActiveRenderInfo");
}

matrix floatbuffer::model_view_matrix() {


	jfieldID modelViewField = env->GetStaticFieldID(klass(), "modelview", "Ljava/nio/FloatBuffer;");

	jobject modelView = env->GetStaticObjectField(klass(), modelViewField);
}