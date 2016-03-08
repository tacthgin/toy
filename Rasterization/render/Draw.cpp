#include "Draw.h"
#include <algorithm>

using namespace std;


Draw::Draw()
:_buffer(nullptr)
,_screenWidth(0)
,_screenHeight(0)
,_dn(nullptr)
{

}

Draw::Draw(int width, int height)
:_buffer(nullptr)
{
    setFrameSize(width, height);
}

Draw::~Draw() {
    if(_buffer)
    {
        delete[] _buffer;
    }
}

void Draw::setFrameSize(int width, int height) {
    if(_buffer)
    {
        delete[] _buffer;
    }
    _buffer = new unsigned int[width * height];
    std::fill_n(_buffer, width * height, 0xffffffff);
    _screenWidth = width;
    _screenHeight = height;
    _minX = 0;
    _maxX = _screenWidth - 1;
    _minY = 0;
    _maxY = _screenHeight - 1;
}

void Draw::generatePPM(const char *file) {
    FILE *f = fopen(file, "w");         // Write image to PPM file.
    fprintf(f, "P3\n%d %d\n%d\n", _screenWidth, _screenHeight, 255);
    for (int i=0; i< _screenWidth * _screenHeight; i++)
        fprintf(f,"%d %d %d ", (_buffer[i] & 0x00ff0000) >> 16, (_buffer[i] & 0x0000ff00) >> 8, (_buffer[i] & 0x000000ff) );
    fclose(f);
}

void Draw::setPiexl(unsigned int x, unsigned int y, const Color& c) {
    if(x >= _screenWidth || y >= _screenHeight)
    {
        return;
    }

    _buffer[y * _screenWidth + x] = c.toUInt();
}

void Draw::drawLine(float x0, float y0, float x1, float y1, const Color& color0, const Color& color1){
    float dx = x1 - x0;
    float dy = y1- y0;
    if(dx == 0.0 && dy == 0.0)
    {
        setPiexl(x1, y1, color1);
        return;
    }

    if(abs(dx) > abs(dy))
    {
        float xmin, xmax;

        if(x0 < x1)
        {
            xmin = x0;
            xmax = x1;
        }else
        {
            xmin = x1;
            xmax = x0;
        }

        float slope = dy / dx;
        for (float x = xmin; x <= xmax ; x += 1.0f) {
            float y = y0 + ((x - x0) * slope);
            Color c = color0 + (color1 - color0) * ((x - x0) / dx);
            setPiexl(x, y, c);
        }
    }else {
        float ymin, ymax;
        if (y0 < y1) {
            ymin = y0;
            ymax = y1;
        } else {
            ymin = y1;
            ymax = y0;
        }

        float slope = dx / dy;
        for (float y = ymin; y <= ymax; y += 1.0f) {
            float x = x0 + ((y - y0) * slope);
            Color c = color0 + (color1 - color0) * ((y - y0) / dy);
            setPiexl(x, y, c);
        }
    }
}

void Draw::drawTriangle(float x0, float y0,
                        float x1, float y1,
                        float x2, float y2, const Color& color)
{
    if((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2))
    {
        return;
    }
    
    if (y1 < y0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    if (y2 < y0) {
        std::swap(x0, x2);
        std::swap(y0, y2);
    }
    
    if (y2 < y1) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }
    
    if (y2 < _minY || y0 > _maxY ||
        (x0 < _minX && x1 < _minX && x2 < _minX) ||
        (x0 > _maxX && x1 > _maxX && x2 > _maxX)) {
        return;
    }
    
    if (y1 == y0) {
        drawTopTriangle(x0, y0, x1, y1, x2, y2, color);
    }else if(y1 == y2)
    {
        drawBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    }else
    {
        float newX = x0 + (0.5 + (y1 - y0) * (x2 - x0) / (y2 - y0));
        drawBottomTriangle(x0, y0, newX, y1, x2, y2, color);
        drawTopTriangle(x1, y1, newX, y1, x2, y2, color);
    }
}

void Draw::drawTopTriangle(float x0, float y0,
                     float x1, float y1,
                     float x2, float y2, const Color& color)
{
    
    if(x1 < x0)
    {
        std::swap(x0, x1);
    }
    
    float dxLeft = (x2 - x0) / (y2 - y0);
    float dxRight = (x2 - x1) / (y2 - y0);
    
    float xs = x0;
    float xe= x1 + 0.5;
    
    if (y0 < _minY) {
        xs = xs + dxLeft * (-y0 + _minY);
        xe = xe + dxRight * (-y0 + _minY);
        y0 = _minY;
    }
    
    if (y2 > _maxY) {
        y2 = _maxY;
    }
    
    unsigned int *dest = _buffer + (unsigned int)(y0 * _screenWidth);
    
    if (x0 >= _minX && x0 <= _maxX &&
        x1 >= _minX && x1 <= _maxX &&
        x2 >= _minX && x2 <= _maxX) {
        for (float y = y0; y <= y2; y += 1.0f, dest += _screenWidth) {
            memset(dest + (unsigned int)xs, color.toUInt(), (unsigned int)((int)xe - (int)xs + 1));
            xs += dxLeft;
            xe += dxRight;
        }
    }else
    {
        for (float y = y0; y <= y2; y += 1.0f, dest += _screenWidth) {
            float left = xs;
            float right = xe;
            
            xs += dxLeft;
            xe += dxRight;
            
            if (left < _minX) {
                left = _minX;
                
                if (right < _minX) {
                    continue;
                }
            }
            
            if (right > _maxX) {
                right = _maxX;
                if (left > _maxX) {
                    continue;
                }
            }
            
            memset(dest + (unsigned int)left, color.toUInt(), (unsigned int)((int)right - (int)left + 1));
        }
    }
    
}

void Draw::drawBottomTriangle(float x0, float y0,
                        float x1, float y1,
                        float x2, float y2, const Color& color)
{
    if(x2 < x1)
    {
        std::swap(x2, x1);
    }
    
    float dxLeft = (x1 - x0) / (y2 - y0);
    float dxRight = (x2 - x0) / (y2 - y0);
    
    float xs = x1;
    float xe= x1;
    
    if (y0 < _minY) {
        xs = xs + dxLeft * (-y0 + _minY);
        xe = xe + dxRight * (-y0 + _minY);
        y0 = _minY;
    }
    
    if (y2 > _maxY) {
        y2 = _maxY;
    }
    
    unsigned int *dest = _buffer + (unsigned int)(y0 * _screenWidth);
    
    if (x0 >= _minX && x0 <= _maxX &&
        x1 >= _minX && x1 <= _maxX &&
        x2 >= _minX && x2 <= _maxX) {
        for (float y = y0; y <= y2; y += 1.0f, dest += _screenWidth) {
            memset(dest + (unsigned int)xs, color.toUInt(), (unsigned int)((int)xe - (int)xs + 1));
            xs += dxLeft;
            xe += dxRight;
        }
    }else
    {
        for (float y = y0; y <= y2; y += 1.0f, dest += _screenWidth) {
            float left = xs;
            float right = xe;
            
            xs += dxLeft;
            xe += dxRight;
            
            if (left < _minX) {
                left = _minX;
                
                if (right < _minX) {
                    continue;
                }
            }
            
            if (right > _maxX) {
                right = _maxX;
                if (left > _maxX) {
                    continue;
                }
            }
            
            memset(dest + (unsigned int)left, color.toUInt(), (unsigned int)((int)right - (int)left + 1));
        }
    }

}

//使用cocos2d方式画图
void Draw::cocoDrawLine(float x0, float y0, float x1, float y1, const Color& color0, const Color& color1)
{
    using namespace cocos2d;
    
    if (_dn == nullptr) {
        return;
    }
    
    _dn->drawLine(cocos2d::Vec2(x0, y0), cocos2d::Vec2(x1, y1), cocos2d::Color4F(color0.r, color0.g, color0.b, color0.a));
}

void Draw::cocoDrawTriangle(float x0, float y0,
                      float x1, float y1,
                      float x2, float y2, const Color& color)
{
    using namespace cocos2d;
    
    if (_dn == nullptr) {
        return;
    }
    
    _dn->drawTriangle(cocos2d::Vec2(x0, y0), cocos2d::Vec2(x1, y1), cocos2d::Vec2(x2, y2), cocos2d::Color4F(color.r, color.g, color.b, color.a));
}



