#include "Window.hpp"

Window::Window(int height, int width) :  height(height), width(width), img_index(0)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(this->width, this->height, 0, &this->window, &this->renderer);
    this->clear();
}

Window::~Window()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

int Window::get_width() const
{
    return this->width;
}

int Window::get_height() const
{
    return this->height;
}

void Window::clear()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
}

void Window::refresh()
{
    SDL_RenderPresent(this->renderer);
}

void Window::pause()
{
    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
        //std::cout << event.key.keysym.sym << std::endl;
        // this->event_info(event);
        switch (event.type)
        {
        case SDL_QUIT:
            printf( "Quit\n" );
            return;
        case SDL_KEYDOWN:
            if (!event.key.repeat)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        this->set_next_image();
                        break;
                    case SDLK_LEFT:
                        this->set_prev_image();
                        break;
                    case SDLK_s:
                        if (event.key.keysym.mod == KMOD_LCTRL)
                            Saver::saveToBMP(this->height, this->width, this->imgs[img_index].getPixels());
                        break;
                }
            }
            break;
        default:
            // printf( "Default\n" );
            break;
        }
    }
}

void Window::stream(Image &img)
{

    // for (int i = 0; i < this->height; ++i)
    //     for (int j = 0; j < this->width; ++j)
    //         img[i][j].getRed() != 0.0 && std::cout << -------------" << std::endl; 


    if (!img.is_valid(this->width, this->height))
        throw "Window::stream: Image and window dimensions do not match.";

    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            SDL_SetRenderDrawColor(
                this->renderer,
                img[i][j].getRed(),
                img[i][j].getGreen(),
                img[i][j].getBlue(),
                img[i][j].getOpacity()
            );
            SDL_RenderDrawPoint(this->renderer, i, j);
        }
    }
    this->refresh();

    // poll for an event for the window to pop
    SDL_Event event;
    SDL_PollEvent(&event);
}

void Window::load_image(Image *img)
{

    if (!img->is_valid(this->height, this->width))
        throw "Image and window dimensions do not match.";

    std::cout << "image loaded 2" << std::endl;
    Image new_img(img);
    std::cout << "image loaded 3" << std::endl;
    this->imgs.push_back(new_img);
    std::cout << "image loaded 4" << std::endl;
}

void Window::set_image()
{
    if (this->imgs.size() == 0)
        throw "Window::set_image: No images loaded.";

    for (int h = 0; h < this->height; ++h)
    {
        for (int w = 0; w < this->width; ++w)
        {
            SDL_SetRenderDrawColor(
                this->renderer,
                this->imgs[this->img_index][h][w].getRed(),
                this->imgs[this->img_index][h][w].getGreen(),
                this->imgs[this->img_index][h][w].getBlue(),
                this->imgs[this->img_index][h][w].getOpacity()
            );
            SDL_RenderDrawPoint(this->renderer, w, h);
        }
    }
    this->refresh();
}

void Window::set_next_image()
{
    ++this->img_index;
    if (this->img_index >= (int)this->imgs.size())
        this->img_index = 0;
    this->set_image();
}

void Window::set_prev_image()
{
    --this->img_index;
    if (this->img_index < 0)
        this->img_index = this->imgs.size() - 1;
    this->set_image();
}

void Window::event_info(SDL_Event event) const
{
    switch (event.type)
    {
    case SDL_FIRSTEVENT:
        printf("SDL_FIRSTEVENT\n");
        break;
    case SDL_QUIT:
        printf("SDL_QUIT\n");
        break;
    case SDL_APP_TERMINATING:
        printf("SDL_APP_TERMINATING\n");
        break;
    case SDL_APP_LOWMEMORY:
        printf("SDL_APP_LOWMEMORY\n");
        break;
    case SDL_APP_WILLENTERBACKGROUND:
        printf("SDL_APP_WILLENTERBACKGROUND\n");
        break;
    case SDL_APP_DIDENTERBACKGROUND:
        printf("SDL_APP_DIDENTERBACKGROUND\n");
        break;
    case SDL_APP_WILLENTERFOREGROUND:
        printf("SDL_APP_WILLENTERFOREGROUND\n");
        break;
    case SDL_APP_DIDENTERFOREGROUND:
        printf("SDL_APP_DIDENTERFOREGROUND\n");
        break;
    case SDL_LOCALECHANGED:
        printf("SDL_LOCALECHANGED\n");
        break;
    case SDL_DISPLAYEVENT:
        printf("SDL_DISPLAYEVENT\n");
        break;
    case SDL_WINDOWEVENT:
        printf("SDL_WINDOWEVENT\n");
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("Window %d shown", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("Window %d hidden", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("Window %d exposed", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("Window %d moved to %d,%d",
                    event.window.windowID, event.window.data1,
                    event.window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("Window %d resized to %dx%d",
                    event.window.windowID, event.window.data1,
                    event.window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("Window %d size changed to %dx%d",
                    event.window.windowID, event.window.data1,
                    event.window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("Window %d minimized", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("Window %d maximized", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("Window %d restored", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            SDL_Log("Mouse entered window %d",
                    event.window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("Mouse left window %d", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("Window %d gained keyboard focus",
                    event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("Window %d lost keyboard focus",
                    event.window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("Window %d closed", event.window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            SDL_Log("Window %d is offered a focus", event.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            SDL_Log("Window %d has a special hit test", event.window.windowID);
            break;
#endif
        default:
            SDL_Log("Window %d got unknown event %d",
                    event.window.windowID, event.window.event);
            break;
        }
        break;
    case SDL_SYSWMEVENT:
        printf("SDL_SYSWMEVENT\n");
        break;
    case SDL_KEYDOWN:
        printf("SDL_KEYDOWN\n");
        break;
    case SDL_KEYUP:
        printf("SDL_KEYUP\n");
        break;
    case SDL_TEXTEDITING:
        printf("SDL_TEXTEDITING\n");
        break;
    case SDL_TEXTINPUT:
        printf("SDL_TEXTINPUT\n");
        break;
    case SDL_KEYMAPCHANGED:
        printf("SDL_KEYMAPCHANGED\n");
        break;
    case SDL_MOUSEMOTION:
        printf("SDL_MOUSEMOTION\n");
        break;
    case SDL_MOUSEBUTTONDOWN:
        printf("SDL_MOUSEBUTTONDOWN\n");
        break;
    case SDL_MOUSEBUTTONUP:
        printf("SDL_MOUSEBUTTONUP\n");
        break;
    case SDL_MOUSEWHEEL:
        printf("SDL_MOUSEWHEEL\n");
        break;
    case SDL_JOYAXISMOTION:
        printf("SDL_JOYAXISMOTION\n");
        break;
    case SDL_JOYBALLMOTION:
        printf("SDL_JOYBALLMOTION\n");
        break;
    case SDL_JOYHATMOTION:
        printf("SDL_JOYHATMOTION\n");
        break;
    case SDL_JOYBUTTONDOWN:
        printf("SDL_JOYBUTTONDOWN\n");
        break;
    case SDL_JOYBUTTONUP:
        printf("SDL_JOYBUTTONUP\n");
        break;
    case SDL_JOYDEVICEADDED:
        printf("SDL_JOYDEVICEADDED\n");
        break;
    case SDL_JOYDEVICEREMOVED:
        printf("SDL_JOYDEVICEREMOVED\n");
        break;
    case SDL_CONTROLLERAXISMOTION:
        printf("SDL_CONTROLLERAXISMOTION\n");
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        printf("SDL_CONTROLLERBUTTONDOWN\n");
        break;
    case SDL_CONTROLLERBUTTONUP:
        printf("SDL_CONTROLLERBUTTONUP\n");
        break;
    case SDL_CONTROLLERDEVICEADDED:
        printf("SDL_CONTROLLERDEVICEADDED\n");
        break;
    case SDL_CONTROLLERDEVICEREMOVED:
        printf("SDL_CONTROLLERDEVICEREMOVED\n");
        break;
    case SDL_CONTROLLERDEVICEREMAPPED:
        printf("SDL_CONTROLLERDEVICEREMAPPED\n");
        break;
    case SDL_CONTROLLERTOUCHPADDOWN:
        printf("SDL_CONTROLLERTOUCHPADDOWN\n");
        break;
    case SDL_CONTROLLERTOUCHPADMOTION:
        printf("SDL_CONTROLLERTOUCHPADMOTION\n");
        break;
    case SDL_CONTROLLERTOUCHPADUP:
        printf("SDL_CONTROLLERTOUCHPADUP\n");
        break;
    case SDL_CONTROLLERSENSORUPDATE:
        printf("SDL_CONTROLLERSENSORUPDATE\n");
        break;
    case SDL_FINGERDOWN:
        printf("SDL_FINGERDOWN\n");
        break;
    case SDL_FINGERUP:
        printf("SDL_FINGERUP\n");
        break;
    case SDL_FINGERMOTION:
        printf("SDL_FINGERMOTION\n");
        break;
    case SDL_DOLLARGESTURE:
        printf("SDL_DOLLARGESTURE\n");
        break;
    case SDL_DOLLARRECORD:
        printf("SDL_DOLLARRECORD\n");
        break;
    case SDL_MULTIGESTURE:
        printf("SDL_MULTIGESTURE\n");
        break;
    case SDL_CLIPBOARDUPDATE:
        printf("SDL_CLIPBOARDUPDATE\n");
        break;
    case SDL_DROPFILE:
        printf("SDL_DROPFILE\n");
        break;
    case SDL_DROPTEXT:
        printf("SDL_DROPTEXT\n");
        break;
    case SDL_DROPBEGIN:
        printf("SDL_DROPBEGIN\n");
        break;
    case SDL_DROPCOMPLETE:
        printf("SDL_DROPCOMPLETE\n");
        break;
    case SDL_AUDIODEVICEADDED:
        printf("SDL_AUDIODEVICEADDED\n");
        break;
    case SDL_AUDIODEVICEREMOVED:
        printf("SDL_AUDIODEVICEREMOVED\n");
        break;
    case SDL_SENSORUPDATE:
        printf("SDL_SENSORUPDATE\n");
        break;
    case SDL_RENDER_TARGETS_RESET:
        printf("SDL_RENDER_TARGETS_RESET\n");
        break;
    case SDL_RENDER_DEVICE_RESET:
        printf("SDL_RENDER_DEVICE_RESET\n");
        break;
    case SDL_USEREVENT:
        printf("SDL_USEREVENT\n");
        break;
    case SDL_LASTEVENT:
        printf("SDL_LASTEVENT\n");
        break;
    default:
        printf("Other event\n");
        break;
    }
}
