#include "../menu/menu.hpp"
#include "../../vendors/imgui/imgui.h"

#include "../../vendors/imgui/imgui_impl_win32.h"
#include "../../vendors/imgui/imgui_impl_opengl2.h"
#include "../menu/byte_array.hpp"
#include "../menu/keycodes.hpp"
#include "../menu/etc.hpp"
#include "../menu/nav.hpp"

#include "../modules/clicker.hpp"
#include "../modules/aimassist.hpp"
#include "../modules/velocity.hpp"
#include "../sdk/minecraft/minecraft.hpp"

#include <iostream>

#include <gl/GL.h>
#include <mutex>
#include <Shlobj.h>

int tab = 0;

ImFont* medium;
ImFont* bold;
ImFont* tab_icons;
ImFont* logo;
ImFont* tab_title;
ImFont* tab_title_icon;
ImFont* subtab_title;
ImFont* combo_arrow;


enum heads {
	rage, antiaim, visuals, settings, skins, configs, scripts
};
enum sub_heads {
	aim, clicker, velo, reach, _general,
};

int subtab = sub_heads::aim;


const char* tab_name = tab == rage ? "Autoclicker" : tab == antiaim ? "Anti-aim" : tab == visuals ? "Visuals" : tab == settings ? "Settings" : tab == skins ? "Skins" : tab == configs ? "Configs" : tab == scripts ? "Scripts" : 0;
const char* tab_icon = tab == rage ? "B" : tab == antiaim ? "C" : tab == visuals ? "D" : tab == settings ? "E" : tab == skins ? "F" : tab == configs ? "G" : tab == scripts ? "H" : 0;

std::once_flag setupFlag;
std::atomic_flag clipCursor = ATOMIC_FLAG_INIT;
RECT originalClip;

typedef bool(__stdcall* template_wglSwapBuffers) (HDC hdc);
template_wglSwapBuffers original_wglSwapBuffers;
bool __stdcall hook_wglSwapBuffers(_In_ HDC hdc) {

	menu::HandleWindow = WindowFromDC(hdc);

	HWND mcWindow = FindWindow(L"LWJGL", nullptr);
	RECT windowRect;
	GetWindowRect(mcWindow, &windowRect);

	std::call_once(setupFlag, [&]() {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImFontConfig font_config;
		font_config.PixelSnapH = false;
		font_config.OversampleH = 5;
		font_config.OversampleV = 5;
		font_config.RasterizerMultiply = 1.2f;

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0xE000, 0xE226, // icons
			0,
		};

		font_config.GlyphRanges = ranges;
		medium = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 15.0f, &font_config, ranges);
		bold = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

		tab_icons = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 15.0f, &font_config, ranges);
		logo = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 21.0f, &font_config, ranges);

		tab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 19.0f, &font_config, ranges);
		tab_title_icon = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 18.0f, &font_config, ranges);

		subtab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

		combo_arrow = io.Fonts->AddFontFromMemoryTTF(combo, sizeof(combo), 9.0f, &font_config, ranges);

		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(menu::HandleWindow);
		ImGui_ImplOpenGL2_Init();
		menu::init = true;
		return original_wglSwapBuffers(hdc);
		});



	ImGuiIO& io = ImGui::GetIO();


	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();


	ImGui::SetNextWindowPos(ImVec2(200, 200));


	if (menu::is_open) {
		ImGui::NewFrame();

		ImGui::SetNextWindowSize({ (float)730, (float)460 }, ImGuiCond_Once);
		ImGui::SetNextWindowPos({ 200, 200 }, ImGuiCond_Once);
		ImGui::Begin("hi world", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar); {
		
			auto draw = ImGui::GetWindowDrawList();
			auto pos = ImGui::GetWindowPos();
			auto size = ImGui::GetWindowSize();

			ImGuiStyle style = ImGui::GetStyle();

			draw->AddRectFilled(pos, ImVec2(pos.x + 210, pos.y + size.y), ImColor(24, 24, 26), style.WindowRounding, ImDrawFlags_RoundCornersLeft);
			draw->AddLine(ImVec2(pos.x + 210, pos.y + 2), ImVec2(pos.x + 210, pos.y + size.y - 2), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddLine(ImVec2(pos.x + 47, pos.y + 2), ImVec2(pos.x + 47, pos.y + size.y - 2), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddLine(ImVec2(pos.x + 2, pos.y + 47), ImVec2(pos.x + 47, pos.y + 47), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddLine(ImVec2(pos.x + 63, pos.y + 47), ImVec2(pos.x + 195, pos.y + 47), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
			draw->AddText(logo, 21.0f, ImVec2(pos.x + 14, pos.y + 12), ImColor(menu::main_color[0], menu::main_color[1], menu::main_color[2]), "A");

			draw->AddText(tab_title_icon, 18.0f, ImVec2(pos.x + 65, pos.y + 14), ImColor(menu::main_color[0], menu::main_color[1], menu::main_color[2]), tab_icon);
			draw->AddText(tab_title, 19.0f, ImVec2(pos.x + 93, pos.y + 15), ImColor(1.0f, 1.0f, 1.0f), tab_name);

			draw->AddRect(pos + ImVec2(1, 1), pos + size - ImVec2(1, 1), ImColor(1.0f, 1.0f, 1.0f, 0.03f), style.WindowRounding);

			ImGui::SetCursorPos({ 8, 56 });
			ImGui::BeginGroup(); {
				if (elements::tab("B", tab == rage)) { tab = rage; }
				if (elements::tab("E", tab == settings)) { tab = settings; }
			} ImGui::EndGroup();


			switch (tab) {
			case rage:
				draw->AddText(subtab_title, 15.0f, ImVec2(pos.x + 72, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.4f), "COMBAT");

				ImGui::SetCursorPos({ 57, 86 });
				ImGui::BeginGroup(); {
					if (elements::subtab("Autoclicker", subtab == clicker)) { subtab = clicker; }
					if (elements::subtab("Aim-Assist", subtab == aim)) { subtab = aim; }
					if (elements::subtab("Velocity", subtab == velo)) { subtab = velo; }
					if (elements::subtab("Reach", subtab == reach)) { subtab = reach; }
				} ImGui::EndGroup();

				switch (subtab) {
				case clicker:
					ImGui::SetCursorPos({ 226, 16 });
					e_elements::begin_child("Left Clicker", ImVec2(240, 430)); {
						ImGui::Checkbox("Enabled", &aclicker::toggled, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::Checkbox("Randomized", &aclicker::randomized, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::Checkbox("Sword-Only", &aclicker::sword_only, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::SliderInt("CPS", &aclicker::cps, 0, 20, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);

						//ImGui::Text("Clicker keybind");
						//keybind_button(aclicker::left_clicker_key, 200, 30);


					}
					e_elements::end_child();
					ImGui::SetCursorPos({ 476, 16 });
					e_elements::begin_child("Right Clicker", ImVec2(240, 430)); {
						ImGui::Checkbox("Enabled", &aclicker::toggled_right, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::Checkbox("Randomized", &aclicker::randomized_right, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::Checkbox("Blocks-Only", &aclicker::blocks_only, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::SliderInt("CPS", &aclicker::cps_right, 0, 20, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);


					}
					e_elements::end_child();

					break;
				case aim:
					ImGui::SetCursorPos({ 226, 16 });
					e_elements::begin_child("Aim", ImVec2(240, 430)); {
						ImGui::Checkbox("Enabled", &aimassist::enabled, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						//ImGui::SliderFloat("Distance", &distance_float, 3, 6, "%d%Distance", ImGuiSliderFlags_None);
						ImGui::SliderInt("FOV", &aimassist::fov, 10, 180, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::Checkbox("Draw FOV Circle", &aimassist::draw_fov, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::SliderInt("Speed", &aimassist::speed, 1, 10, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
					}
					e_elements::end_child();
					break;
				case velo:
					ImGui::SetCursorPos({ 226, 16 });
					e_elements::begin_child("Velocity", ImVec2(240, 430)); {
						ImGui::Checkbox("Enabled", &velocity::enabled, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::SliderInt("Horizontal", &velocity::horizontal, 0, 100, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::SliderInt("Vertical", &velocity::vertical, 0, 100, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::Checkbox("Air Only", &velocity::air_only, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::Checkbox("While Moving Only", &velocity::moving, menu::main_color[0], menu::main_color[1], menu::main_color[2]);

						ImGui::SliderInt("Tick Delay", &velocity::delay, 0, 20, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						ImGui::SliderInt("Velocity Chance", &velocity::chance, 0, 100, "%d%", ImGuiSliderFlags_None, menu::main_color[0], menu::main_color[1], menu::main_color[2]);


					}
					e_elements::end_child();
					break;
				case reach:
					ImGui::SetCursorPos({ 226, 16 });
					e_elements::begin_child("Reach", ImVec2(240, 430)); {
						ImGui::Checkbox("Enabled", &velocity::enabled, menu::main_color[0], menu::main_color[1], menu::main_color[2]);
						//ImGui::SliderFloat("Distance", &distance_float, 3, 6, "%d%Distance", ImGuiSliderFlags_None);
					}
					e_elements::end_child();
					break;
				}
				break;
			case settings:
				subtab = _general;
				draw->AddText(subtab_title, 15.0f, ImVec2(pos.x + 72, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.4f), "SETTINGS");

				ImGui::SetCursorPos({ 57, 86 });
				ImGui::BeginGroup(); {
					if (elements::subtab("General", subtab == _general)) { subtab = _general; }
				} ImGui::EndGroup();
				switch (subtab) {
				case _general:
					ImGui::SetCursorPos({ 226, 16 });
					e_elements::begin_child("Settings", ImVec2(240, 430)); {
						ImGui::ColorPicker4("Main Color", menu::main_color);
						//ImGui::Checkbox("Rainbow Mode", &rainbow, main_color[0], main_color[1], main_color[2]);

						if (ImGui::Button("Uninject", ImVec2(200, 30))) {
							SendMessageW(GetForegroundWindow(), WM_KEYDOWN, VK_ESCAPE, 0);
							SendMessageW(GetForegroundWindow(), WM_KEYUP, VK_ESCAPE, 0);
							menu::injected = false;

						}

					}
					e_elements::end_child();

					ImGui::SetCursorPos({ 476, 16 });
					e_elements::begin_child("Keybinds", ImVec2(240, 430)); {
						ImGui::Text("Open Menu Keybind");
						//keybind_button(menu_key, 201, 30);

					}
					e_elements::end_child();

					break;
				}
			}
		
		}
		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
	if (!menu::is_open && aimassist::draw_fov) {
		ImGui::NewFrame();

		ImGui::SetNextWindowSize({ (float)730, (float)460 }, ImGuiCond_Once);
		ImGui::SetNextWindowPos({ 200, 200 }, ImGuiCond_Once);
		ImGui::Begin("overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
		ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
		
		aimassist::draw();

		ImGui::End();
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
	return original_wglSwapBuffers(hdc);
}

void menu::Hook_wglSwapBuffers()
{
	LPVOID wglSwapBuffers = (LPVOID)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
	MH_CreateHook(wglSwapBuffers, (LPVOID)hook_wglSwapBuffers, (LPVOID*)&original_wglSwapBuffers);
	MH_EnableHook(wglSwapBuffers);
}

void menu::Unhook_wglSwapBuffers()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
}