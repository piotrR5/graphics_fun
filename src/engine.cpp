#include "engine.h"
#include "STL_utils.cpp"
#include "constants.h"

#include <ctime>

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

int drawMode=DRAW_NORMAL;

Engine::Engine(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
    renderer=SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);    

     
    camera=Camera();

    mainLoop();
}

Engine::~Engine(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::vector<Object2>__util_get2DAxis(){
    Point2 R(VIEW_WIDTH/2,0),L(-VIEW_WIDTH/2, 0),U(0, VIEW_HEIGHT/2),D(0, -VIEW_HEIGHT/2);
    R.color={100,100,100,255};
    L.color={100,100,100,255};
    U.color={100,100,100,255};
    D.color={100,100,100,255};
    Object2 axis({{U,D}, {R,L}});
    return {axis}; 
}

void Engine::eventHandler(bool& run){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            run = false;
            std::cout << "Quitting!\n";
            break;
        
        break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_q:{
                    run = false;
                    std::cout << "Quitting!\n";
                    break;
                }
                break;
                case SDLK_w:
                    camera.moveCamera({CAMERA_SPEED*camera.get_projection_plane().x, CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*camera.get_projection_plane().z});
                break;
                case SDLK_a:{
                    Vec3 moveVector=matrix_to_vector3(multip_matrix(ry_elementary_rotation(-3.14/2),vector3_to_matrix({CAMERA_SPEED*camera.get_projection_plane().x, CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*camera.get_projection_plane().z})));
                    moveVector.y=0;
                    camera.moveCamera(moveVector);
                }
                break;
                case SDLK_s:
                    camera.moveCamera({-CAMERA_SPEED*camera.get_projection_plane().x, -CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*-camera.get_projection_plane().z});
                    printf( "S pressed\n");
                break;
                case SDLK_d:{
                    Vec3 moveVector=matrix_to_vector3(multip_matrix(ry_elementary_rotation(3.14/2),vector3_to_matrix({CAMERA_SPEED*camera.get_projection_plane().x, CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*camera.get_projection_plane().z})));
                    moveVector.y=0;
                    camera.moveCamera(moveVector);
                }
                break;
                case SDLK_SPACE:
                    camera.moveCamera({0,CAMERA_SPEED,0});
                break;
                case SDLK_LSHIFT:
                    camera.moveCamera({0,-CAMERA_SPEED,0});
                break;
                case SDLK_m:{
                    drawMode++;
                    drawMode%=4;
                    drawMode++;
                }
                break;
            }
            printf( "Key press detected\n" );
            break;

        case SDL_KEYUP:
            printf( "Key release detected\n" );
            break;
        }
    }
}

bool Engine::mainLoop(){
    bool run=true;

    
    /*
        axis:
    */
    std::vector<Object2>AXIS=__util_get2DAxis();
    /*

    */
    STLObject test, test2;
    test.read_file("stl_models/lantern.stl");
    test2.read_file("stl_models/paleta.stl");
    Object3 ob(test.getTriangles()), ob1(test2.getTriangles());
    ob.rotate_object_x(3.14/2+3.14);
    ob1.rotate_object_x(3.14/2+3.14);
    ob1.translate_object({40,20,0});

    while(run){
        int startLoop=SDL_GetTicks();
        SDL_RenderClear(renderer);
        /*
            event handling
        */
        eventHandler(run);
        /*
        
        */
        draw(transformToFitScreen(AXIS), DRAW_COLOR, {50,50,50,255});
        /*
            handle adding obcjects before "tranformToFitScreen" and "drawAll" functions
        */


        draw(transformToFitScreen(projection(camera, {camera.axisX})), DRAW_NORMAL, {0,0,255,255});
        draw(transformToFitScreen(projection(camera, {camera.axisY})), DRAW_NORMAL, {255,0,0,255});
        draw(transformToFitScreen(projection(camera, {camera.axisZ})), DRAW_NORMAL, {0,255,0,255});




        draw(transformToFitScreen(projection(camera, {ob})), drawMode, {0,255,0,255});
        draw(transformToFitScreen(projection(camera, {ob1})), drawMode, {0,255,0,255});
        ob.rotate_object_y(0.01);
        




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
        //clearConsole();
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
                if(i.size()==1)drawPoint(i[0], renderer);
                if(i.size()==2)drawLine(i[0],i[1], renderer);
                if(i.size()==3)drawTriangleMesh(i[0],i[1],i[2], renderer);
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
                if(i.size()==1)drawPoint(i[0], renderer);
                if(i.size()==2)drawLine(i[0],i[1], renderer);
                if(i.size()==3)drawTriangle(i[0],i[1],i[2], renderer);
            }
        }
    }
}

