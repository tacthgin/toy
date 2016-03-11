#ifndef _FILELOAD_H_
#define _FILELOAD_H_

#include <cstdio>
#include "Vector4d.h"

class Object4D;
class FileLoad
{
public:
    static char* getLinePLG(char *buffer, int maxLength, FILE *fp);
    static void loadObject4DPLG(Object4D *obj, const char* file,
          const Vec4& scale = Vec4(1, 1, 1, 1),
          const Vec4& pos = Vec4(0, 0, 0, 1),
          const Vec4& angle = Vec4(0, 0, 0, 1));
};

#endif //_FILELOAD_H_


