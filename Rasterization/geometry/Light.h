#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "../render/Color.h"
#include "Vector4d.h"

class Light
{
public:
    Light(int index, int state, int attr, const Color& ambinent, const Color& diffuse, const Color& specular,
          const Vector4d& pos, const Vector4d& direction, float kc, float kl, float kq, float spotInner, float spotOuter, float pf);
    int _state;
    int _id;
    int _attr;
    
    Color _cAmbient; //环境光强度
    Color _cDiffuse; //散射光强度
    Color _cSpecular; //镜面光强度
    
    Vector4d _pos;
    Vector4d _direction;
    
    float _kc, _kl, _kq;//衰减因子
    
    float _spotInner;//聚光灯内锥
    float _spotOuter;//聚光灯外锥
    float _pf;//聚光灯指数因子
};

#endif //__LIGHT_H__
