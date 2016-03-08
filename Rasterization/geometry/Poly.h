#ifndef _POLY_H_
#define _POLY_H_

#include <vector>
#include "../math/Vec2.h"
#include "../math/Vec4.h"
#include "../render/Color.h"
#include "Vertex.h"

class Poly4D
{
public:
    Poly4D();
    int _state;
    int _attr;//物理属性
    Color _color;//多边形颜色
    Color _colorLit[3];//光照处理后的颜色
    
    std::vector<Vertex>* _vlist;//顶点列表
    std::vector<Vec2>* _tlist;//纹理坐标列表
    
    int _mati;//材质
    
    int _vindex[3]; //顶点列表的索引
    int _tindex[3]; //纹理坐标索引
    float _nLength; //法线长度
};

class PolyFace4D
{
public:
    PolyFace4D();
    PolyFace4D(const PolyFace4D& poly);
    PolyFace4D& operator=(const PolyFace4D& poly);
    
    int _state;
    int _attr;
    Color _color;
    Color _colorLit[3];//光照处理后的颜色
    
    int _mati;
    
    float _nLength; //法线长度
    Vec4 _normal;//多边形法线
    
    float _avgz; //平均z值
    
    Vertex _vlist[3]; //三角形顶点
    Vertex _tvlist[3];//变化后的顶点
};




#endif //_POLY_H_
