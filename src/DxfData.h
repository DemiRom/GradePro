#ifndef GRADEPRO_DXFDATA_H
#define GRADEPRO_DXFDATA_H

#include <vector>
#include "dl_entities.h"
#include "DxfPolyline.h"

class DxfData {
public:
    std::vector<DL_LayerData> layers;
    std::vector<DL_PointData> points;
    std::vector<DL_LineData> lines;
    std::vector<DL_ArcData> arcs;
    std::vector<DL_CircleData> circles;
    std::vector<DL_VertexData> vertices;
    std::vector<DxfPolyline> polylines;
    std::vector<DL_3dFaceData> threedfaces;
};


#endif //GRADEPRO_DXFDATA_H
