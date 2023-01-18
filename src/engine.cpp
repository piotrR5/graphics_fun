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

// void fastRotation(point2& p, double a){
//     double newX=p.x*std::cos(a) - p.y*std::sin(a);
//     double newY=p.x*std::sin(a) + p.y*std::cos(a);
//     p.x=newX;
//     p.y=newY;
// }

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
    point2 r(500,0),l(-500, 0),u(0, 500),d(0, -500);
    r.color={100,100,100,255};
    l.color={100,100,100,255};
    u.color={100,100,100,255};
    d.color={100,100,100,255};
    addLine(u,d);
    addLine(r,l);
    /*

    */

   point2 a(0,0), b(0,200), c(100, 300);
   a.color={255,0,0,255};
   b.color={255,0,255,255};
   c.color={0,0,255,255};
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
        //fastRotation(lines[2].b, 0.1);
        tranformToFitScreen();
        drawTriangleMesh(a,b,c,renderer);

        drawAll();
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

void Engine::tranformToFitScreen(){
    pScreen.clear();
    lScreen.clear();
    tScreen.clear();

    for(int i=0;i<points.size();i++){
        pScreen.push_back(transformPoint(points[i]));
    }

    for(int i=0;i<lines.size();i++){
        line2 ls;
        ls.a=transformPoint(lines[i].a);
        ls.b=transformPoint(lines[i].b);
        lScreen.push_back(ls);
    }

    for(int i=0;i<triangles.size();i++){
        triangle2 ts;
        ts.a=transformPoint(triangles[i].a);
        ts.b=transformPoint(triangles[i].b);
        ts.c=transformPoint(triangles[i].c);
        tScreen.push_back(ts);
    }
}

void Engine::drawAll(){
    for(auto i:pScreen){
        drawPoint(i, renderer);
        //std::cout<<"[point: "<<i.x<<" "<<i.y<<"]\n";
    }
    
    for(auto i:lScreen){
        drawLine(i.a, i.b, renderer);
        // std::cout<<"[line: ]\n";
        // std::cout<<"[\t"<<i.a.x<<" "<<i.a.y<<"\t]\n";
        // std::cout<<"[\t"<<i.b.x<<" "<<i.b.y<<"\t]\n";
    }
    for(auto i:tScreen){
        drawTriangle(i.a, i.b, i.c, renderer);
        // std::cout<<"[trianglee: ]\n";
        // std::cout<<"[\t"<<i.a.x<<" "<<i.a.y<<"\t]\n";
        // std::cout<<"[\t"<<i.b.x<<" "<<i.b.y<<"\t]\n";
        // std::cout<<"[\t"<<i.c.x<<" "<<i.c.y<<"\t]\n";
    }

    // std::cout<<"[OG OBJECT]\n";
    // for(auto i:points){
    //     std::cout<<"[point: "<<i.x<<" "<<i.y<<"]\n";
    // }
    // for(auto i:lines){
    //     std::cout<<"[line: ]\n";
    //     std::cout<<"[\t"<<i.a.x<<" "<<i.a.y<<"\t]\n";
    //     std::cout<<"[\t"<<i.b.x<<" "<<i.b.y<<"\t]\n";
    // }

    // for(auto i:triangles){
    //     std::cout<<"[trianglee: ]\n";
    //     std::cout<<"[\t"<<i.a.x<<" "<<i.a.y<<"\t]\n";
    //     std::cout<<"[\t"<<i.b.x<<" "<<i.b.y<<"\t]\n";
    //     std::cout<<"[\t"<<i.c.x<<" "<<i.c.y<<"\t]\n";
    // }
}

void Engine::addTriangle(point2 a, point2 b, point2 c){
    triangles.push_back(triangle2(a,b,c));
    tScreen.push_back(triangle2());
}

void Engine::addTriangle(triangle2 t){
    triangles.push_back(t);
    tScreen.push_back(triangle2());
}

void Engine::popTriangle(){
    triangles.pop_back();
    tScreen.pop_back();
}

void Engine::removeTriangle(std::size_t i){
    triangles.erase(triangles.begin()+1);
    tScreen.pop_back();
}

void Engine::addLine(point2 a, point2 b){
    lines.push_back(line2(a,b));
    //lScreen.push_back(line2());
}

void Engine::addLine(line2 l){
    lines.push_back(l);
    //lScreen.push_back(line2());
}

void Engine::popLine(){
    lines.pop_back();
    //lScreen.pop_back();
}

void Engine::removeLine(std::size_t i){
    lines.erase(lines.begin()+i);
    //lScreen.pop_back();
}

void Engine::addPoint(point2 p){
    points.push_back(p);
    //pScreen.push_back(point2());
}

void Engine::popPoint(){
    points.pop_back();
    //pScreen.pop_back();
}

void Engine::removePoint(std::size_t i){
    points.erase(points.begin()+i);
    //pScreen.pop_back();
}