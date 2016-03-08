#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
    float r, g, b, a;
    Color();
    explicit Color(float rr, float gg, float bb, float aa);
    explicit Color(int rr, int gg, int bb, int aa);

    Color operator*(float val)const;
    Color operator+(const Color& c)const;
    Color operator-(const Color& c)const;

    unsigned int toUInt()const;
    void set(int rr = 255, int gg = 255, int bb = 255, int aa = 255);
    void set(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f, float aa = 1.0f);

private:
    void limit(float &rr, float &gg, float &bb, float aa) const;
};

#endif //_COLOR_H_



