# Keypoint generator

최초 개발 : 김대현(울프슨랩, http://wolfsonlab.com/)    
CsvToJson.py : 박원형(미소정보기술, http://www.misoinfo.co.kr/)    
수정 : 안기옥(kiokahn@gazzi.ai, kiokahn76@gmail.com, 주식회사 가치랩스, http://gazzi.ai)    
       &nbsp;&nbsp;&nbsp;&nbsp;안계환(kdsdhgkahn@gmail.com, (주)에어패스, http://www.airpass.co.kr/ko/)     
Tested :  MS WIndows 10 Pro, Windows SDK 10.0.xxxx, Microsoft Visual Studio Community 2022 (64-bit) 

## Usage
```
keypoint_gen.exe times.txt 2DKeypoints(CSV) output -key22
```

times.txt contains time info to extract    
2DKeypoints(CSV) is a directory which contains the input csv files,    
note that you need separate the each person into each sub directory,    
output is the output directory    
-key22 is optional for 22 keypoints, default is 30 keypoints    

## Reference

https://rapidjson.org/