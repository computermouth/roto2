/* nuklear - 1.32.0 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_gl2.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

static int
editor(struct nk_context *ctx)
{
    /* window flags */
    //~ static int titlebar = nk_false;
    //~ static int border = nk_true;
    static nk_flags window_flags = 0;
    ctx->style.window.header.align = NK_HEADER_RIGHT;
    window_flags |= NK_WINDOW_SCALABLE;
    window_flags |= NK_WINDOW_NO_SCROLLBAR;

    /* popups */
    static int show_app_about = nk_false;
	
	// fill the sdl window with the nk_window
	int sdl_width, sdl_height;
	SDL_GetWindowSize(sdl.win, &sdl_width, &sdl_height);
	static struct nk_rect window_bounds;
	window_bounds = nk_rect(0, 0, sdl_width, sdl_height);
	
	static int window = nk_false;
	if (window == nk_true)
		nk_window_set_bounds(ctx, "Overview", window_bounds);

    if (window = nk_begin(ctx, "Overview", window_bounds, window_flags))
    {
		
		float menu_h = 25;
		
        {
            /* menubar */
            nk_menubar_begin(ctx);

            /* menu #1 */
            nk_layout_row_static(ctx, menu_h, 40, 4);
            if (nk_menu_begin_label(ctx, "FILE", NK_TEXT_LEFT, nk_vec2(200, 200)))
            {
				nk_layout_row_dynamic(ctx, 20, 1);
				nk_menu_item_label(ctx, "New", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Open", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Save", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Close", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT);
                nk_menu_end(ctx);
            }
            if (nk_menu_begin_label(ctx, "EDIT", NK_TEXT_LEFT, nk_vec2(200, 200)))
            {
				nk_layout_row_dynamic(ctx, 20, 1);
				nk_menu_item_label(ctx, "Copy", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Delete", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Cut", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Paste", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Preferences", NK_TEXT_LEFT);
                nk_menu_end(ctx);
            }
            if (nk_menu_begin_label(ctx, "PLAY", NK_TEXT_LEFT, nk_vec2(200, 200)))
            {
				nk_layout_row_dynamic(ctx, 20, 1);
				nk_menu_item_label(ctx, "Play", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Play 2x", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Play 0.5x", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Stop", NK_TEXT_LEFT);
                nk_menu_end(ctx);
            }
            if (nk_menu_begin_label(ctx, "HELP", NK_TEXT_LEFT, nk_vec2(200, 200)))
            {
				nk_layout_row_dynamic(ctx, 20, 1);
				nk_menu_item_label(ctx, "About", NK_TEXT_LEFT);
                nk_menu_end(ctx);
            }
            nk_menubar_end(ctx);
        }
		
		
		// widths
		float wpad_w = 4;
		float try0_w = 150;
		float try2_w = try0_w + try0_w / 5;
		float tool_w = 55;
		float canv_w = sdl_width - (try0_w * 2 + try2_w + tool_w + wpad_w * 6);
		
		// heights
		float hpad_h = 4;
		float bpad_h = 10 + hpad_h;
		float topl_h = sdl_height - bpad_h - menu_h - hpad_h;
		
		float tray_h = topl_h - ( 3 + (25 * 3) + (hpad_h * 4));
		
		float widths[] = {try0_w, try0_w, try2_w, canv_w, tool_w};
		nk_layout_row(ctx, NK_STATIC, topl_h, sizeof(widths)/sizeof(widths[0]), widths);
		
		if (nk_group_begin(ctx, "Animations", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, 25, 1);
			nk_label(ctx, "ANIMATIONS", NK_TEXT_CENTERED);
			nk_layout_row_dynamic(ctx, 25, 5);
			nk_button_label(ctx, "+");
			nk_button_label(ctx, "t");
			nk_button_label(ctx, "u");
			nk_button_label(ctx, "d");
			nk_button_label(ctx, "b");
			
			nk_layout_row_dynamic(ctx, tray_h, 1);			
			if (nk_group_begin(ctx, "AnimTray", NK_WINDOW_BORDER)) {
				nk_button_label(ctx, "+");
				nk_group_end(ctx);
			}
			
			nk_layout_row_dynamic(ctx, 25, 3);
			nk_label(ctx, "0", NK_TEXT_CENTERED);
			nk_label(ctx, "/", NK_TEXT_CENTERED);
			nk_label(ctx, "0", NK_TEXT_CENTERED);
			
			nk_group_end(ctx);
		}
		if (nk_group_begin(ctx, "Frames", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, 25, 1);
			nk_label(ctx, "FRAMES", NK_TEXT_CENTERED);
			nk_layout_row_dynamic(ctx, 25, 5);
			nk_button_label(ctx, "+");
			nk_button_label(ctx, "t");
			nk_button_label(ctx, "u");
			nk_button_label(ctx, "d");
			nk_button_label(ctx, "b");
			
			nk_layout_row_dynamic(ctx, tray_h, 1);			
			if (nk_group_begin(ctx, "FrameTray", NK_WINDOW_BORDER)) {
				nk_button_label(ctx, "+");
				nk_group_end(ctx);
			}
			
			nk_layout_row_dynamic(ctx, 25, 3);
			nk_label(ctx, "0", NK_TEXT_CENTERED);
			nk_label(ctx, "/", NK_TEXT_CENTERED);
			nk_label(ctx, "0", NK_TEXT_CENTERED);
			nk_group_end(ctx);
		}
		if (nk_group_begin(ctx, "Layers", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, 25, 1);
			nk_label(ctx, "LAYERS", NK_TEXT_CENTERED);
			nk_layout_row_dynamic(ctx, 25, 6);
			nk_button_label(ctx, "+");
			nk_button_label(ctx, "i");
			nk_button_label(ctx, "t");
			nk_button_label(ctx, "u");
			nk_button_label(ctx, "d");
			nk_button_label(ctx, "b");
			
			nk_layout_row_dynamic(ctx, tray_h, 1);			
			if (nk_group_begin(ctx, "LayerTray", NK_WINDOW_BORDER)) {
				nk_button_label(ctx, "+");
				nk_group_end(ctx);
			}
			
			nk_layout_row_dynamic(ctx, 25, 3);
			nk_label(ctx, "0", NK_TEXT_CENTERED);
			nk_label(ctx, "/", NK_TEXT_CENTERED);
			nk_label(ctx, "0", NK_TEXT_CENTERED);
			nk_group_end(ctx);
		}
		if (nk_group_begin(ctx, "Canvas", NK_WINDOW_BORDER)) {
			nk_group_end(ctx);
		}
		if (nk_group_begin(ctx, "Tools", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, 25, 1);
			nk_label(ctx, "tool", NK_TEXT_CENTERED);
			nk_button_label(ctx, "add");
			nk_button_label(ctx, "rem");
			nk_button_label(ctx, "mov");
			nk_label(ctx, "zoom", NK_TEXT_CENTERED);
			nk_button_label(ctx, "zm+");
			nk_button_label(ctx, "zm-");
			nk_button_label(ctx, "zm1");
			nk_group_end(ctx);
		}


    }
    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Overview");
}

int
main(int argc, char *argv[])
{
    /* Platform */
    SDL_Window *win;
    SDL_GLContext glContext;
    int win_width, win_height;
    int running = 1;

    /* GUI */
    struct nk_context *ctx;
    struct nk_colorf bg;

    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    win = SDL_CreateWindow("roto2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_RESIZABLE);
    glContext = SDL_GL_CreateContext(win);
    SDL_GetWindowSize(win, &win_width, &win_height);

    ctx = nk_sdl_init(win);
    {
		struct nk_font_atlas *atlas;
		nk_sdl_font_stash_begin(&atlas);
		nk_sdl_font_stash_end();
    }

    bg.r = 0.7f, bg.g = 0.0f, bg.b = 0.176f, bg.a = 1.0f;
    while (running)
    {
        /* Input */
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) goto cleanup;
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        editor(ctx);

        /* Draw */
        SDL_GetWindowSize(win, &win_width, &win_height);
        glViewport(0, 0, win_width, win_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_sdl_render(NK_ANTI_ALIASING_ON);
        SDL_GL_SwapWindow(win);
    }

cleanup:
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

