#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "SDL2\SDL.h"
#include "SDL2\SDL_thread.h"
#include "imgui\imgui.h"
#include "imgui\backends\imgui_impl_sdl.h"

#include "imgui_sdl\imgui_sdl.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

int main(int argc, char* argv[]){
    bool quit = false;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    SDL_Renderer * renderer = NULL;
    SDL_Event event;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }else{
        //Create window
        window = SDL_CreateWindow( "Pixel Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE );
        if( window == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }else{
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( window );

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

            // Fixes #6: https://github.com/Tyyppi77/imgui_sdl/issues/6
            SDL_Rect cliprect;
            cliprect.x = 0;
            cliprect.y = 0;
            cliprect.w = SCREEN_WIDTH;
            cliprect.h = SCREEN_HEIGHT;
            SDL_RenderSetClipRect(renderer,&cliprect);

            //Figure out the rendere we got:
            SDL_RendererInfo render_info;
            SDL_GetRendererInfo(renderer,&render_info);
            printf("render_info.name: %s\n",render_info.name);

             // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGuiContext* ctx =  ImGui::CreateContext();
            printf("ctx= %p\n",ctx);
            ImGuiSDL::Initialize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            ImGui_ImplSDL2_InitForMetal(window);
            ImGui::SetNextWindowPos(ImVec2(20, 20));

            //GUI IO
            ImGuiIO& io = ImGui::GetIO();

            //Wait two seconds
            while (!quit){
                while( SDL_PollEvent(&event) != 0 ){

                    ImGui_ImplSDL2_ProcessEvent(&event);
                    switch (event.type){
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_MOUSEWHEEL:
                            break;
                        case SDL_MOUSEBUTTONUP:
                            {
                                //printf("SDL_MOUSEBUTTONUP event: %hhu\n",event.button);
                            }
                            break;
                        case SDL_WINDOWEVENT:
                            {
                                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                                {
                                    io.DisplaySize.x = static_cast<float>(event.window.data1);
                                    io.DisplaySize.y = static_cast<float>(event.window.data2);
                                }
                            }
                        break;
                    }

                    if (abort){
                        break;
                    }
                }

                {
                    static bool check = false;
                    static int clicked = 0;

                    ImGui::NewFrame();
                    ImGui_ImplSDL2_NewFrame(window);

                     // Using "###" to display a changing title but keep a static identifier "AnimatedTitle"
                    char buf[128];
                    sprintf(buf, "Image frame %c %d###AnimatedTitle", "|/-\\"[(int)(ImGui::GetTime() / 0.25f) & 3], ImGui::GetFrameCount());


                    ImGui::Begin("Settings",NULL,ImGuiWindowFlags_AlwaysAutoResize);
                    {
                        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                        ImGui::SameLine(); HelpMarker("Look! A help marker!");
                    }
                    ImGui::End();

                    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                    SDL_RenderClear(renderer);

                    ImGui::Render();
                    ImGuiSDL::Render(ImGui::GetDrawData());

                    SDL_RenderPresent(renderer);
                }

            }
        }
    }

    //Destroy window
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}