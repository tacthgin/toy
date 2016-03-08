#include "Light.h"

Light::Light(int index, int state, int attr, const Color& ambinent, const Color& diffuse, const Color& specular,
      const Vec4& pos, const Vec4& direction, float kc, float kl, float kq, float spotInner, float spotOuter, float pf)
:_cAmbient(ambinent)
,_cDiffuse(diffuse)
,_cSpecular(specular)
,_pos(pos)
,_direction(direction)
{
    _direction.normalize();
    _id = index;
    _state = state;
    _attr = attr;
    _kc = kc;
    _kl = kl;
    _kq = kq;
    _spotInner = spotInner;
    _spotOuter = spotOuter;
    _pf = pf;
}