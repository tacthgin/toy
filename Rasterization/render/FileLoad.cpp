#include "FileLoad.h"
#include "../geometry/Object4D.h"
#include <cstdlib>

#define PLX_RGB_MASK 0x8000 //抽取RGB/索引颜色的掩码
#define PLX_SHADE_MODE_MASK 0X6000
#define PLX_2SIDE_MASK 0x1000
#define PLX_COLOR_MASK 0X0fff

#define PLX_COLOR_MODE_RGB_FLAG 0x8000//rgb
#define PLX_COLOR_MODE_INDEXED_FLAG 0x0000//8位索引

#define PLX_2SIDED_FLAG 0x1000//双面
#define PLX_1SIDED 0x0000 //单面

#define PLX_SHADE_MODE_PURE_FLAG 0x0000 //固定颜色
#define PLX_SHADE_MODE_CONSTANT_FLAG 0x0000
#define PLX_SHADE_MODE_FLAT_FLAG 0x2000 //恒定着色
#define PLX_SHADE_MODE_GOURAUD_FLAG 0x4000 //gouraud着色
#define PLX_SHADE_MODE_PHONG_FLAG 0x6000 //phone着色
#define PLX_SHADE_MODE_FAST_PHONG_FLAG 0x6000 //phone着色

char *FileLoad::getLinePLG(char *buffer, int maxLength, FILE *fp)
{
    int index = 0;
    int length = 0;

    while(1)
    {
        if(!fgets(buffer, maxLength, fp))
            return nullptr;

        for (length = strlen(buffer), index = 0;isspace(buffer[index]); index++);

        if(index >= length || buffer[index] == '#')
            continue;

        return (&buffer[index]);
    }

    return nullptr;
}

void FileLoad::loadObject4DPLG(Object4D *obj, const char *file, const Vec4 &scale, const Vec4 &pos, const Vec4 &angle)
{
    FILE *fp = fopen(file, "r");
    if(!fp)
    {
        return;
    }
    
    obj->_state = OBJECT4D_STATE_ACTIVE | OBJECT4D_STATE_VISIBLE;
    obj->_worldPos = pos;
    obj->_frameNums = 1;
    obj->_curFrame = 0;
    obj->_attr = OBJECT4D_ATTR_SINGLE_FRAME;
    
    char buffer[256] = "";
    char *objData = nullptr;

    if(!(objData = getLinePLG(buffer, 256, fp)))//读取模型数据
    {
        return;
    }
    
    int vertices = 0;
    int polyNums = 0;
    sscanf(objData, "%s %d %d",obj->_name, &vertices, &polyNums);
    
    obj->init(vertices, polyNums, obj->_frameNums);

    for (int i = 0; i < vertices; ++i)
    {
        if(!(objData = getLinePLG(buffer, 256, fp)))//读取顶点数据
        {
            return;
        }
        
        Vertex v;
        sscanf(objData, "%f %f %f", &v.x, &v.y, &v.z);
        v.w = 1;
        v.v *= scale;
        
        SET_BIT(v.attr, VERTEX4D_ATTR_POINT);
        obj->_vlist[i] = v;
    }

    obj->computeRadius();//计算平均半径最大半径

    int polySurfaceDesc = 0;
    int polyVertNums = 0;
    char polyDesc[8] = "";

    //加载多边形列表
    for (int poly = 0; poly < polyNums; ++poly) {
        if(!(objData = getLinePLG(buffer, 256, fp)))//读取多边形描述
        {
            return;
        }

        Poly4D p4d;
        sscanf(objData, "%s %d %d %d %d", polyDesc, &polyVertNums, &p4d._vindex[0], &p4d._vindex[1], &p4d._vindex[2]);//顶点总是3个

        if(polyDesc[0] == '0' && toupper(polyDesc[1]) == 'X')//面描述符
        {
            sscanf(polyDesc, "%x", &polySurfaceDesc);
        } else
        {
            polySurfaceDesc = atoi(polyDesc);
        }
        
        if (polySurfaceDesc & PLX_2SIDED_FLAG) {
            SET_BIT(p4d._attr, POLY4D_ATTR_2SIDE);
        }

        //颜色模式
        if(polySurfaceDesc & PLX_COLOR_MODE_RGB_FLAG)
        {
            SET_BIT(p4d._attr, POLY4D_ATTR_RGB16);

            int red = ((polySurfaceDesc & 0x0f00) >> 8);
            int green = ((polySurfaceDesc & 0x00f0) >> 4);
            int blue = (polySurfaceDesc & 0x000f);

            p4d._color.set(red, green, blue, 255);
        }else
        {
            SET_BIT(p4d._attr, POLY4D_ATTR_8BITCOLOR);
            int red = ((polySurfaceDesc & 0x00e0) >> 5);
            int green = ((polySurfaceDesc & 0x001c) >> 2);
            int blue = (polySurfaceDesc & 0x0003);
            p4d._color.set(red, green, blue);
        }

        int shadeMode = (polySurfaceDesc & PLX_SHADE_MODE_MASK);
        switch (shadeMode)
        {
            case PLX_SHADE_MODE_PURE_FLAG:
            {
                SET_BIT(p4d._attr, POLY4D_ATTR_SHADE_MODE_PURE);
            }break;

            case PLX_SHADE_MODE_FLAT_FLAG:
            {
                SET_BIT(p4d._attr, POLY4D_ATTR_SHADE_MODE_FLAT);
            }break;

            case PLX_SHADE_MODE_GOURAUD_FLAG:
            {
                SET_BIT(p4d._attr, POLY4D_ATTR_SHADE_MODE_GOURAUD);
                SET_BIT(obj->_vlist[p4d._vindex[0]].attr, VERTEX4D_ATTR_NORMAL);
                SET_BIT(obj->_vlist[p4d._vindex[1]].attr, VERTEX4D_ATTR_NORMAL);
                SET_BIT(obj->_vlist[p4d._vindex[2]].attr, VERTEX4D_ATTR_NORMAL);
            }break;

            case PLX_SHADE_MODE_PHONG_FLAG:
            {
                SET_BIT(p4d._attr, POLY4D_ATTR_SHADE_MODE_PHONG);
                SET_BIT(obj->_vlist[p4d._vindex[0]].attr, VERTEX4D_ATTR_NORMAL);
                SET_BIT(obj->_vlist[p4d._vindex[1]].attr, VERTEX4D_ATTR_NORMAL);
                SET_BIT(obj->_vlist[p4d._vindex[2]].attr, VERTEX4D_ATTR_NORMAL);
            }break;
        }

        p4d._state = POLY4D_STATE_ACTIVE;
        SET_BIT(p4d._attr, POLY4D_ATTR_DISABLE_MATERIAL);
        p4d._vlist = &obj->_vlist;
        p4d._tlist = &obj->_tlist;
        obj->_polyList.push_back(p4d);
    }
    
    obj->computePolyNormals();
    obj->computeVertexNormals();

    fclose(fp);
}