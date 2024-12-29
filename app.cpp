#if defined(__APPLE__)
#define SOKOL_METAL
#elif defined(_WIN32)
#define SOKOL_D3D11
#else
#define SOKOL_DUMMY_BACKEND
#endif

#include "cimgui.h"
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_imgui.h"
#include "sokol_log.h"

static const char* APP_NAME = (char*)"App";

static struct
{
    sg_pass_action pass_action;
} state;

static void init(void)
{
    sg_desc desc = {
        .environment = sglue_environment(),
        .logger.func = slog_func,
    };
    sg_setup(&desc);

    simgui_desc_t imgui_desc{0};
    simgui_setup(&imgui_desc);

    // initial clear color
    state.pass_action = (sg_pass_action){
        .colors[0] = {.load_action = SG_LOADACTION_CLEAR, .clear_value = {0.0f, 0.5f, 1.0f, 1.0}}};
}

static void draw_ui(void)
{
    igSetNextWindowPos((ImVec2){10, 10}, ImGuiCond_Once);
    igSetNextWindowSize((ImVec2){400, 100}, ImGuiCond_Once);
    igBegin("Dear Imgui!", 0, ImGuiWindowFlags_None);
    igColorEdit3("Background", &state.pass_action.colors[0].clear_value.r, ImGuiColorEditFlags_None);
    igEnd();
}

static void frame(void)
{
    simgui_frame_desc_t frame_desc{
        .width = sapp_width(),
        .height = sapp_height(),
        .delta_time = sapp_frame_duration(),
        .dpi_scale = sapp_dpi_scale(),
    };
    simgui_new_frame(&frame_desc);

    draw_ui();

    sg_pass pass_desc = {
        .action = state.pass_action,
        .swapchain = sglue_swapchain(),
    };

    sg_begin_pass(&pass_desc);
    simgui_render();
    sg_end_pass();
    sg_commit();
}

static void cleanup(void)
{
    simgui_shutdown();
    sg_shutdown();
}

static void event(const sapp_event* ev)
{
    simgui_handle_event(ev);
}

sapp_desc sokol_main(int argc, char** argv)
{
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = event,
        .window_title = APP_NAME,
        .width = 800,
        .height = 600,
        .icon.sokol_default = true,
        .logger.func = slog_func,
    };
}
