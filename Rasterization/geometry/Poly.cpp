#include "Poly.h"

Poly4D::Poly4D()
:_state(0)
,_attr(0)
,_vlist(nullptr)
{

}

PolyFace4D::PolyFace4D()
:_state(0)
,_attr(0)
,_mati(0)
,_avgz(0)
,_nLength(0)
{

}

PolyFace4D::PolyFace4D(const PolyFace4D& poly)
{
    _state = poly._state;
    _attr = poly._attr;
    _color = poly._color;
    _mati = poly._mati;
    _nLength = poly._nLength;
    _avgz = poly._avgz;
    
    memcpy(_colorLit, poly._colorLit, sizeof(_colorLit));
    memcpy(_vlist, poly._vlist, sizeof(_vlist));
    memcpy(_tvlist, poly._tvlist, sizeof(_tvlist));
}

PolyFace4D& PolyFace4D::operator=(const PolyFace4D& poly)
{
    if (&poly != this) {
        _state = poly._state;
        _attr = poly._attr;
        _color = poly._color;
        _mati = poly._mati;
        _nLength = poly._nLength;
        _avgz = poly._avgz;
        
        memcpy(_colorLit, poly._colorLit, sizeof(_colorLit));
        memcpy(_vlist, poly._vlist, sizeof(_vlist));
        memcpy(_tvlist, poly._tvlist, sizeof(_tvlist));
    }
    
    return *this;
}
