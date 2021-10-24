#pragma once

#include "../header.hpp"

class Window;
class Pixel;

class LoadingBar
{
    private:
        Window *window;
        int percentage;

        Pixel *black;
        Pixel *grey;

        void refresh();

    public:
        LoadingBar(Window *window);
        ~LoadingBar();
        void add(int i);
};