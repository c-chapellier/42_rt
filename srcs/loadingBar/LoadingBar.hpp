#include "../window/Window.hpp"
#include "../image/Image.hpp"

class LoadingBar
{
private:
    /* data */
    Window window;
    int percentage;

    void refresh();

public:
    LoadingBar(Window &window);
    ~LoadingBar();
    LoadingBar &operator+=(const int rhs);
};