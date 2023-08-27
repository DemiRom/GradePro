#include "DxfPolyline.h"

void DxfPolyline::addVertex(const DL_VertexData &vertexData) {
    this->vertices.push_back(vertexData);
}
