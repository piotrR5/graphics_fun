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

void fastRotation(point2& p, double a){
    double newX=p.x*std::cos(a) - p.y*std::sin(a);
    double newY=p.x*std::sin(a) + p.y*std::cos(a);
    p.x=newX;
    p.y=newY;
}

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

    /*
        axis:
    */
    point2 R(500,0),L(-500, 0),U(0, 500),D(0, -500);
    R.color={100,100,100,255};
    L.color={100,100,100,255};
    U.color={100,100,100,255};
    D.color={100,100,100,255};
    /*

    */

   point2 a(-200,-200), b(200,-200), c(-200, 200), d(200,200);
   a.color={255,0,255,255};
   b.color={255,0,0,255};
   c.color={0,0,255,255};
   d.color={255,255,255};

   point2 a1(20,20), b1(20, 180), c1(80, 280);
   a1.color={255,0,255,255};
   b1.color={255,0,0,255};
   c1.color={0,0,255,255};

   
   //addTriangle(a,b,c);
    

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
        /*
        
        */


        /*
            handle adding obcjects before "tranformToFitScreen" and "drawAll" functions
        */
        
        fastRotation(a,0.01);
        fastRotation(b,0.01);
        fastRotation(c,0.01);
        fastRotation(d,0.01);

        draw(transformToFitScreen({{a,b,c}, {b,c,d}}));
        draw(transformToFitScreen({{U,D}, {R,L}}));

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

    return 0;
}

point2 Engine::transformPoint(const point2& p){
    point2 ret;
    ret.x=(500+p.x)*mx;
    ret.y=(500-p.y)*my;
    ret.color=p.color;
    return ret;
}

std::vector<std::vector<point2>>Engine::transformToFitScreen(const std::vector<std::vector<point2>>& obj){
    std::vector<std::vector<point2>>ret;
    for(const auto& o:obj){
        ret.push_back(std::vector<point2>());
        for(auto i:o)ret[ret.size()-1].push_back(transformPoint(i));
    }

    return ret;
}

void Engine::draw(const std::vector<std::vector<point2>>& obj){
    for(const auto& o:obj){
        switch(o.size()){
            case 1:{
                drawPoint(o[0], renderer);
            }
            break;
            case 2:{
                drawLine(o[0], o[1], renderer);
            }
            break;
            case 3:{
                drawTriangle(o[0], o[1], o[2], renderer);
            }
            break;
        }
    }
}

void Engine::draw(const std::vector<std::vector<point2>>& obj, color_RGBA color){
    for(const auto& o:obj){
        switch(o.size()){
            case 1:{
                drawPoint(o[0], color, renderer);
            }
            break;
            case 2:{
                drawLine(o[0], o[1], color, renderer);
            }
            break;
            case 3:{
                drawTriangle(o[0], o[1], o[2], color, renderer);
            }
            break;
        }
    }
}

void Engine::draw(const std::vector<std::vector<point2>>& obj, bool wireframe){
    for(const auto& o:obj){
        switch(o.size()){
            case 1:{
                drawPoint(o[0], renderer);
            }
            break;
            case 2:{
                drawLine(o[0], o[1], renderer);
            }
            break;
            case 3:{
                drawTriangleMesh(o[0], o[1], o[2], renderer);
            }
            break;
        }
    }
}



