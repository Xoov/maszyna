#include "stdafx.h"
#include "launcher/launcheruilayer.h"
#include "application.h"

launcher_ui::launcher_ui()
{
	add_external_panel(&m_scenerylist_panel);
	add_external_panel(&m_keymapper_panel);
	add_external_panel(&m_vehiclepicker_panel);
}

bool launcher_ui::on_key(const int Key, const int Action)
{
	if (m_keymapper_panel.key(Key))
		return true;

	return ui_layer::on_key(Key, Action);
}

void launcher_ui::render_()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;
	ImVec2 display_size = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowPos(ImVec2(display_size.x * 0.66f, display_size.y / 2.0f));
	ImGui::SetNextWindowSize(ImVec2(200, -1));

	if (ImGui::Begin(STR_C("Main menu"), nullptr, flags)) {
		if (ImGui::Button(STR_C("Scenario list"), ImVec2(-1, 0)))
			m_scenerylist_panel.is_open = !m_scenerylist_panel.is_open;
		if (ImGui::Button(STR_C("Vehicle list"), ImVec2(-1, 0)))
			m_vehiclepicker_panel.is_open = !m_vehiclepicker_panel.is_open;
		if (ImGui::Button(STR_C("Keymapper"), ImVec2(-1, 0)))
			m_keymapper_panel.is_open = !m_keymapper_panel.is_open;
		if (ImGui::Button(STR_C("Quit"), ImVec2(-1, 0)))
			Application.queue_quit();
	}
	ImGui::End();
}