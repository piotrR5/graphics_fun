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

    point2 a,b,c;
    point2 d,e,f;

    a.x=500;
    a.y=0;
    a.color.r=255;
    
    b.x=-500;
    b.y=0;
    b.color.g=255;

    c.x=0;
    c.y=200;
    c.color.b=255;

    d.x=-500;
    d.y=-500;
    d.color.r=255;
    d.color.g=255;
    d.color.b=255;

    e.x=500;
    e.y=500;
    e.color.r=0;
    e.color.g=0;
    e.color.b=0;

    f.x=-300;
    f.y=500;
    f.color.r=50;
    f.color.g=50;
    f.color.b=50;

    std::vector<point2*>points;

    points.push_back(&a);
    points.push_back(&b);
    points.push_back(&c);
    points.push_back(&d);
    points.push_back(&e);
    points.push_back(&f);



    transformToFitScreen(points);



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
        drawTriangle(a,b,c,renderer);
        drawTriangle(d,e,f,renderer);
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