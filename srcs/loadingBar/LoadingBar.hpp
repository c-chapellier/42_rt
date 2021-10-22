#pragma once

#include "../header.hpp"

class Window;

class LoadingBar
{
    private:
        Window *window;
        int percentage;

        void refresh();

    public:
        LoadingBar(Window *window);
        ~LoadingBar();
        LoadingBar &operator+=(const int rhs);
};