
// the main computational file

#ifndef __mandel__
#define __mandel__
#include <SDL2/SDL.h>


//Screen dimension constants
const int SCREEN_SIZE = 600;

typedef long double float128_t; // 128 bit float on most systems

struct camera // a struct to define the world we are viewing
{
    explicit camera(const short clicks, const float128_t zoom);
    void update(const float128_t centerX, const float128_t centerY, const float128_t zoom);
    float128_t m_centerX;
    float128_t m_centerY;
    float128_t m_left;
    float128_t m_top;
    float128_t m_right;
    float128_t m_bottom;
    float128_t m_zoom; // distance between points

    private:
    short m_clicks; // how many units along and across, from center to each edge, world is square
};

struct longVec // a 2d vector with high precision float coordinates
{
    float128_t x;
    float128_t y;
};


void render(SDL_Renderer* renderer, const camera* cam);
longVec screen_to_cam(const camera* cam, const int x, const int y); // convert screen coordinates to camera coordinates
float mandelbrot(const float128_t x, const float128_t y); // returns the blue component representing the distance from 0
void update_buffer(const camera* cam); // update the array that holds the pixel colors
void scroll_left(const camera* cam); // all the scrolling functions update the screen_buffeer
void scroll_right(const camera* cam);
void scroll_up(const camera* cam);
void scroll_down(const camera* cam);
void zoom(const camera* cam);

#endif /* __mendel__*/

