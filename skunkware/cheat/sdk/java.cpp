#include "java.hpp"
#include <windows.h>
#include <iostream>

bool java::attach() {
	HMODULE jvm = GetModuleHandleA("jvm.dll");

	using t_createdvms = jint(__stdcall*)(JavaVM**, jsize, jsize*);

	FARPROC processAddress = GetProcAddress(reinterpret_cast<HMODULE>(jvm), "JNI_GetCreatedJavaVMs");
	t_createdvms created_java_vms = reinterpret_cast<t_createdvms>(processAddress);

	auto ret = created_java_vms(&vm, 1, nullptr);

	if (ret != JNI_OK)
		return false;

	ret = vm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr);

	if (ret != JNI_OK)
		return false;

	vm->GetEnv(reinterpret_cast<void**>(&jvmtiEnv), JVMTI_VERSION_1_1);

	if (!jvmtiEnv)
		return false;

	get_klasses();

	std::cout << "(" << klasses.size() << ") klasses found" << std::endl;

	return true;
}

void java::get_klasses()
{
	jint numberOfClasses;
	jclass* classes;

	jvmtiEnv->GetLoadedClasses(&numberOfClasses, &classes);

	for (int i = 0; i < numberOfClasses; i++)
	{
		jclass klass = env->FindClass("java/lang/Class");

		jmethodID getNameMid = env->GetMethodID(klass, "getName", "()Ljava/lang/String;");
		jstring name = (jstring)env->CallObjectMethod(classes[i], getNameMid);

		const char* str = env->GetStringUTFChars(name, 0);
		std::string klassName(str);
		env->ReleaseStringUTFChars(name, str);
		
		if (klassName._Starts_with("net.minecraft.client.Minecraft"))
		{
			klasses[klassName] = classes[i];
		}
		else
		{
			env->DeleteLocalRef(classes[i]);
		}

	}
}
