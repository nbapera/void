#include "axisaligned.hpp"
#include "../../java.hpp"
#include "../minecraft.hpp"
#include "../../jni/jni.h"



/*axis_aligned::axis_aligned(JNIEnv* env, std::unordered_map<std::string, jclass> klasses)
{
	this->env = env;
	this->klasses = klasses;
}

axis_aligned::~axis_aligned()
{

}

jclass axis_aligned::klass()
{
	return findClass("net.minecraft.client.Minecraft");
}

jobject axis_aligned::getAxisAligned()
{
	// No need to create extra objects because we aren't alowed to delete klasses
	jfieldID theMinecraftField = env->GetStaticFieldID(klass(), "theMinecraft", "Lnet/minecraft/client/Minecraft;");
	return env->GetStaticObjectField(klass(), theMinecraftField);
}

axis_aligned_t axis_aligned::GetNativeBoundingBox()
{
	if (this == NULL)
		return axis_aligned_t();

	jclass alignedAxisClass = env->GetObjectClass(aligned_axis);


	jfieldID minXField = env->GetFieldID(alignedAxisClass, "minX", "D");
	double minX = env->GetDoubleField(aligned_axis, minXField);
	jfieldID minYField = env->GetFieldID(alignedAxisClass, "minY", "D");
	double minY = env->GetDoubleField(aligned_axis, minYField);
	jfieldID minZField = env->GetFieldID(alignedAxisClass, "minZ", "D");
	double minZ = env->GetDoubleField(aligned_axis, minZField);

	jfieldID maxXField = env->GetFieldID(alignedAxisClass, "maxX", "D");
	double maxX = env->GetDoubleField(aligned_axis, maxXField);
	jfieldID maxYField = env->GetFieldID(alignedAxisClass, "maxY", "D");
	double maxY = env->GetDoubleField(aligned_axis, maxYField);
	jfieldID maxZField = env->GetFieldID(alignedAxisClass, "maxZ", "D");
	double maxZ = env->GetDoubleField(aligned_axis, maxZField);

	env->DeleteLocalRef(alignedAxisClass);

	return { (float)minX, (float)minY, (float)minZ, (float)maxX, (float)maxY, (float)maxZ };


}

void axis_aligned::SetNativeBoundingBox(axis_aligned_t buffer)
{
	if (this == NULL)
		return;

	jclass alignedAxisClass = env->GetObjectClass(aligned_axis);

	jfieldID minXField = env->GetFieldID(alignedAxisClass, "minX", "D");
	jfieldID minYField = env->GetFieldID(alignedAxisClass, "minY", "D");
	jfieldID minZField = env->GetFieldID(alignedAxisClass, "minZ", "D");

	jfieldID maxXField = env->GetFieldID(alignedAxisClass, "maxX", "D");
	jfieldID maxYField = env->GetFieldID(alignedAxisClass, "maxY", "D");
	jfieldID maxZField = env->GetFieldID(alignedAxisClass, "maxZ", "D");


	env->SetDoubleField(aligned_axis, minXField, buffer.minX);
	env->SetDoubleField(aligned_axis, minYField, buffer.minY);
	env->SetDoubleField(aligned_axis, minZField, buffer.minZ);

	env->SetDoubleField(aligned_axis, maxXField, buffer.maxX);
	env->SetDoubleField(aligned_axis, maxYField, buffer.maxY);
	env->SetDoubleField(aligned_axis, maxZField, buffer.maxZ);

	env->DeleteLocalRef(alignedAxisClass);
}
*/