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

    double chuj=0;

    a.x=0;
    a.y=1;
    a.color.r=255;
    
    b.x=0;
    b.y=200;
    b.color.g=255;

    c.x=200;
    c.y=200;
    c.color.b=255;

    point2 r,l,u,d;
    r.x=500;
    r.color={255,255,255,255};

    l.x=-500;
    l.color={255,255,255,255};

    u.y=500;
    u.color={255,255,255,255};

    d.y=-500;
    d.color={255,255,255,255};
    

    std::vector<point2*>points;

    points.push_back(&a);
    points.push_back(&b);
    points.push_back(&c);
    points.push_back(&r);
    points.push_back(&l);
    points.push_back(&d);
    points.push_back(&u);

    transformToFitScreen(points);

    while(run){
        chuj+=0.00001;
        if(chuj==100)chuj=0;
        double newX=b.x*std::cos(chuj)-b.y*std::sin(chuj);
        double newY=b.x*std::sin(chuj)+b.y*std::cos(chuj);
        b.x=newX;
        b.y=newY;


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
        drawLine(u,d,renderer);
        drawLine(r,l,renderer);
        /*

        */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);



        /*
            fps cap
        */
        int dT = SDL_GetTicks() - startLoop;
        if(desiredDT-dT)std::cout<<"[fps: "<<1000/abs(desiredDT+dT)<<"]\n";
        else std::cout<<"[fps: "<<fps<<"]\n";
        if(dT<desiredDT){
            SDL_Delay(desiredDT-dT);
        }
        clearConsole();
    }
}