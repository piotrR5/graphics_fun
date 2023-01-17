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

double getA(point2& a, point2& b){
    if(a.x-b.x==0){
        a.x++;
        return (b.y-a.y)/(b.x-a.x);
    }
    if(a.y-b.y==0)return 0;
    else return (b.y-a.y)/(b.x-a.x);
}

double getB(point2 p, double a){
    double ret=0.0;

    if(a==0)return p.y;
    if(a==INT_BIG)return INT_BIG;
    return p.y - a*p.x;
}

point2 linesIntersection(double A1, double B1, double A2, double B2){
    point2 ret;
    if(A1-A2)ret.x=(B2-B1)/(A1-A2);
    if(!(B2-B1))ret.x=INT_BIG;
    ret.y=A1*ret.x+B1;

    return ret;
}

bool isInDomain(point2 x, point2 a, point2 b){
    if(x.x > a.x && x.x > b.x)return false;
    if(x.x < a.x && x.x < b.x)return false;
    return true;
}

void drawTriangle(point2 a, point2 b, point2 c, SDL_Renderer* renderer){
    int miny=std::min(a.y, std::min(b.y,c.y));
    int maxy=std::max(a.y, std::max(b.y,c.y));

    double A[3];
    double B[3];
    int X[3];

    A[0]=getA(a,b);
    A[1]=getA(b,c);
    A[2]=getA(c,a);

    B[0]=getB(a, A[0]);
    B[1]=getB(b, A[1]);
    B[2]=getB(c, A[2]);

    point2 i,j;

    for(int y=miny; y<=maxy;y++){
        double Ay=0;
        double By=y;
        point2 intersections[3];
        for(int i=0;i<3;i++)intersections[i]=linesIntersection(A[i], B[i], Ay, By);

        //inter0


        if(isInDomain(intersections[0], a, b) && isInDomain(intersections[1], b,c)){
            i.x=intersections[0].x;
            i.y=y;
            i.color=linearColorInterpolation(a,b,intersections[0]);

            j.x=intersections[1].x;
            j.y=y;
            j.color=linearColorInterpolation(b,c,intersections[1]);

            drawLine(i,j,renderer);

        }else if(isInDomain(intersections[0], a, b) && isInDomain(intersections[2], c,a)){
            i.x=intersections[0].x;
            i.y=y;
            i.color=linearColorInterpolation(a,b,intersections[0]);

            j.x=intersections[2].x;
            j.y=y;
            j.color=linearColorInterpolation(c,a,intersections[2]);

            drawLine(i,j,renderer);
            
        }else if(isInDomain(intersections[2], c, a) && isInDomain(intersections[1], b,c)){
            i.x=intersections[2].x;
            i.y=y;
            i.color=linearColorInterpolation(c,a,intersections[2]);

            j.x=intersections[1].x;
            j.y=y;
            j.color=linearColorInterpolation(b,c,intersections[1]);

            drawLine(i,j,renderer);
        }
    }
}