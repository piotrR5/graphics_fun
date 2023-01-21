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

    Object2 square({{a,b,c}, {d,c,b}});
    Object2 axis({{U,D}, {R,L}});
    std::vector<Object2>objects{square}, AXIS{axis};  
    objects[0].setAxis({100,100});  

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

        draw(transformToFitScreen(objects), DRAW_NORMAL, {255,200,100,255});
        draw(transformToFitScreen(AXIS), DRAW_WIREFRAME_COLOR, {200,50,0,255});
        
        objects[0].rotate(0.02);
        objects[0].scale(0.995);

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

std::vector<Object2>Engine::transformToFitScreen(std::vector<Object2>& obj){
    std::vector<Object2>ret;
    for(auto& o:obj){
        std::vector<std::vector<point2>>foo;
        for(auto& i:o.getVertices()){
            std::vector<point2>r;
            for(auto& v:i)r.push_back(transformPoint(v));
            foo.push_back(r);
        }
        ret.push_back(Object2(foo));
        //ret.getVertices().push_back(std::vector<point2>());
        //for(auto i:o.getVertices())ret[ret.size()-1].push_back(transformPoint(i));
    }

    return ret;
}

void Engine::draw(std::vector<Object2> object, uint8_t mode, color_RGBA color){
    if(mode==DRAW_WIREFRAME_NORMAL){
        for(auto& o:object){
            for(auto& i:o.getVertices()){
                if(i.size()==1)drawPoint(i[0], renderer);
                if(i.size()==2)drawLine(i[0],i[1], renderer);
                if(i.size()==3)drawTriangleMesh(i[0],i[1],i[2], renderer);
            }
        }
    }else if(mode==DRAW_WIREFRAME_COLOR){
        for(auto& o:object){
            for(auto& i:o.getVertices()){
                if(i.size()==1)drawPoint(i[0], color,renderer);
                if(i.size()==2)drawLine(i[0],i[1], color,renderer);
                if(i.size()==3)drawTriangleMesh(i[0],i[1],i[2], color, renderer);
            }
        }
    }else if(mode==DRAW_NORMAL){
        for(auto& o:object){
            for(auto& i:o.getVertices()){
                if(i.size()==1)drawPoint(i[0], renderer);
                if(i.size()==2)drawLine(i[0],i[1], renderer);
                if(i.size()==3)drawTriangle(i[0],i[1],i[2], renderer);
            }
        }
    }else if(mode==DRAW_COLOR){
        for(auto& o:object){
            for(auto& i:o.getVertices()){
                if(i.size()==1)drawPoint(i[0], color,renderer);
                if(i.size()==2)drawLine(i[0],i[1], color,renderer);
                if(i.size()==3)drawTriangle(i[0],i[1],i[2],color, renderer);
            }
        }
    }
}



