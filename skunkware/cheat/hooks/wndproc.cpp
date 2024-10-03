#include "../menu/menu.hpp"

#include "../../vendors/imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* template_WndProc) (HWND, UINT, WPARAM, LPARAM);
template_WndProc original_wndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		if (wParam == VK_INSERT)
			menu::is_open = !menu::is_open;
		if (wParam == VK_ESCAPE && menu::is_open)
			menu::is_open = false;
	}

	if (menu::is_open && menu::init)
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProc(original_wndProc, hwnd, msg, wParam, lParam);
}

void menu::Hook_wndProc()
{
	original_wndProc = (template_WndProc)SetWindowLongPtrA(FindWindow(L"LWJGL", nullptr), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hook_WndProc));
}

void menu::Unhook_wndProc()
{
	SetWindowLongPtr(FindWindow(L"LWJGL", nullptr), GWLP_WNDPROC, (LONG_PTR)original_wndProc);
}