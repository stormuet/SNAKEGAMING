// SNAKE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int scale = 15;
const string WINDOW_TITLE = "SNAKEGAMING";

void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal = false);

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

struct game {
    int x, y;
    int X0, Y0;
    int xspeed = 0, yspeed = 0;
    vector <int> tailX;
    vector <int> tailY;
    int length = 0;
    void headRenderer(SDL_Renderer* renderer) {
        SDL_Rect head;
        head.x = x;
        head.y = y;
        head.w = scale;
        head.h = scale;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &head);
    }
    void move() {
        X0 = x;
        Y0 = y;
        x += xspeed * scale;
        y += yspeed * scale;
    }
    void turnLeft() {
        xspeed = -1;
        yspeed = 0;
    }
    void turnRight() {
        xspeed = 1;
        yspeed = 0;
    }
    void turnUp() {
        xspeed = 0;
        yspeed = -1;
    }
    void turnDown() {
        xspeed = 0;
        yspeed = 1;
    }
    
};
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    // Your drawing code here
    // use SDL_RenderPresent(renderer) to show it
    game r;
    r.x = SCREEN_WIDTH / 2;
    r.y = SCREEN_HEIGHT / 2;
    SDL_Event e;
    while (true) {
        r.move();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer); 
        r.headRenderer(renderer);  
        SDL_RenderPresent(renderer);
        SDL_Delay(40);
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT: r.turnLeft();
                break;
            case SDLK_RIGHT: r.turnRight();
                break;
            case SDLK_DOWN: r.turnDown();
                break;
            case SDLK_UP: r.turnUp();
                break;
            default: break;
            }
        }

    }
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, 
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
