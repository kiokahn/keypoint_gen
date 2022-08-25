#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h" 

using namespace rapidjson;

#include "CsvToJson.h"

std::string& rename_label_22(const std::string& label)
{
    std::string label_kor = "";

    if (label.compare("leftEar") == 0)
        label_kor.append("¿ÞÂÊ ±Í");
    else if (label.compare("leftEye") == 0)
        label_kor.append("¿ÞÂÊ ´«");
    else if (label.compare("nose") == 0)
        label_kor.append("ÄÚ");
    else if (label.compare("rightEye") == 0)
        label_kor.append("¿À¸¥ÂÊ ´«");
    else if (label.compare("rightEar") == 0)
        label_kor.append("¿À¸¥ÂÊ ±Í");

    else if (label.compare("leftHand") == 0)
        label_kor.append("¿ÞÂÊ ¼Õ¸ñ");
    else if (label.compare("leftElbow") == 0)
        label_kor.append("¿ÞÂÊ ÆÈ²ÞÄ¡");
    else if (label.compare("leftShoulder") == 0)
        label_kor.append("¿ÞÂÊ ¾î±ú");
    else if (label.compare("sternum") == 0)
        label_kor.append("¸ñ");
    else if (label.compare("rightShoulder") == 0)
        label_kor.append("¿À¸¥ÂÊ ¾î±ú");

    else if (label.compare("rightElbow") == 0)
        label_kor.append("¿À¸¥ÂÊ ÆÈ²ÞÄ¡");
    else if (label.compare("rightHand") == 0)
        label_kor.append("¿À¸¥ÂÊ ¼Õ¸ñ");
    else if (label.compare("leftThigh") == 0)
        label_kor.append("¿ÞÂÊ ¾ûµ¢ÀÌ");
    else if (label.compare("leftKnee") == 0)
        label_kor.append("¿ÞÂÊ ¹«¸­");
    else if (label.compare("leftFoot") == 0)
        label_kor.append("¿ÞÂÊ ¹ß¸ñ");

    else if (label.compare("LBigToe") == 0)
        label_kor.append("¿ÞÂÊ ¾öÁö¹ß°¡¶ô");
    else if (label.compare("LHeel") == 0)
        label_kor.append("¿ÞÂÊ ¹ßµÞ²ÞÄ¡");
    else if (label.compare("rightThigh") == 0)
        label_kor.append("¿À¸¥ÂÊ ¾ûµ¢ÀÌ");
    else if (label.compare("rightKnee") == 0)
        label_kor.append("¿À¸¥ÂÊ ¹«¸­");
    else if (label.compare("rightFoot") == 0)
        label_kor.append("¿À¸¥ÂÊ ¹ß¸ñ");

    else if (label.compare("RBigToe") == 0)
        label_kor.append("¿À¸¥ÂÊ ¾öÁö¹ß°¡¶ô");
    else if (label.compare("RHeel") == 0)
        label_kor.append("¿À¸¥ÂÊ ¹ßµÞ²ÞÄ¡");

	return label_kor;
}

std::string& rename_label_30(const std::string& label)
{
    std::string label_kor = "";

    if (label.compare("RightFootEE") == 0)
        label_kor.append("¿À¸¥ÂÊ ¹ß ³¡");
    else if (label.compare("RightToeBase") == 0)
        label_kor.append("¿À¸¥ÂÊ ¹ß°¡¶ô ½ÃÀÛÁ¡")
    else if (label.compare("RightFoot") == 0)
        label_kor.append("¿À¸¥ÂÊ ¹ß¸ñ");
    else if (label.compare("RightLeg") == 0)
        label_kor.append("¿À¸¥ÂÊ ¹«¸­");
    else if (label.compare("RightUpLeg") == 0)
        label_kor.append("¿À¸¥ÂÊ ¾ûµ¢ÀÌ");

    else if (label.compare("LeftFootEE") == 0)
        label_kor.append("¿ÞÂÊ ¹ß ³¡");
    else if (label.compare("LeftToeBase") == 0)
        label_kor.append("¿ÞÂÊ ¹ß°¡¶ô ½ÃÀÛÁ¡");
    else if (label.compare("LeftFoot") == 0)
        label_kor.append("¿ÞÂÊ ¹ß¸ñ");
    else if (label.compare("LeftLeg") == 0)
        label_kor.append("¿ÞÂÊ ¹«¸­");
    else if (label.compare("LeftUpLeg") == 0)
        label_kor.append("¿ÞÂÊ ¾ûµ¢ÀÌ");

    else if (label.compare("RightHandEE") == 0)
        label_kor.append("¿À¸¥ÂÊ ¼Õ°¡¶ô ½ÃÀÛÁ¡");
    else if (label.compare("RightHand") == 0)
        label_kor.append("¿À¸¥ÂÊ ¼Õ¸ñ");
    else if (label.compare("RightForeArm") == 0)
        label_kor.append("¿À¸¥ÂÊ ÆÈ²ÞÄ¡");
    else if (label.compare("RightArm") == 0)
        label_kor.append("¿À¸¥ÂÊ ¾î±ú");
    else if (label.compare("RightShoulder") == 0)
        label_kor.append("¿À¸¥ÂÊ ¼â°ñ");

    else if (label.compare("LeftHandEE") == 0)
        label_kor.append("¿ÞÂÊ ¼Õ°¡¶ô ½ÃÀÛÁ¡");
    else if (label.compare("LeftHand") == 0)
        label_kor.append("¿ÞÂÊ ¼Õ¸ñ");
    else if (label.compare("LeftForeArm") == 0)
        label_kor.append("¿ÞÂÊ ÆÈ²ÞÄ¡");
    else if (label.compare("LeftArm") == 0)
        label_kor.append("¿ÞÂÊ ¾î±ú");
    else if (label.compare("LeftShoulder") == 0)
        label_kor.append("¿ÞÂÊ ¼â°ñ");

    else if (label.compare("HeadEE") == 0)
        label_kor.append("Á¤¼ö¸®");
    else if (label.compare("Head") == 0)
        label_kor.append("¸Ó¸®");
    else if (label.compare("Neck") == 0)
        label_kor.append("¸ñ");
    else if (label.compare("Spine4") == 0)
        label_kor.append("Ã´Ãß4");
    else if (label.compare("Spine3") == 0)
        label_kor.append("Ã´Ãß3");

    else if (label.compare("Spine2") == 0)
        label_kor.append("Ã´Ãß2");
    else if (label.compare("Spine1") == 0)
        label_kor.append("Ã´Ãß1");
    else if (label.compare("Spine") == 0)
        label_kor.append("Ã´Ãß0");
    else if (label.compare("Hips") == 0)
        label_kor.append("¾ûµ¢ÀÌ");
    else if (label.compare("Nose") == 0)
        label_kor.append("ÄÚ");

   return label_kor;
}

bool csvToJson(
    const std::string& csvFilePath,
    const std::string& jsonFilePath,
    const std::string& label_kor,
    int NoOfPoint, int width, int length) 
{
	return true;
}


CsvToJson::CsvToJson()
{
    m_pdoc = new Document(kObjectType);
}

CsvToJson::~CsvToJson()
{
    delete m_pdoc;
}

void CsvToJson::AddPose()
{

}
