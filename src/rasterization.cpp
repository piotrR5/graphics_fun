#include "rasterization.h"
#include <iostream>

void drawPoint(point2 a, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, a.color.r, a.color.g, a.color.b, a.color.a);
    SDL_RenderDrawPoint(renderer, a.x, a.y);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

void drawLineBresenham(point2 a, point2 b, SDL_Renderer* renderer){
    int x0=a.x, y0=a.y;
    int x1=b.x, y1=b.y;

    int dx=abs(x1-x0);
    int sx=x0 < x1 ? 1 : -1;
    int dy=-abs(y0-y1);
    int sy=y0 < y1 ? 1 : -1;
    int error = dx + dy;
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    while(true){
        SDL_RenderDrawPoint(renderer, x0, y0);

        if(x0==x1 && y0==y1)break;
        int e2=2*error;
        if(e2 >= dy){
            if(x0 == x1)break;
            error+=dy;
            x0+=sx;
        }
        if(e2 <= dx){
            if(y0==y1)break;
            error+=dx;
            y0+=sy;
        }

    }
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

color_RGBA linearColorInterpolation(point2 a, point2 b, point2 m){
    double f=0.0;
    if(b.x-a.x)f=(m.x-a.x)/(b.x-a.x);
    else if(b.y-a.y)f=(m.y-a.y)/(b.y-a.y);

    color_RGBA ret;

    ret.r=(b.color.r - a.color.r) * f + a.color.r;
    ret.g=(b.color.g - a.color.g) * f + a.color.g;
    ret.b=(b.color.b - a.color.b) * f + a.color.b;
    ret.a=(b.color.a - a.color.a) * f + a.color.a;


    return ret;
}

void drawLine(point2 a, point2 b, SDL_Renderer* renderer){
    color_RGBA c0=a.color;
    color_RGBA c1=b.color;
    color_RGBA c;


    int x0=a.x, y0=a.y;
    int x1=b.x, y1=b.y;

    int dx=abs(x1-x0);
    int sx=x0 < x1 ? 1 : -1;
    int dy=-abs(y0-y1);
    int sy=y0 < y1 ? 1 : -1;
    int error = dx + dy;
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    while(true){
        point2 m;
        m.x=x0;
        m.y=y0;
        c=linearColorInterpolation(a,b, m);
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderDrawPoint(renderer, x0, y0);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);

        if(x0==x1 && y0==y1)break;
        int e2=2*error;
        if(e2 >= dy){
            if(x0 == x1)break;
            error+=dy;
            x0+=sx;
        }
        if(e2 <= dx){
            if(y0==y1)break;
            error+=dx;
            y0+=sy;
        }

    }
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

int getXFromY(double a, double b, int y){
    if(a==0)return 2147483647;
    return (y-b)/a;
}

double getA(point2 a, point2 b){
    if(b.y-a.y==0)return 0;
    if(b.x-a.x==0)return 1;
    return (b.y-a.y)/(b.x-a.x);
}

bool doesTheLineContainX(point2 a, point2 b, int x){
    if(x<a.x && x<b.x)return false;
    if(x>a.x && x>b.x)return false;
    return true;
}

void drawTriangle(point2 a, point2 b, point2 c, SDL_Renderer* renderer){
    drawLine(a,b,renderer);
    drawLine(b,c,renderer);
    drawLine(a,c,renderer);

    double a0=getA(a,b);
    double b0=a.y-a0*a.x;

    double a1=getA(b,c);
    double b1=b.y-a1*b.x;

    double a2=getA(c,a);
    double b2=c.y-a2*c.x;
    
    int miny=std::min(a.y, std::min(b.y, c.y));
    int maxy=std::max(a.y, std::max(b.y,c.y));

    for(int y=miny; y<=maxy; y++){
        
        point2 i,j,k;
        int x0=getXFromY(a0,b0,y);
        int x1=getXFromY(a1,b1,y);
        int x2=getXFromY(a2,b2,y);

        //std::cout<<y<<" "<<x0<<" "<<x1<<" "<<x2<<std::endl;
        
point2 m,n,o;

        i.x=x0;
        i.y=y;
        m.x=x0;
        m.y=y;
        i.color=linearColorInterpolation(a,b,m);

        j.x=x1;
        j.y=y;
        n.x=x1;
        n.y=y;
        j.color=linearColorInterpolation(b,c,n);

        o.x=x2;
        o.y=y;
        k.x=x2;
        k.y=y;
        k.color=linearColorInterpolation(a,c,o);

        if(doesTheLineContainX(a,b,x0) && doesTheLineContainX(b,c,x1))drawLine(i,j,renderer);
        else if(doesTheLineContainX(b,c,x1) && doesTheLineContainX(a,c,x2))drawLine(j,k,renderer);
        else if(doesTheLineContainX(a,b,x0) && doesTheLineContainX(a,c,x2))drawLine(i,k,renderer);
    }

}

void transformPoint(point2& p, double mx, double my){
    p.y=-(p.y);
    p.y+=500;
    p.x+=500;
    p.x*=mx;
    p.y*=my;
}

void transformToFitScreen(std::vector<point2*>points){
    int plane2x=1000;
    int plane2y=1000;

    int screenx=640;
    int screeny=480;

    double mx=screenx/(double)plane2x;
    double my=screeny/(double)plane2y;

    for(int i=0;i<points.size();i++){
        transformPoint(*points[i], mx,my);
    }
}
