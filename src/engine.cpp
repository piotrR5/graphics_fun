#include "engine.h"
#include "STL_utils.cpp"
#include "constants.h"

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
    window=SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
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

void debugObject2(std::vector<Object2>o){
    for(auto& i:o){
        for(auto& v:i.getVertices()){
            if(v.size()==1)std::cout<<"POINT\n";
            if(v.size()==2)std::cout<<"LINE\n";
            if(v.size()==3)std::cout<<"TRIANGLE\n";
            for(auto& x:v)std::cout<<x.x<<" , "<<x.y<<"\n";
        }
        std::cout<<"\n";
    }
}

bool Engine::mainLoop(){
    bool run=true;

    /*
        axis:
    */
    Point2 R(VIEW_WIDTH/2,0),L(-VIEW_WIDTH/2, 0),U(0, VIEW_HEIGHT/2),D(0, -VIEW_HEIGHT/2);
    R.color={100,100,100,255};
    L.color={100,100,100,255};
    U.color={100,100,100,255};
    D.color={100,100,100,255};
    Object2 axis({{U,D}, {R,L}});
    std::vector<Object2>AXIS{axis}; 
    /*

    */
         

    STLObject stl_cube, stl_o1;
    stl_cube.read_file("stl_models/Artifact.stl");
    stl_o1.read_file("stl_models/senor_bumbo_cactoni.stl");

    Object3 cube(stl_cube.getTriangles());
    Object3 senor(stl_o1.getTriangles());

    for(auto& i:cube.getVertives()){
        for(auto& j:i){
            j.x-=40;
            j.z+=500;
            j.y-=50;
        }
    }

    for(auto& i:senor.getVertives()){
        for(auto& j:i){
            j.x+=40;
            j.z+=500;
            j.y+=30;
        }
    }

    Camera camera;

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


        for(auto& i:senor.getVertives()){
        for(auto& j:i){
            j.x+=1;
            //j.z+=0.5;
            //j.y+=30;
        }
    }

        draw(transformToFitScreen(AXIS), DRAW_WIREFRAME_COLOR, {200,50,0,255});
        draw(
            transformToFitScreen(projection(camera,{cube})),
            DRAW_COLOR,
            {69,0,200,255}
        );

        draw(transformToFitScreen(projection(camera, {senor})),DRAW_WIREFRAME_COLOR, {0,255,0,255});


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

Point2 Engine::transformPoint(const Point2& p){
    Point2 ret;
    ret.x=(VIEW_WIDTH/2+p.x)*mx;
    ret.y=(VIEW_HEIGHT/2-p.y)*my;
    ret.color=p.color;
    return ret;
}

std::vector<Object2>Engine::transformToFitScreen(std::vector<Object2> obj){
    std::vector<Object2>ret;
    for(auto& o:obj){
        std::vector<std::vector<Point2>>foo;
        for(auto& i:o.getVertices()){
            std::vector<Point2>r;
            for(auto& v:i)r.push_back(transformPoint(v));
            foo.push_back(r);
        }
        ret.push_back(Object2(foo));
    }

    return ret;
}

void Engine::draw(std::vector<Object2> object, uint8_t mode, Color_RGBA color){
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