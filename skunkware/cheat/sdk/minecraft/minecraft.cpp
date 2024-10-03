#include "minecraft.hpp"

std::unique_ptr<c_minecraft> instance;
std::unique_ptr<c_activerenderinfo> renderinfo;

c_minecraft::c_minecraft(JNIEnv* env, std::unordered_map<std::string, jclass> klasses)
{
	this->env = env;
	this->klasses = klasses;
}

c_minecraft::~c_minecraft()
{

}

jclass c_minecraft::klass()
{
	return findClass("net.minecraft.client.Minecraft");
}

jobject c_minecraft::getMinecraft()
{
	// No need to create extra objects because we aren't alowed to delete klasses
	jfieldID theMinecraftField = env->GetStaticFieldID(klass(), "theMinecraft", "Lnet/minecraft/client/Minecraft;");
	return env->GetStaticObjectField(klass(), theMinecraftField);
}

jobject c_minecraft::getPlayer()
{
	jobject theMinecraft = getMinecraft();

	jfieldID thePlayerField = env->GetFieldID(klass(), "thePlayer", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
	jobject thePlayer = env->GetObjectField(theMinecraft, thePlayerField);

	env->DeleteLocalRef(theMinecraft);

	return thePlayer;
}

jobject c_minecraft::getAxis()
{
	jobject theMinecraft = getMinecraft();

	jfieldID thePlayerField = env->GetFieldID(klass(), "thePlayer", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
	jobject thePlayer = env->GetObjectField(theMinecraft, thePlayerField);

	env->DeleteLocalRef(theMinecraft);

	return thePlayer;
}

jobject c_minecraft::getWorld()
{
	jobject theMinecraft = getMinecraft();

	jfieldID theWorldField = env->GetFieldID(klass(), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
	jobject theWorld = env->GetObjectField(theMinecraft, theWorldField);

	env->DeleteLocalRef(theMinecraft);

	return theWorld;
} 

jobject c_minecraft::getMovingObject() {

	jobject theMinecraft = getMinecraft();

	jfieldID movingObjectField = env->GetFieldID(klass(), "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	jobject movingObject = env->GetObjectField(theMinecraft, movingObjectField);

	env->DeleteLocalRef(theMinecraft);

	return movingObject;

}

jobject c_minecraft::getGameSettings() {

	jobject theMinecraft = getMinecraft();

	jfieldID gameSettingsField = env->GetFieldID(klass(), "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
	jobject gameSettings = env->GetObjectField(theMinecraft, gameSettingsField);

	env->DeleteLocalRef(theMinecraft);

	return gameSettings;
}

bool c_minecraft::is_in_gui_state() {

	jobject theMinecraft = getMinecraft();

	jfieldID guiStateField = env->GetFieldID(klass(), "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
	if (env->GetObjectField(theMinecraft, guiStateField) != NULL) return true;
	env->DeleteLocalRef(theMinecraft);
	return false;
}

