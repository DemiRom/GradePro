#include "DxfInterface.h"

//#define DXF_INTERFACE_DEBUG

DxfInterface::DxfInterface() {
    dxfData = new DxfData();
};

void DxfInterface::addLayer(const DL_LayerData &data) {
    this->dxfData->layers.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding Layer\n");

    printAttributes();
#endif
}

void DxfInterface::addPoint(const DL_PointData &data) {
    this->dxfData->points.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding Point\n");

    printAttributes();
#endif

}

void DxfInterface::addLine(const DL_LineData &data) {
    this->dxfData->lines.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding Line\n");

    printAttributes();
#endif

}

void DxfInterface::addArc(const DL_ArcData &data) {
    this->dxfData->arcs.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding Arc\n");

    printAttributes();
#endif

}

void DxfInterface::addCircle(const DL_CircleData &data) {
    this->dxfData->circles.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding Circle\n");

    printAttributes();
#endif

}

void DxfInterface::addPolyline(const DL_PolylineData &data) {
    this->dxfData->polylines.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding Polyline\n");

    printAttributes();
#endif

}

void DxfInterface::addVertex(const DL_VertexData &data) {
    this->dxfData->vertex.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding Vertex\n");

    printAttributes();
#endif

}

void DxfInterface::add3dFace(const DL_3dFaceData &data) {
    this->dxfData->threedfaces.push_back(data);
#ifdef DXF_INTERFACE_DEBUG
    printf("Adding 3d\n");

    printAttributes();
#endif
}

void DxfInterface::printAttributes() {

    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor() == 256) {
        printf("BYLAYER");
    } else if (attributes.getColor() == 0) {
        printf("BYBLOCK");
    } else {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth() == -1) {
        printf("BYLAYER");
    } else if (attributes.getWidth() == -2) {
        printf("BYBLOCK");
    } else if (attributes.getWidth() == -3) {
        printf("DEFAULT");
    } else {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLinetype().c_str());
}

DxfData *DxfInterface::getDxfData() {
    return this->dxfData;
}

void DxfInterface::addTrace(const DL_TraceData &data) {

}
