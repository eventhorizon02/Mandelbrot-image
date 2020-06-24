
#include <iostream>
#include "mandel.h"


float getDeltaTime();
void processEvents();

 //Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void closeAll();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning = true;
camera* cam = nullptr;


int main()
{
   if (!init())
   {
       printf("initialization failed\n");
       closeAll();
       return 0;
   }
    
    // number of clicks is half screen size and intial zoom is 0.005
    cam = new camera(SCREEN_SIZE / 2 , 0.005); 
    update_buffer(cam);
    render(renderer, cam);
    while(isRunning)
    {
        processEvents();
    }
    
    closeAll();
    return 0;
}

// initialize window and renderer. and keyboard state
bool init()
{
  isRunning = true;
  bool success = true;
  SDL_Init(SDL_INIT_VIDEO);
  window=SDL_CreateWindow("Mendelbrut image",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_SIZE,SCREEN_SIZE, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

  return success;
}

// free everyting
void closeAll()
{
  //Destroy window
    SDL_DestroyWindow( window);
    window = NULL;
    SDL_DestroyRenderer( renderer );
  renderer = NULL;
//Quit SDL subsystems
   SDL_Quit();
}

void processEvents()
{
  SDL_Event e;
  
  while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            isRunning = false;
        
        if (e.type == SDL_KEYUP)
            {
              if ((e.key.keysym.sym) == SDLK_SPACE) // zoom in
               {
                  cam->m_zoom *= 0.5;
                  cam->update(cam->m_centerX, cam->m_centerY, cam->m_zoom);
                  zoom(cam);
               }

              else if ((e.key.keysym.sym) == SDLK_RETURN) // zoom out
               {
                  cam->m_zoom *= 2.0;
                  cam->update(cam->m_centerX, cam->m_centerY, cam->m_zoom);
                  zoom(cam);
               }

                  render(renderer, cam);
            }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) 
    {
        cam->m_centerX -= cam->m_zoom;
        cam->update(cam->m_centerX, cam->m_centerY, cam->m_zoom);
        scroll_left(cam);
        render(renderer, cam);
    }
   else if (state[SDL_SCANCODE_RIGHT]) 
   {
       cam->m_centerX += cam->m_zoom;
       cam->update(cam->m_centerX, cam->m_centerY, cam->m_zoom);
        scroll_right(cam);
        render(renderer, cam);
   }
   else if(state[SDL_SCANCODE_UP])
   {
        cam->m_centerY -= cam->m_zoom;
        cam->update(cam->m_centerX, cam->m_centerY, cam->m_zoom);
        scroll_up(cam);
        render(renderer, cam);
   }
   else if (state[SDL_SCANCODE_DOWN])
   {
       cam->m_centerY += cam->m_zoom;
       cam->update(cam->m_centerX, cam->m_centerY, cam->m_zoom);
       scroll_down(cam);
       render(renderer, cam);
   }
}



