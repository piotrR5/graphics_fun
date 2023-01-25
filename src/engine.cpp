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

    

    srand(time(NULL));

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
    test_object1.read_file("stl_models/SpinMe.stl");
    Object3 moai(test_object1.getTriangles());
    moai.set_object_position({0,0,100});
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
            
            break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_w:
                        camera.moveCamera({CAMERA_SPEED*camera.get_projection_plane().x, CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*camera.get_projection_plane().z});
                    break;
                    case SDLK_a:
                        camera.moveCamera(matrix_to_vector3(multip_matrix(ry_elementary_rotation(-3.14/2),vector3_to_matrix({CAMERA_SPEED*camera.get_projection_plane().x, CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*camera.get_projection_plane().z}))));
                    break;
                    case SDLK_s:
                        camera.moveCamera({-CAMERA_SPEED*camera.get_projection_plane().x, -CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*-camera.get_projection_plane().z});
                        printf( "S pressed\n");
                    break;
                    case SDLK_d:
                        camera.moveCamera(matrix_to_vector3(multip_matrix(ry_elementary_rotation(3.14/2),vector3_to_matrix({CAMERA_SPEED*camera.get_projection_plane().x, CAMERA_SPEED*camera.get_projection_plane().y, CAMERA_SPEED*camera.get_projection_plane().z}))));
                    break;
                    case SDLK_SPACE:
                        camera.moveCamera({0,CAMERA_SPEED,0});
                    break;
                    case SDLK_LSHIFT:
                        camera.moveCamera({0,-CAMERA_SPEED,0});
                    break;
                }
                printf( "Key press detected\n" );
                break;

            case SDL_KEYUP:
                printf( "Key release detected\n" );
                break;
            }
        }
        /*
        
        */

        /*
            handle adding obcjects before "tranformToFitScreen" and "drawAll" functions
        */
    

        draw(transformToFitScreen(AXIS), DRAW_WIREFRAME_COLOR, {50,50,50,255});

        draw(transformToFitScreen(projection(camera, {camera.axisX})), DRAW_COLOR, {0,0,255,255});
        draw(transformToFitScreen(projection(camera, {camera.axisY})), DRAW_COLOR, {255,0,0,255});
        draw(transformToFitScreen(projection(camera, {camera.axisZ})), DRAW_COLOR, {0,255,0,255});

        std::vector<Object2>moai_tranformed=transformToFitScreen(projection(camera, {moai}));
        for(auto& i:moai_tranformed){
            for(auto& j:i.getVertices()){
                for(auto& k:j){
                    k.color.r=rand()%256;
                    k.color.g=rand()%256;
                    k.color.b=rand()%256;
                }
            }
        }
        draw(moai_tranformed, DRAW_WIREFRAME_NORMAL, {0,255,0,255});
        // moai.rotate_object_y(0.05);
        // moai.translate_object({cos(delete_this_double), sin(delete_this_double*10/7), 0});

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