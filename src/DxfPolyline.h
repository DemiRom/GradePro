#ifndef GRADEPRO_DXFPOLYLINE_H
#define GRADEPRO_DXFPOLYLINE_H


#include "dl_entities.h"

class DxfPolyline {
public:
    explicit DxfPolyline(DL_PolylineData data) : polyline(data) {};


    void addVertex(const DL_VertexData& vertexData);


    DL_PolylineData polyline;
    std::vector<DL_VertexData> vertices;
};


#endif //GRADEPRO_DXFPOLYLINE_H
