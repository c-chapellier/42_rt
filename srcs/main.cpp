#include "window/Window.hpp"

int main(void)
{
    Window win(600, 600);

    Pixel pxl(255, 0, 0, 255);

    std::vector< std::vector<Pixel> > pxls;
    pxls.resize(600, std::vector<Pixel>(600));

    for (int i = 0; i < 600; ++i)
        for (int j = 0; j < 600; ++j)
            pxls[i][j] = pxl;

    Image img(600, 600, pxls);

    win.load_image("ok", img);
    win.set_image("ok");

    win.pause();
    return 0;
}
