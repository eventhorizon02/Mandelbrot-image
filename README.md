# Mandelbrot-image
A C++ Madelbrot set viewer
This code lets you view the beautiful images generated by the Mandelbrot set.
You can see fractal and zoom in and explore for hours.
There are many articles on the net about fractal and the Mandelbrot set if you are interested.
It was compiled on OS X but should be otherwise easily compiled on any other platform since it is in C++.
The Binaries need to link with the SDL2 graphical library.

Once running use the arrow keys to scroll, space bar to zoom it, enter to zoom out.

Theoretically you should be able to zoom in for all of eternity, unfortunately once you zoomed in enough times the long double floating point variable will run out of precision.
Once that happens you will start loosing the fractal edges and the image will start smoothing out.
If you are so motivated you could come up with your own data type, a dynamically ever expanding float. If you did that then the only limiting factor will be your systems ram.
I might, if I have more time in the future implement that improvement myself.
You can do as you wish with this code, no restrictions whatsoever.
