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

     
    O=Point3(0,0,500);
    X=Point3(50,0,500); Xa1=Point3(40,5,500); Xa2=Point3(40,-5,500); 
    Y=Point3(0,50,500); Ya1=Point3(5,40,500); Ya2=Point3(-5,40,500);
    Z=Point3(0,0,550); Za1=Point3(5,0,540); Za2=Point3(-5, 0, 540);

    axisX=Object3({{O,X}, {X,Xa1}, {X,Xa2}}); 
    axisY=Object3({{O,Y}, {Y,Ya1}, {Y,Ya2}});
    axisZ=Object3({{O,Z}, {Z, Za1}, {Z,Za2}});

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
    STLObject test_object1;
    test_object1.read_file("stl_models/lantern.stl");
    Object3 moai(test_object1.getTriangles());
    moai.set_object_position({0,0,0});
    moai.scale_object(2);
    moai.rotate_object_x(3.14/2);
    moai.rotate_object_y(3.14);
    moai.rotate_object_z(3.14);

    // STLObject test_object2;
    // test_object2.read_file("stl_models/moai.stl");
    // moai.addVertices(test_object2.getTriangles());

    Camera camera;

    double delete_this_double=0;

    while(run){
        delete_this_double+=0.01;
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
    

        //draw(transformToFitScreen(AXIS), DRAW_WIREFRAME_COLOR, {50,50,50,255});
        // // draw(
        // //     transformToFitScreen(projection(camera,{cube})),
        // //     DRAW_WIREFRAME_COLOR,
        // //     {69,0,200,255}
        // // );

        // draw(transformToFitScreen(projection(camera, {senor})),DRAW_WIREFRAME_COLOR, {0,255,0,255});

        // draw(transformToFitScreen(projection(camera, {axisX})), DRAW_COLOR, {0,0,255,255});
        // draw(transformToFitScreen(projection(camera, {axisY})), DRAW_COLOR, {255,0,0,255});
        // draw(transformToFitScreen(projection(camera, {axisZ})), DRAW_COLOR, {0,255,0,255});

        draw(transformToFitScreen(projection(camera, {moai})), DRAW_WIREFRAME_COLOR, {0,255,0,255});
        //moai.rotate_object_x(0.1);
        moai.rotate_object_y(0.1);
        //moai.rotate_object_z(0.1);
        //moai.translate_object({1,0,0});
        //moai.translate_object({0,0,5*sin(delete_this_double)});

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