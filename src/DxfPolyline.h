#ifndef GRADEPRO_DXFPOLYLINE_H
#define GRADEPRO_DXFPOLYLINE_H


#include "dl_entities.h"

class DxfPolyline {
public:
    DL_PolylineData polyline;
    std::vector<DL_VertexData> vertecies;
};


#endif //GRADEPRO_DXFPOLYLINE_H
