#!/usr/bin/env python
# coding: utf-8

# In[1]:


import csv
import json
import math
import os
import time
import sys


def rename_label_22(label):
    if label=="leftEar":
        label_kor.append("왼쪽 귀")
    elif label=="leftEye":
        label_kor.append("왼쪽 눈")
    elif label=="nose":
        label_kor.append("코")
    elif label=="rightEye":
        label_kor.append("오른쪽 눈")
    elif label=="rightEar":
        label_kor.append("오른쪽 귀")
    
    elif label=="leftHand":
        label_kor.append("왼쪽 손목")
    elif label=="leftElbow":
        label_kor.append("왼쪽 팔꿈치")
    elif label=="leftShoulder":
        label_kor.append("왼쪽 어깨")
    elif label=="sternum":
        label_kor.append("목")
    elif label=="rightShoulder":
        label_kor.append("오른쪽 어깨")
        
    elif label=="rightElbow":
        label_kor.append("오른쪽 팔꿈치")
    elif label=="rightHand":
        label_kor.append("오른쪽 손목")
    elif label=="leftThigh":
        label_kor.append("왼쪽 엉덩이")
    elif label=="leftKnee":
        label_kor.append("왼쪽 무릎")
    elif label=="leftFoot":
        label_kor.append("왼쪽 발목")
        
    elif label=="LBigToe":
        label_kor.append("왼쪽 엄지발가락")
    elif label=="LHeel":
        label_kor.append("왼쪽 발뒷꿈치")
    elif label=="rightThigh":
        label_kor.append("오른쪽 엉덩이")
    elif label=="rightKnee":
        label_kor.append("오른쪽 무릎")
    elif label=="rightFoot":
        label_kor.append("오른쪽 발목")
  
    elif label=="RBigToe":
        label_kor.append("오른쪽 엄지발가락")
    elif label=="RHeel":
        label_kor.append("오른쪽 발뒷꿈치")



def rename_label_30(label):
    if label=="RightFootEE":
        label_kor.append("오른쪽 발 끝")
    elif label=="RightToeBase":
        label_kor.append("오른쪽 발가락 시작점")
    elif label=="RightFoot":
        label_kor.append("오른쪽 발목")
    elif label=="RightLeg":
        label_kor.append("오른쪽 무릎")
    elif label=="RightUpLeg":
        label_kor.append("오른쪽 엉덩이")
    
    elif label=="LeftFootEE":
        label_kor.append("왼쪽 발 끝")
    elif label=="LeftToeBase":
        label_kor.append("왼쪽 발가락 시작점")
    elif label=="LeftFoot":
        label_kor.append("왼쪽 발목")
    elif label=="LeftLeg":
        label_kor.append("왼쪽 무릎")
    elif label=="LeftUpLeg":
        label_kor.append("왼쪽 엉덩이")
        
    elif label=="RightHandEE":
        label_kor.append("오른쪽 손가락 시작점")
    elif label=="RightHand":
        label_kor.append("오른쪽 손목")
    elif label=="RightForeArm":
        label_kor.append("오른쪽 팔꿈치")
    elif label=="RightArm":
        label_kor.append("오른쪽 어깨")
    elif label=="RightShoulder":
        label_kor.append("오른쪽 쇄골")
        
    elif label=="LeftHandEE":
        label_kor.append("왼쪽 손가락 시작점")
    elif label=="LeftHand":
        label_kor.append("왼쪽 손목")
    elif label=="LeftForeArm":
        label_kor.append("왼쪽 팔꿈치")
    elif label=="LeftArm":
        label_kor.append("왼쪽 어깨")
    elif label=="LeftShoulder":
        label_kor.append("왼쪽 쇄골")
  
    elif label=="HeadEE":
        label_kor.append("정수리")
    elif label=="Head":
        label_kor.append("머리")
    elif label=="Neck":
        label_kor.append("목")
    elif label=="Spine4":
        label_kor.append("척추4")
    elif label=="Spine3":
        label_kor.append("척추3")
    
    elif label=="Spine2":
        label_kor.append("척추2")
    elif label=="Spine1":
        label_kor.append("척추1")
    elif label=="Spine":
        label_kor.append("척추0")
    elif label=="Hips":
        label_kor.append("엉덩이")
    elif label=="Nose":
        label_kor.append("코")



def csvToJson(csvFilePath, jsonFilePath, label_kor, NoOfPoint, width, length):
    i=0
    q=0
    lab=dict()
    data={}
    data["annotation"]=[]
    with open(csvFilePath, encoding='utf-8') as csvf:
        csvReader = csv.DictReader(csvf)  
        for rows in csvReader:
            for key, val in rows.items():
                i=i+1
           
                if(i==5 or i==7 or i==9):
                    k=0
                    q=q+1
                    fin=dict()
                    
                    for j in range(1, int(NoOfPoint)*2+1, 2):
                        lab=dict()
                        lab["x"]=math.trunc(float(val[j])*int(width))
                        lab["y"]=math.trunc(float(val[j+1])*int(length))
                        lab["view"]=1
                        fin[label_kor[k]]=lab
                        k=k+1
                    
                    annotation=dict()
                    pose=dict()
                    location=dict()
                    location["location"]=fin
                    location["label"]=val[0]
                    location["type"]="pose"
                    pose["pose"]=location
                    annotation["annotation"]=pose
                    data["annotation"].append(annotation["annotation"])
                   
    with open(jsonFilePath, 'w', encoding='utf-8') as make_file:
        json.dump(data, make_file, indent="\t", ensure_ascii=False)





print("키포인트의 개수는 csv파일에 입력된 값의 개수에 따라 자동으로 입력됩니다.\n")
print("키포인트의 개수가 다른 csv파일이 동일 폴더 경로에 있을 경우에도 실행 가능합니다.\n\n")


print("csv파일의 폴더 경로를 입력하세요.   ex)C:\\Users\\miso\\test\\csvFile")
path_before=input(": ")
path_before=path_before.replace("\\","\\\\")
index=path_before.rfind("\\")

print("\njson파일은 "+ path_before[0:index].replace("\\\\","\\") + "jsonFile에 저장됩니다.\n")


width=input("가로: ")
length=input("세로: ")

label_kor=[]

for (root, directories, files) in os.walk(path_before):
    for d in directories:
        d_path = os.path.join(root, d)
       
    for file in files:
        file_path = os.path.join(root, file)
        i=0
        try:
            if not os.path.exists(path_before[0:index]+"jsonFile\\"):
                os.makedirs(path_before[0:index]+"jsonFile\\")
        except OSError:
            print("Error: Failed to create the directory.")

        json_file=path_before[0:index]+"jsonFile\\"+file[:-4]+".json"
        #print(json_file)
        label_kor=[]
  
        with open(file_path, encoding='cp949') as csvf:
           
            csvReader = csv.DictReader(csvf)                    
            for rows in csvReader:
                for key, val in rows.items():
                    i=i+1
                    if(i==3):
                        NoOfPoint=int((len(val)-1)/2)
                      
                        fin=dict()
                        
                        for j in range(1, NoOfPoint*2+1, 2):
                            if (NoOfPoint==18):
                                rename_label_18(val[j]);
                            elif (NoOfPoint==21):
                                rename_label_21(val[j]);
                            elif (NoOfPoint==22):
                                rename_label_22(val[j]);
                            elif (NoOfPoint==29):
                                rename_label_29(val[j]);
                            elif (NoOfPoint==30):
                                rename_label_30(val[j]);
                        
        if(NoOfPoint!=len(label_kor)):
            print("keypoint의 개수가 일치하지 않습니다")
            time.sleep(10)
            sys.exit(0)
  
        csvToJson(file_path, json_file, label_kor, NoOfPoint, width, length)
    
print("\n완료")
time.sleep(10)
os.system('puase')
        


# In[ ]:




