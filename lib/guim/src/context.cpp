#include <guim/context.hpp>
#include <guim/appwindow.hpp>

namespace guim
{
    context::context(appwindow* wnd)
    {
        _wnd = wnd;

        const std::string glsl_version = "#version 130";

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        _io = &ImGui::GetIO();

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(_wnd->wnd_ptr(), true);
        ImGui_ImplOpenGL3_Init(glsl_version.c_str());

        _bg_color = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
    }

    void context::set_background_color(ImVec4 color)
    {
        _bg_color = color;
    }

    void context::start(std::function<void(void)> main_loop)
    {
        while (!_wnd->should_close())
        {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            main_loop();

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(_wnd->wnd_ptr(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(_bg_color.x, _bg_color.y, _bg_color.z, _bg_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(_wnd->wnd_ptr());
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(_wnd->wnd_ptr());
        glfwTerminate();
    }
}