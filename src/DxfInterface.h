#ifndef GRADEPRO_DXFINTERFACE_H
#define GRADEPRO_DXFINTERFACE_H


#include "dl_creationadapter.h"
#include "DxfData.h"

//DXF_COLOR_HEX=["#000000","#ff0000","#ffff00","#00ff00","#00ffff","#0000ff","#ff00ff","#ffffff","#414141","#808080","#ff0000","#ffaaaa","#bd0000","#bd7e7e","#810000","#815656","#680000","#684545","#4f0000","#4f3535","#ff3f00","#ffbfaa","#bd2e00","#bd8d7e","#811f00","#816056","#681900","#684e45","#4f1300","#4f3b35","#ff7f00","#ffd4aa","#bd5e00","#bd9d7e","#814000","#816b56","#683400","#685645","#4f2700","#4f4235","#ffbf00","#ffeaaa","#bd8d00","#bdad7e","#816000","#817656","#684e00","#685f45","#4f3b00","#4f4935","#ffff00","#ffffaa","#bdbd00","#bdbd7e","#818100","#818156","#686800","#686845","#4f4f00","#4f4f35","#bfff00","#eaffaa","#8dbd00","#adbd7e","#608100","#768156","#4e6800","#5f6845","#3b4f00","#494f35","#7fff00","#d4ffaa","#5ebd00","#9dbd7e","#408100","#6b8156","#346800","#566845","#274f00","#424f35","#3fff00","#bfffaa","#2ebd00","#8dbd7e","#1f8100","#608156","#196800","#4e6845","#134f00","#3b4f35","#00ff00","#aaffaa","#00bd00","#7ebd7e","#008100","#568156","#006800","#456845","#004f00","#354f35","#00ff3f","#aaffbf","#00bd2e","#7ebd8d","#00811f","#568160","#006819","#45684e","#004f13","#354f3b","#00ff7f","#aaffd4","#00bd5e","#7ebd9d","#008140","#56816b","#006834","#456856","#004f27","#354f42","#00ffbf","#aaffea","#00bd8d","#7ebdad","#008160","#568176","#00684e","#45685f","#004f3b","#354f49","#00ffff","#aaffff","#00bdbd","#7ebdbd","#008181","#568181","#006868","#456868","#004f4f","#354f4f","#00bfff","#aaeaff","#008dbd","#7eadbd","#006081","#567681","#004e68","#455f68","#003b4f","#35494f","#007fff","#aad4ff","#005ebd","#7e9dbd","#004081","#566b81","#003468","#455668","#00274f","#35424f","#003fff","#aabfff","#002ebd","#7e8dbd","#001f81","#566081","#001968","#454e68","#00134f","#353b4f","#0000ff","#aaaaff","#0000bd","#7e7ebd","#000081","#565681","#000068","#454568","#00004f","#35354f","#3f00ff","#bfaaff","#2e00bd","#8d7ebd","#1f0081","#605681","#190068","#4e4568","#13004f","#3b354f","#7f00ff","#d4aaff","#5e00bd","#9d7ebd","#400081","#6b5681","#340068","#564568","#27004f","#42354f","#bf00ff","#eaaaff","#8d00bd","#ad7ebd","#600081","#765681","#4e0068","#5f4568","#3b004f","#49354f","#ff00ff","#ffaaff","#bd00bd","#bd7ebd","#810081","#815681","#680068","#684568","#4f004f","#4f354f","#ff00bf","#ffaaea","#bd008d","#bd7ead","#810060","#815676","#68004e","#68455f","#4f003b","#4f3549","#ff007f","#ffaad4","#bd005e","#bd7e9d","#810040","#81566b","#680034","#684556","#4f0027","#4f3542","#ff003f","#ffaabf","#bd002e","#bd7e8d","#81001f","#815660","#680019","#68454e","#4f0013","#4f353b","#333333","#505050","#696969","#828282","#bebebe","#ffffff"];

class DxfInterface : public DL_CreationAdapter{
public:
    DxfInterface();

    void addLayer(const DL_LayerData& data) final;
    void addPoint(const DL_PointData& data) final;
    void addLine(const DL_LineData& data) final;
    void addArc(const DL_ArcData& data) final;
    void addCircle(const DL_CircleData& data) final;
    void addPolyline(const DL_PolylineData& data) final;
    void addVertex(const DL_VertexData& data) final;
    void add3dFace(const DL_3dFaceData& data) final;

    void addTrace(const DL_TraceData &data) final;



    void printAttributes();

    DxfData* getDxfData();

private:
    DxfData* dxfData;
};


#endif //GRADEPRO_DXFINTERFACE_H
