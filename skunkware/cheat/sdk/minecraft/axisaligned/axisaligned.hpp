#pragma once

struct axis_aligned_t {
	float minX, minY, minZ, maxX, maxY, maxZ;
};

/*class axis_aligned
{
private:
	JNIEnv* env;
	std::unordered_map<std::string, jclass> klasses;

public:
	axis_aligned(JNIEnv* env, std::unordered_map<std::string, jclass> klasses);
	~axis_aligned();

	jclass findClass(std::string klassName) { return klasses[klassName]; }

	jclass klass();
	jobject getAxisAligned();

	axis_aligned_t GetNativeBoundingBox();
	void SetNativeBoundingBox(axis_aligned_t buffer);
};*/