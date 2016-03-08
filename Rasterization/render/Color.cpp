#include "Color.h"

Color::Color()
{
    set(1.0f, 1.0f, 1.0f, 1.0f);
}

Color::Color(float rr, float bb, float gg, float aa)
{
    set(rr, bb, gg, aa);
}

Color::Color(int rr, int gg, int bb, int aa) {
    set(rr, gg, bb, aa);
}

Color Color::operator*(float val) const {
    float rr = r * val;
    float bb = b * val;
    float gg = g * val;
    float aa = a * val;
    limit(rr, gg, bb, aa);
    return Color(rr, gg, bb, aa);
}

Color Color::operator+(const Color &c) const {
    float rr = r + c.r;
    float gg = g + c.g;
    float bb = b + c.b;
    float aa = a + c.a;
    limit(rr, gg, bb, aa);
    return Color(rr, gg, bb, aa);
}

Color Color::operator-(const Color &c) const {
    float rr = r - c.r;
    float gg = g - c.g;
    float bb = b - c.b;
    float aa = a - c.a;
    limit(rr, gg, bb, aa);
    return Color(rr, gg, bb, aa);
}

void Color::limit(float &rr, float &gg, float &bb, float aa) const{
    rr = rr < 0 ? 0 : rr;
    rr = rr > 1 ? 1 : rr;

    gg = gg < 0 ? 0 : gg;
    gg = gg > 1 ? 1 : gg;

    bb = bb < 0 ? 0 : bb;
    bb = bb > 1 ? 1 : bb;

    aa = aa < 0 ? 0 : aa;
    aa = aa > 1 ? 1 : aa;
}


unsigned int Color::toUInt()const {
    unsigned int val = 0;
    val |= ((unsigned int)(a * 255) << 24);
    val |= ((unsigned int)(r * 255) << 16);
    val |= ((unsigned int)(g * 255) << 8);
    val |= ((unsigned int)(b * 255) << 0);

    return val;
}

void Color::set(int rr, int gg, int bb, int aa) {
    r = (float)rr / 255;
    g = (float)gg / 255;
    b = (float)bb / 255;
    a = (float)aa/ 255;
}

void Color::set(float rr, float gg, float bb, float aa) {
    r = rr;
    g = gg;
    b = bb;
    a = aa;
}
