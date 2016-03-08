#ifndef _DRAW_H_
#define _DRAW_H_

#include "Color.h"
#include "cocos2d.h"

class Draw
{
public:
    Draw();
    Draw(int width, int height);
    ~Draw();
    void setFrameSize(int width, int height);
    void setPiexl(unsigned int x, unsigned int y, const Color& c);
    void generatePPM(const char* file);
    
    void drawLine(float x0, float y0, float x1, float y1, const Color& color0, const Color& color1);
    void drawTriangle(float x0, float y0,
                            float x1, float y1,
                      float x2, float y2, const Color& color);
    //使用cocos2d方式画图
    void cocoDrawLine(float x0, float y0, float x1, float y1, const Color& color0, const Color& color1);
    void cocoDrawTriangle(float x0, float y0,
                          float x1, float y1,
                          float x2, float y2, const Color& color);
private:
    void drawTopTriangle(float x0, float y0,
                         float x1, float y1,
                         float x2, float y2, const Color& color);
    void drawBottomTriangle(float x0, float y0,
                            float x1, float y1,
                            float x2, float y2, const Color& color);
private:
    unsigned int *_buffer;
    int _screenWidth;
    int _screenHeight;
    int _minX;
    int _maxX;
    int _minY;
    int _maxY;
    CC_SYNTHESIZE(cocos2d::DrawNode*, _dn, DrawNode);
};

#endif //_DRAW_H_
