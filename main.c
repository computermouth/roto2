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
		
        {
            /* menubar */
            enum menu_states {MENU_DEFAULT, MENU_WINDOWS};
            static nk_size mprog = 60;
            static int mslider = 10;
            static int mcheck = nk_true;
            nk_menubar_begin(ctx);

            /* menu #1 */
            nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
            nk_layout_row_push(ctx, 45);
            if (nk_menu_begin_label(ctx, "MENU", NK_TEXT_LEFT, nk_vec2(200, 600)))
            {
                enum menu_state {MENU_NONE,MENU_FILE, MENU_EDIT,MENU_VIEW,MENU_CHART};
                static enum menu_state menu_state = MENU_NONE;
                enum nk_collapse_states state;

                state = (menu_state == MENU_FILE) ? NK_MAXIMIZED: NK_MINIMIZED;
                if (nk_tree_state_push(ctx, NK_TREE_TAB, "FILE", &state)) {
                    menu_state = MENU_FILE;
                    nk_menu_item_label(ctx, "New", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Open", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Save", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Close", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT);
                    nk_tree_pop(ctx);
                } else menu_state = (menu_state == MENU_FILE) ? MENU_NONE: menu_state;

                state = (menu_state == MENU_EDIT) ? NK_MAXIMIZED: NK_MINIMIZED;
                if (nk_tree_state_push(ctx, NK_TREE_TAB, "EDIT", &state)) {
                    menu_state = MENU_EDIT;
                    nk_menu_item_label(ctx, "Copy", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Delete", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Cut", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Paste", NK_TEXT_LEFT);
                    nk_tree_pop(ctx);
                } else menu_state = (menu_state == MENU_EDIT) ? MENU_NONE: menu_state;

                state = (menu_state == MENU_VIEW) ? NK_MAXIMIZED: NK_MINIMIZED;
                if (nk_tree_state_push(ctx, NK_TREE_TAB, "VIEW", &state)) {
                    menu_state = MENU_VIEW;
                    nk_menu_item_label(ctx, "About", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Options", NK_TEXT_LEFT);
                    nk_menu_item_label(ctx, "Customize", NK_TEXT_LEFT);
                    nk_tree_pop(ctx);
                } else menu_state = (menu_state == MENU_VIEW) ? MENU_NONE: menu_state;
                nk_menu_end(ctx);
            }
            /* menu widgets */
            nk_layout_row_push(ctx, 70);
            nk_progress(ctx, &mprog, 100, NK_MODIFIABLE);
            nk_slider_int(ctx, 0, &mslider, 16, 1);
            nk_checkbox_label(ctx, "check", &mcheck);
            nk_menubar_end(ctx);
        }

        if (show_app_about)
        {
            /* about popup */
            static struct nk_rect s = {20, 100, 300, 190};
            if (nk_popup_begin(ctx, NK_POPUP_STATIC, "About", NK_WINDOW_CLOSABLE, s))
            {
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, "Nuklear", NK_TEXT_LEFT);
                nk_label(ctx, "By Micha Mettke", NK_TEXT_LEFT);
                nk_label(ctx, "nuklear is licensed under the public domain License.",  NK_TEXT_LEFT);
                nk_popup_end(ctx);
            } else show_app_about = nk_false;
        }
		
		// left trays
		nk_layout_space_begin(ctx, NK_STATIC, 0, INT_MAX); // INT_MAX for maximum rows
		nk_layout_space_push(ctx, nk_rect(0,0,470,window_bounds.h - 43));
		if (nk_group_begin(ctx, "LeftTray", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, window_bounds.h - 53, 3);	
			
			//~ nk_button_label(ctx, "ANIMATIONS");
			
			
			
			// animations start
			//~ nk_layout_space_begin(ctx, NK_STATIC, 0, INT_MAX);
			nk_layout_space_push(ctx, nk_rect(0,0,150,30));
			if (nk_group_begin(ctx, "AnimTop", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
				nk_layout_row_dynamic(ctx, 0, 1);
				
				// label
				nk_label(ctx, "ANIMATIONS", NK_TEXT_LEFT);
				
				// controls
				//~ nk_layout_space_begin(ctx, NK_STATIC, 0, INT_MAX);
				nk_layout_space_push(ctx, nk_rect(0,0,150,30));
				if (nk_group_begin(ctx, "AnimControl", NK_WINDOW_NO_SCROLLBAR)) {
					nk_layout_row_dynamic(ctx, 25, 5);
					nk_button_label(ctx, "+");
					nk_button_label(ctx, "t");
					nk_button_label(ctx, "u");
					nk_button_label(ctx, "d");
					nk_button_label(ctx, "b");					
					nk_group_end(ctx);
				}
				//~ nk_layout_space_end(ctx);
				
				// tray
				//~ nk_layout_space_begin(ctx, NK_STATIC, 0, INT_MAX);
				nk_layout_space_push(ctx, nk_rect(0,50,50,300));
				if (nk_group_begin(ctx, "Animations", NK_WINDOW_BORDER)) {
					nk_layout_row_dynamic(ctx, 25, 1);
					nk_button_label(ctx, "#FFAA");
					nk_button_label(ctx, "#FFBB");
					nk_button_label(ctx, "#FFCC");
					nk_button_label(ctx, "#FFDD");
					nk_button_label(ctx, "#FFEE");
					nk_button_label(ctx, "#FFAA");
					nk_button_label(ctx, "#FFBB");
					nk_button_label(ctx, "#FFCC");
					nk_button_label(ctx, "#FFDD");
					nk_button_label(ctx, "#FFEE");
					nk_button_label(ctx, "#FFAA");
					nk_button_label(ctx, "#FFBB");
					nk_button_label(ctx, "#FFCC");
					nk_button_label(ctx, "#FFDD");
					nk_button_label(ctx, "#FFEE");
					nk_button_label(ctx, "#FFAA");
					nk_button_label(ctx, "#FFBB");
					nk_button_label(ctx, "#FFCC");
					nk_button_label(ctx, "#FFDD");
					nk_button_label(ctx, "#FFEE");
					nk_button_label(ctx, "#FFAA");
					nk_button_label(ctx, "#FFBB");
					nk_button_label(ctx, "#FFCC");
					nk_button_label(ctx, "#FFDD");
					nk_button_label(ctx, "#FFEE");
					nk_group_end(ctx);
				}
				//~ nk_layout_space_end(ctx);
				
				nk_group_end(ctx);
			}
			//~ nk_layout_space_end(ctx);
			// animations start
			// animations end
			nk_button_label(ctx, "FRAMES");
			nk_button_label(ctx, "LAYERS");
			
			
			nk_group_end(ctx);
		}
		// left trays end
		
		// canvas
		nk_layout_space_push(ctx, nk_rect(480,0,window_bounds.w - 480 - 80 ,window_bounds.h - 43));
		if (nk_group_begin(ctx, "Canvas", NK_WINDOW_BORDER)) {
			nk_layout_row_dynamic(ctx, 25, 1);
			nk_button_label(ctx, "rem");
			nk_group_end(ctx);
		}
		// canvas end
		
		// right tools
		nk_layout_space_push(ctx, nk_rect(window_bounds.w - 70,0,55,window_bounds.h - 43));
		if (nk_group_begin(ctx, "Layers", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, 25, 1);
			nk_button_label(ctx, "add");
			nk_button_label(ctx, "rem");
			nk_button_label(ctx, "mov");
			nk_button_label(ctx, "zm+");
			nk_button_label(ctx, "zm-");
			nk_button_label(ctx, "zm1");
			nk_group_end(ctx);
		}
		// right tool end
		
		//~ nk_layout_space_push(ctx, nk_rect(0,0,150,window_bounds.h - 43));
		//~ if (nk_group_begin(ctx, "Animations2", NK_WINDOW_BORDER)) {
			//~ nk_layout_row_dynamic(ctx, 25, 1);
			//~ nk_label(ctx, "ANIMATIONS", NK_TEXT_LEFT);
			//~ nk_button_label(ctx, "#FFAA");
			//~ nk_button_label(ctx, "#FFBB");
			//~ nk_button_label(ctx, "#FFCC");
			//~ nk_button_label(ctx, "#FFDD");
			//~ nk_button_label(ctx, "#FFEE");
			//~ nk_group_end(ctx);
		//~ }
		//~ nk_layout_space_end(ctx);
		
		nk_layout_space_end(ctx);


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

