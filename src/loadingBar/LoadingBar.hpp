#pragma once

#include "../header.hpp"

class Window;
class Pixel;

class LoadingBar
{
    private:
        Window *window;
        int percentage;

        void refresh();

    public:
        LoadingBar(Window *window);
        ~LoadingBar();
        void add(int i);
        void set(int i);
};