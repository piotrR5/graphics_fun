#include "engine.h"

#ifdef __linux__ 
    //linux code goes here
    void clearConsole(){
        system("clear");
    }
#elif _WIN32
    // windows code goes here
    void clearConsole(){
        system("cls");
    }
#else

#endif



Engine::Engine(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN); 
    renderer=SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    mainLoop();
}

Engine::~Engine(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Engine::mainLoop(){
    bool run=true;
    while(run){
        int startLoop=SDL_GetTicks();
        SDL_RenderClear(renderer);

        /*
            event handling
        */
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                run = false;
                std::cout << "Quitting!\n";
                break;
            }
        }




        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        /*
            for the time being, call all draw functions between this and the next comment
        */
        // drawTriangleMesh(10, 10, SDL_Color({255,0,0,255}), 50, 50, SDL_Color({255,0,0,255}), 30, 100, SDL_Color({255,0,0,255}), renderer);

        // drawTriangleMesh(110, 110, SDL_Color({255,0,0,255}), 150, 150, SDL_Color({255,0,0,255}), 130, 200, SDL_Color({255,0,0,255}), renderer);
        /*

        */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        




        SDL_RenderPresent(renderer);



        /*
            fps cap
        */
        int dT = SDL_GetTicks() - startLoop;
        std::cout<<"[fps: "<<1000/(desiredDT-dT)<<"]\n";
        if(dT<desiredDT){
            SDL_Delay(desiredDT-dT);
        }
        clearConsole();
    }
}