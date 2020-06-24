
#include "mandel.h"
#include <complex>      // std::complex
#define MAX_ITER 1000 // max iteration per complex point

int buffer[SCREEN_SIZE][SCREEN_SIZE];
// 'clicks' is how many units from the center in each direction
camera::camera(const short clicks, const float128_t zoom):
m_centerX(0),
m_centerY(0),
m_left(-clicks * zoom),
m_top(-clicks * zoom),
m_right(clicks * zoom),
m_bottom(clicks * zoom),
m_zoom(zoom),
m_clicks(clicks)
{

}

void camera::update(const float128_t centerX, const float128_t centerY, const float128_t zoom)
{
   m_centerX = centerX;
   m_centerY = centerY;
   m_zoom = zoom;
   m_left = m_centerX - m_zoom * m_clicks;
   m_right = m_centerX + m_zoom * m_clicks;
   m_top = m_centerY - m_zoom * m_clicks;
   m_bottom = m_centerY + m_zoom * m_clicks;
}


void render(SDL_Renderer* renderer, const camera* cam)
{
   for (int i = 0; i < SCREEN_SIZE; ++i)
     {
         for (int j = 0; j < SCREEN_SIZE; ++j)
         {
             SDL_SetRenderDrawColor(renderer, 0x00, 0x00, buffer[j][i], 0x00);
             SDL_RenderDrawPoint(renderer,j, i);
         }
     }
    //Update screen
    SDL_RenderPresent(renderer );
}

 // update the array that holds the pixel colors
 // this is a complete update, like after zoom
 void update_buffer(const camera* cam)
 {
     longVec point;
     for (int i = 0; i < SCREEN_SIZE; ++i)
     {
         for (int j = 0; j < SCREEN_SIZE; ++j)
         {
             point = screen_to_cam(cam, j, i); // convert to world coordinates
             float col = mandelbrot(point.x, point.y);
             buffer[j][i] = col;
         }
     }
 }

 // convert screen coordinates to camera coordinates
 longVec screen_to_cam(const camera* cam, const int x, const int y)
 {
     longVec point;
     point.x = cam->m_left + ((float128_t)(x) * cam->m_zoom);
     point.y = cam->m_top + ((float128_t)(y) * cam->m_zoom);
     return point;
}

  // return a color representing the distance from 0
  // any point that is bounded to distance two will be black
  // the rest will be depentdet on the number of iteration before it escapes to infinity
  float mandelbrot(const float128_t x, const float128_t y)
  {
      // the formula is z = z*z + c
      std::complex<long double> c(x, y);
      std::complex<long double> z(0,0);
      for ( int i = 0; i < MAX_ITER; ++i)
      {
          if (std::abs(z) > 2)
          {
             float blue = 2550 * i / MAX_ITER;   // blue color
             return blue;
          }
          z = z * z + c;
      }
       return 0; // black component
  }

// all the scrolling functions update the screen_buffeer

void scroll_left(const camera* cam)
{
    // move every colum in buffer one colum to the right
    // need to calculate one colum on left side of buffer
    for (int i = SCREEN_SIZE - 2; i >= 0; --i)
    {
        for (int j = 0; j < SCREEN_SIZE; ++j)
        buffer[i+1][j] = buffer[i][j];
    }
    longVec point;
    for (int j = 0; j < SCREEN_SIZE; ++j) // calculate colors for left edge
     {
            point = screen_to_cam(cam, 0, j); // convert to world coordinates
            float col = mandelbrot(point.x, point.y);
            buffer[0][j] = col;
     }
    //update_buffer(cam);
}
void scroll_right(const camera* cam)
{
    // move every colum in buffer one colum to the left
    // need to calculate one colum on right side of buffer
    for (int i = 1; i < SCREEN_SIZE; ++i)
    {
        for (int j = 0; j < SCREEN_SIZE; ++j)
        buffer[i-1][j] = buffer[i][j];
    }
    longVec point;
    for (int j = 0; j < SCREEN_SIZE; ++j) // calculate colors for right edge
     {
            point = screen_to_cam(cam, SCREEN_SIZE - 1, j); // convert to world coordinates
            float col = mandelbrot(point.x, point.y);
            buffer[SCREEN_SIZE-1][j] = col;
     }
    
}
void scroll_up(const camera* cam)
{
    // move every row one row down
    // re claculate top row again
    for (int j = SCREEN_SIZE - 2; j >= 0; --j )
    {
        for (int i = 0; i < SCREEN_SIZE; ++ i)
        buffer[i][j+1] = buffer[i][j];
    }
    // recalculate top edge
    longVec point;
    for (int i = 0; i < SCREEN_SIZE; ++i)
    {
      point = screen_to_cam(cam, i, 0); // convert to world coordinates
      float col = mandelbrot(point.x, point.y);
      buffer[i][0] = col;  
    }

    
}
void scroll_down(const camera* cam)
{
    // move every row one row up
    // re claculate bottom row again
    for (int j = 1; j < SCREEN_SIZE; ++j )
    {
        for (int i = 0; i < SCREEN_SIZE; ++ i)
        buffer[i][j-1] = buffer[i][j];
    }
    // recalculate bottom edge
    longVec point;
    for (int i = 0; i < SCREEN_SIZE; ++i)
    {
      point = screen_to_cam(cam, i, SCREEN_SIZE - 1); // convert to world coordinates
      float col = mandelbrot(point.x, point.y);
      buffer[i][SCREEN_SIZE-1] = col;  
    }
}
void zoom(const camera* cam)
{
    // could not think of a more efficient way to zoom without a complete buffer update
    update_buffer(cam);
}
