#include "../../java.hpp"
#include "../../vec3.hpp"

#include <vector>
#include <memory>
#include <string>

#pragma once
class c_entity
{
protected:
	JNIEnv* env;
	jobject entity;
public:
	c_entity();
	c_entity(JNIEnv* env, jobject entity);
	~c_entity();

	double getPosX();
	double getPosY();
	double getPosZ();

	vec3_t get_motion();
	vec3_t get_pos();
	vec3_t get_prev_pos();
	bool is_on_ground();
	void set_motion(vec3_t motion);
	int get_hurt_timer();
	int get_max_hurt_timer();

	float getRotationPitch();
	float getRotationYaw();
	void setRotationPitch(float pitch);
	void setRotationYaw(float yaw);

	float getPrevRotationPitch();
	float getPrevRotationYaw();
	void setPrevRotationPitch(float pitch);
	void setPrevRotationYaw(float yaw);

	bool isInvisible();


	jobject getEntity() { return entity; }
};

class c_entity_player : public c_entity
{
public:
	c_entity_player(JNIEnv* env, jobject player);
	~c_entity_player();

	std::string getCurrentItem();
};

inline std::unique_ptr<c_entity_player> localPlayer;

class c_world
{
private:
	JNIEnv* env;
	jobject world;
public:
	c_world(JNIEnv* env, jobject world);
	~c_world();

	std::vector<std::shared_ptr<c_entity_player>> getPlayers();
	std::vector<std::shared_ptr<c_entity>> getEntities();

	jobject getWorld() { return world; }
};
inline std::unique_ptr<c_world> world;