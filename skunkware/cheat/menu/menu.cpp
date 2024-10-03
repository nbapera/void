#include "menu.hpp"

void menu::place_hooks() {
	MH_Initialize();
	menu::Hook_wndProc();
	menu::Hook_wglSwapBuffers();
}

void menu::remove_hooks() {
	menu::Unhook_wglSwapBuffers();
	menu::Unhook_wndProc();
}