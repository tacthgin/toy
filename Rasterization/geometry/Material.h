#ifndef _Material_H_
#define _Material_H_

#include "../render/Color.h"

class Bitmap;
class Material
{
public:
    Material();
    
    int _state;
    int _id;
    char _name[64];
    int _attr;
    
    Color _color;
    
    float _ka, _kd, _ks, _power; //对环境光 散射光 镜面反射光的反射系数和镜面反射指数
    Color _ra, _rd, _rs;//计算得到的颜色和反射系数的积
    
    char _textureFile[80];
    
    Bitmap* _texture;
    
    static std::vector<Material> s_materials;
};

#endif //_Material_H_
