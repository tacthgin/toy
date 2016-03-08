#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../render/Color.h"
#include "../math/Vec4.h"

class Light
{
public:
    Light(int index, int state, int attr, const Color& ambinent, const Color& diffuse, const Color& specular,
          const Vec4& pos, const Vec4& direction, float kc, float kl, float kq, float spotInner, float spotOuter, float pf);
    int _state;
    int _id;
    int _attr;
    
    Color _cAmbient; //环境光强度
    Color _cDiffuse; //散射光强度
    Color _cSpecular; //镜面光强度
    
    Vec4 _pos;
    Vec4 _direction;
    
    float _kc, _kl, _kq;//衰减因子
    
    float _spotInner;//聚光灯内锥
    float _spotOuter;//聚光灯外锥
    float _pf;//聚光灯指数因子
};

#endif //_LIGHT_H_
