#include "encode_window.hpp"

#include <vector>
#include <xsteg/availability_map.hpp>

#include "threshold_editor.hpp"

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
    #include <Windows.h>
    #include <commdlg.h>

    std::string openfile_diag(window* wnd)
    {
        std::string result(512, 0);
        OPENFILENAMEA fdata;
        ZeroMemory(&fdata, sizeof(OPENFILENAMEA));
        fdata.lStructSize = sizeof(OPENFILENAMEA);
        fdata.hwndOwner = glfwGetWin32Window(wnd->wnd_ptr());
        fdata.lpstrFile = result.data();
        fdata.nMaxFile = result.size();
        fdata.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        GetOpenFileNameA(&fdata);
        return result;
    }
#endif

encode_window::encode_window(window* wnd, const std::string& name)
    : imgui_window(wnd, name)
{ }

encode_window::encode_window(window* wnd, std::string&& name)
    : imgui_window(wnd, std::move(name))
{ }

void encode_window::show()
{
    imgui_window::show();
    _first_time = true;
}

void encode_window::update_proc()
{
    static bool btn_browse_input = false;
    static bool btn_browse_output = false;
    static bool btn_browse_data = false;
    static bool btn_edit_thresh = false;
    static threshold_editor th_editor;
    
    /*if(_first_time)
    {
        auto [x, y] = _wnd->get_window_size();
        float win_x = static_cast<float>(x * 0.50);
        float win_y = static_cast<float>(y * 0.60);
        ImGui::SetWindowSize(ImVec2(win_x, win_y));
    }*/
    
    // **** Input image path ****
    ImGui::InputTextWithHint("##ii", "Input image path", _input_image.data(), _input_image.size() + 1);    
#ifdef _WIN32
    ImGui::SameLine();
    btn_browse_input = ImGui::Button("Browse...");
    if(btn_browse_input) { _input_image = openfile_diag(_wnd); }
#endif

    // **** Output image path ****
    ImGui::InputTextWithHint("##oi", "Output image path", _output_image.data(), _output_image.size() + 1);
#ifdef _WIN32
    ImGui::SameLine();
    btn_browse_output = ImGui::Button("Browse...");
#endif

    // **** Input data file ****
    ImGui::InputTextWithHint("##df", "Input data file", _input_data.data(), _input_data.size() + 1);
#ifdef _WIN32
    ImGui::SameLine();
    btn_browse_data = ImGui::Button("Browse...");
#endif

    ImGui::Separator();
    ImGui::Spacing();

    // **** Threshold editor ****
    ImGui::Text("Thresholds: (%d)", th_editor.threshold_count());

    th_editor.update();

    ImGui::Button("Generate key");
    ImGui::SameLine();
    ImGui::Button("Restore key");
    ImGui::Separator();

    ImGui::Button("Encode!");
}