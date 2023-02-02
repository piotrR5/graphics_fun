#include "rasterization.h"
#include <iostream>


Color_RGBA linearColorInterpolation(Point2 a, Point2 b, Point2 m){
    double f=0.0;
    if(b.x-a.x)f=(m.x-a.x)/(b.x-a.x);
    else if(b.y-a.y)f=(m.y-a.y)/(b.y-a.y);

    Color_RGBA ret;

    ret.r=(b.color.r - a.color.r) * f + a.color.r;
    ret.g=(b.color.g - a.color.g) * f + a.color.g;
    ret.b=(b.color.b - a.color.b) * f + a.color.b;
    ret.a=(b.color.a - a.color.a) * f + a.color.a;


    return ret;
}

double getA(Vec2 a, Vec2 b){
    if(a.x-b.x==0){
        a.x++;
        return (b.y-a.y)/(b.x-a.x);
    }
    if(a.y-b.y==0)return 0;
    else return (b.y-a.y)/(b.x-a.x);
}

double getB(Vec2 p, double a){
    double ret=0.0;

    if(a==INT_BIG)return INT_BIG;
    return p.y - a*p.x;
}

Vec2 linesIntersection(double A1, double B1, double A2, double B2){
    Vec2 ret;
    if(A1-A2)ret.x=(B2-B1)/(A1-A2);
    if(!(B2-B1))ret.x=INT_BIG;
    ret.y=A1*ret.x+B1;

    return ret;
}

bool isInDomain(Vec2 x, Vec2 a, Vec2 b){
    if(x.x > a.x && x.x > b.x)return false;
    if(x.x < a.x && x.x < b.x)return false;
    return true;
}



void drawPoint(double x, double y, Color_RGBA color, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

void drawPoint(Point2 point, SDL_Renderer* renderer){
    drawPoint(point.x, point.y, point.color, renderer);
}

void drawPoint(Vec2 point, Color_RGBA color, SDL_Renderer* renderer){
    drawPoint(point.x, point.y, color, renderer);
}



void drawLine(Vec2 a, Color_RGBA c0, Vec2 b, Color_RGBA c1, SDL_Renderer* renderer){
    Color_RGBA c;

    int x0=a.x, y0=a.y;
    int x1=b.x, y1=b.y;

    int dx=abs(x1-x0);
    int sx=x0 < x1 ? 1 : -1;
    int dy=-abs(y0-y1);
    int sy=y0 < y1 ? 1 : -1;
    int error = dx + dy;
    while(true){
        Point2 m;
        m.x=x0;
        m.y=y0;
        c=linearColorInterpolation({a, c0},{b, c1}, m);
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
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
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}

void drawLine(Point2 a, Point2 b, SDL_Renderer* renderer){
    drawLine(a.makeVec2(), b.makeVec2(), renderer);
}



void drawTriangle(Vec2 a, Color_RGBA c0, Vec2 b, Color_RGBA c1, Vec2 c, Color_RGBA c2, SDL_Renderer* renderer){
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

    Point2 i,j;

    for(int y=miny; y<=maxy;y++){
        double Ay=0;
        double By=y;
        Vec2 intersections[3];
        for(int i=0;i<3;i++)intersections[i]=linesIntersection(A[i], B[i], Ay, By);

        if(isInDomain(intersections[0], a, b) && isInDomain(intersections[1], b,c)){
            i.x=intersections[0].x;
            i.y=y;
            i.color=linearColorInterpolation({a,c0},{b,c1},intersections[0]);

            j.x=intersections[1].x;
            j.y=y;
            j.color=linearColorInterpolation({b,c1},{c,c2},intersections[1]);

            drawLine(i,j,renderer);
            continue;

        }else if(isInDomain(intersections[0], a, b) && isInDomain(intersections[2], c,a)){
            i.x=intersections[0].x;
            i.y=y;
            i.color=linearColorInterpolation({a,c0},{b,c1},intersections[0]);

            j.x=intersections[2].x;
            j.y=y;
            j.color=linearColorInterpolation({c,c2},{a,c0},intersections[2]);

            drawLine(i,j,renderer);
            continue;
            
        }else if(isInDomain(intersections[2], c, a) && isInDomain(intersections[1], b,c)){
            i.x=intersections[2].x;
            i.y=y;
            i.color=linearColorInterpolation({c,c2},{a,c0},intersections[2]);

            j.x=intersections[1].x;
            j.y=y;
            j.color=linearColorInterpolation({b,c1},{c,c2},intersections[1]);

            drawLine(i,j,renderer);
            continue;
        }
    }
}

void drawTriangle(Point2 a, Point2 b, Point2 c, SDL_Renderer* renderer){
    drawTriangle(a.makeVec2(), a.color, b.makeVec2(), b.color, c.makeVec2(), c.color, renderer);
}



void drawTriangleMesh(Vec2 a, Color_RGBA c0, Vec2 b, Color_RGBA c1, Vec2 c, Color_RGBA c2, SDL_Renderer* renderer){
    drawLine(a, c0, b, c1, renderer);
    drawLine(c, c2, b, c1, renderer);
    drawLine(a, c0, c, c2, renderer);
}

void drawTriangleMesh(Point2 a, Point2 b, Point2 c, SDL_Renderer* renderer){
    drawTriangleMesh(a.makeVec2(), a.color, b.makeVec2(), b.color, c.makeVec2(), c.color, renderer);
}



std::vector<Object2>transformToFitScreen(std::vector<Object2> obj){
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

Point2 transformPoint(const Point2& p){
    Point2 ret;
    ret.x=(VIEW_WIDTH/2+p.x)*mx;
    ret.y=(VIEW_HEIGHT/2-p.y)*my;
    ret.color=p.color;
    return ret;
}
