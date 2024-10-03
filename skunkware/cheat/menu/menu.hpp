#include <windows.h>
#include "../../vendors/minhook/MinHook.h"
#include "../../vendors/imgui/imgui.h"

namespace menu
{
	inline bool is_open = true;
	inline bool init = false;

	inline bool injected = true;


	inline float main_color[3] = { 255.f / 255, 0.0f / 255, 30.f / 255 };//255, 0, 30

	static inline HWND HandleWindow;
	static inline HDC HandleDeviceContext;

	static inline HGLRC OriginalGLContext;
	static inline HGLRC MenuGLContext;

	static inline ImGuiContext* CurrentImGuiContext;

	void place_hooks();
	void remove_hooks();

	void Hook_wglSwapBuffers();
	void Hook_wndProc();

	void Unhook_wglSwapBuffers();
	void Unhook_wndProc();
};