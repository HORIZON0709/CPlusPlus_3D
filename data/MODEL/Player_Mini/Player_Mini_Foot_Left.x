xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 104;
 -0.00411;0.01366;-0.00246;,
 -0.00411;-0.20924;-0.97906;,
 -0.69468;-0.20924;-0.69302;,
 -0.00411;0.01366;-0.00246;,
 -0.98072;-0.20924;-0.00246;,
 -0.00411;0.01366;-0.00246;,
 -0.69468;-0.20924;0.68811;,
 -0.00411;0.01366;-0.00246;,
 -0.00411;-0.20924;0.97415;,
 -0.00411;0.01366;-0.00246;,
 0.68646;-0.20924;0.68811;,
 -0.00411;0.01366;-0.00246;,
 0.97250;-0.20924;-0.00246;,
 -0.00411;0.01366;-0.00246;,
 0.68646;-0.20924;-0.69302;,
 -0.00411;0.01366;-0.00246;,
 -0.00411;-0.20924;-0.97906;,
 -0.00411;-0.83381;-1.76224;,
 -1.24846;-0.83381;-1.24681;,
 -1.76390;-0.83381;-0.00246;,
 -1.24846;-0.83381;1.24190;,
 -0.00411;-0.83381;1.75733;,
 1.24026;-0.83381;1.24190;,
 1.75569;-0.83381;-0.00246;,
 1.24026;-0.83381;-1.24681;,
 -0.00411;-0.83381;-1.76224;,
 -0.00411;-1.73633;-2.19688;,
 -1.55579;-1.73633;-1.55415;,
 -2.19854;-1.73633;-0.00246;,
 -1.55579;-1.73633;1.54923;,
 -0.00411;-1.73633;2.19196;,
 1.54759;-1.73633;1.54923;,
 2.19032;-1.73633;-0.00246;,
 1.54759;-1.73633;-1.55415;,
 -0.00411;-1.73633;-2.19688;,
 -0.00411;-2.73806;-2.19688;,
 -1.55579;-2.73806;-1.55415;,
 -2.19854;-2.73806;-0.00246;,
 -1.55579;-2.73806;1.54923;,
 -0.00411;-2.73806;2.19196;,
 1.54759;-2.73806;1.54923;,
 2.19032;-2.73806;-0.00246;,
 1.54759;-2.73806;-1.55415;,
 -0.00411;-2.73806;-2.19688;,
 -0.00411;-3.64059;-1.76224;,
 -1.24846;-3.64059;-1.24681;,
 -1.76390;-3.64059;-0.00246;,
 -1.24846;-3.64059;1.24190;,
 -0.00411;-3.64059;1.75733;,
 1.24026;-3.64059;1.24190;,
 1.75569;-3.64059;-0.00246;,
 1.24025;-3.64059;-1.24681;,
 -0.00411;-3.64059;-1.76224;,
 -0.00411;-4.26515;-0.97906;,
 -0.69468;-4.26515;-0.69302;,
 -0.98072;-4.26515;-0.00246;,
 -0.69468;-4.26515;0.68811;,
 -0.00411;-4.26515;0.97415;,
 0.68646;-4.26515;0.68811;,
 0.97250;-4.26515;-0.00246;,
 0.68646;-4.26515;-0.69302;,
 -0.00411;-4.26515;-0.97906;,
 -0.00411;-4.48806;-0.00246;,
 -0.00411;-4.48806;-0.00246;,
 -0.00411;-4.48806;-0.00246;,
 -0.00411;-4.48806;-0.00246;,
 -0.00411;-4.48806;-0.00246;,
 -0.00411;-4.48806;-0.00246;,
 -0.00411;-4.48806;-0.00246;,
 -0.00411;-4.48806;-0.00246;,
 1.30578;-2.29669;-7.15216;,
 1.30578;-4.49549;-7.15216;,
 -1.30857;-4.49549;-7.15216;,
 -1.30857;-2.29669;-7.15216;,
 -3.15719;-4.49549;-4.07757;,
 -3.15719;-2.29669;-4.07757;,
 -3.15719;-4.49549;0.27055;,
 -3.15719;-2.29669;0.27055;,
 -1.30857;-4.49549;3.34514;,
 -1.30857;-2.29669;3.34514;,
 1.30578;-4.49549;3.34514;,
 1.30578;-2.29669;3.34514;,
 3.15440;-4.49549;0.27055;,
 3.15440;-2.29669;0.27055;,
 3.15440;-4.49549;-4.07757;,
 3.15440;-2.29669;-4.07757;,
 1.30578;-4.49549;-7.15216;,
 1.30578;-2.29669;-7.15216;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-2.29669;-1.90351;,
 -0.00140;-4.49549;-1.90351;,
 -0.00140;-4.49549;-1.90351;,
 -0.00140;-4.49549;-1.90351;,
 -0.00140;-4.49549;-1.90351;,
 -0.00140;-4.49549;-1.90351;,
 -0.00140;-4.49549;-1.90351;,
 -0.00140;-4.49549;-1.90351;,
 -0.00140;-4.49549;-1.90351;;
 
 80;
 3;0,1,2;,
 3;3,2,4;,
 3;5,4,6;,
 3;7,6,8;,
 3;9,8,10;,
 3;11,10,12;,
 3;13,12,14;,
 3;15,14,16;,
 4;1,17,18,2;,
 4;2,18,19,4;,
 4;4,19,20,6;,
 4;6,20,21,8;,
 4;8,21,22,10;,
 4;10,22,23,12;,
 4;12,23,24,14;,
 4;14,24,25,16;,
 4;17,26,27,18;,
 4;18,27,28,19;,
 4;19,28,29,20;,
 4;20,29,30,21;,
 4;21,30,31,22;,
 4;22,31,32,23;,
 4;23,32,33,24;,
 4;24,33,34,25;,
 4;26,35,36,27;,
 4;27,36,37,28;,
 4;28,37,38,29;,
 4;29,38,39,30;,
 4;30,39,40,31;,
 4;31,40,41,32;,
 4;32,41,42,33;,
 4;33,42,43,34;,
 4;35,44,45,36;,
 4;36,45,46,37;,
 4;37,46,47,38;,
 4;38,47,48,39;,
 4;39,48,49,40;,
 4;40,49,50,41;,
 4;41,50,51,42;,
 4;42,51,52,43;,
 4;44,53,54,45;,
 4;45,54,55,46;,
 4;46,55,56,47;,
 4;47,56,57,48;,
 4;48,57,58,49;,
 4;49,58,59,50;,
 4;50,59,60,51;,
 4;51,60,61,52;,
 3;53,62,54;,
 3;54,63,55;,
 3;55,64,56;,
 3;56,65,57;,
 3;57,66,58;,
 3;58,67,59;,
 3;59,68,60;,
 3;60,69,61;,
 4;70,71,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;77,76,78,79;,
 4;79,78,80,81;,
 4;81,80,82,83;,
 4;83,82,84,85;,
 4;85,84,86,87;,
 3;88,70,73;,
 3;89,73,75;,
 3;90,75,77;,
 3;91,77,79;,
 3;92,79,81;,
 3;93,81,83;,
 3;94,83,85;,
 3;95,85,87;,
 3;96,72,71;,
 3;97,74,72;,
 3;98,76,74;,
 3;99,78,76;,
 3;100,80,78;,
 3;101,82,80;,
 3;102,84,82;,
 3;103,86,84;;
 
 MeshMaterialList {
  4;
  80;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.674100;0.152100;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   10.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.501600;0.501600;0.501600;1.000000;;
   5.000000;
   0.550000;0.550000;0.550000;;
   0.062700;0.062700;0.062700;;
  }
 }
 MeshNormals {
  60;
  0.000000;1.000000;-0.000001;,
  -0.000001;0.902353;-0.430999;,
  -0.304761;0.902353;-0.304763;,
  -0.430998;0.902353;-0.000001;,
  -0.304761;0.902353;0.304762;,
  -0.000001;0.902353;0.430998;,
  0.304759;0.902354;0.304760;,
  0.430995;0.902355;-0.000001;,
  0.304759;0.902354;-0.304761;,
  -0.000002;0.626423;-0.779484;,
  -0.551177;0.626421;-0.551181;,
  -0.779484;0.626422;-0.000001;,
  -0.551179;0.626419;0.551182;,
  -0.000002;0.626419;0.779486;,
  0.551178;0.626421;0.551180;,
  0.779484;0.626422;-0.000001;,
  0.551176;0.626423;-0.551179;,
  -0.000002;0.224080;-0.974571;,
  -0.689123;0.224079;-0.689129;,
  -0.974571;0.224079;-0.000000;,
  -0.689123;0.224076;0.689129;,
  -0.000002;0.224076;0.974572;,
  0.689125;0.224076;0.689127;,
  0.974572;0.224076;-0.000000;,
  0.689125;0.224078;-0.689127;,
  -0.000002;-0.224080;-0.974571;,
  -0.689123;-0.224078;-0.689129;,
  -0.974571;-0.224079;-0.000000;,
  -0.689124;-0.224076;0.689129;,
  -0.000002;-0.224075;0.974572;,
  0.689126;-0.224075;0.689127;,
  0.974571;-0.224077;-0.000001;,
  0.689124;-0.224080;-0.689127;,
  -0.000001;-0.626426;-0.779481;,
  -0.551176;-0.626423;-0.551179;,
  -0.779483;-0.626424;-0.000001;,
  -0.551177;-0.626422;0.551180;,
  -0.000002;-0.626422;0.779484;,
  0.551177;-0.626424;0.551178;,
  0.779481;-0.626426;-0.000002;,
  0.551174;-0.626426;-0.551178;,
  -0.000000;-0.902352;-0.431000;,
  -0.304762;-0.902352;-0.304764;,
  -0.430999;-0.902352;-0.000001;,
  -0.304762;-0.902353;0.304762;,
  -0.000001;-0.902353;0.430998;,
  0.304760;-0.902354;0.304760;,
  0.430996;-0.902354;-0.000002;,
  0.304760;-0.902353;-0.304763;,
  0.000000;-1.000000;-0.000001;,
  0.000000;1.000000;0.000000;,
  0.492297;0.000000;-0.870427;,
  -0.492297;0.000000;-0.870427;,
  -0.963592;0.000000;-0.267379;,
  -0.963592;0.000000;0.267379;,
  -0.492297;0.000000;0.870427;,
  0.492297;0.000000;0.870427;,
  0.963592;0.000000;0.267379;,
  0.963592;0.000000;-0.267379;,
  0.000000;-1.000000;-0.000000;;
  80;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,16,8;,
  4;8,16,9,1;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,17,9;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,32,24;,
  4;24,32,25,17;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,40,32;,
  4;32,40,33,25;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,48,40;,
  4;40,48,41,33;,
  3;41,49,42;,
  3;42,49,43;,
  3;43,49,44;,
  3;44,49,45;,
  3;45,49,46;,
  3;46,49,47;,
  3;47,49,48;,
  3;48,49,41;,
  4;51,51,52,52;,
  4;52,52,53,53;,
  4;53,53,54,54;,
  4;54,54,55,55;,
  4;55,55,56,56;,
  4;56,56,57,57;,
  4;57,57,58,58;,
  4;58,58,51,51;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;50,50,50;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;;
 }
 MeshTextureCoords {
  104;
  0.062500;0.000000;,
  0.000000;0.142860;,
  0.125000;0.142860;,
  0.187500;0.000000;,
  0.250000;0.142860;,
  0.312500;0.000000;,
  0.375000;0.142860;,
  0.437500;0.000000;,
  0.500000;0.142860;,
  0.562500;0.000000;,
  0.625000;0.142860;,
  0.687500;0.000000;,
  0.750000;0.142860;,
  0.812500;0.000000;,
  0.875000;0.142860;,
  0.937500;0.000000;,
  1.000000;0.142860;,
  0.000000;0.285710;,
  0.125000;0.285710;,
  0.250000;0.285710;,
  0.375000;0.285710;,
  0.500000;0.285710;,
  0.625000;0.285710;,
  0.750000;0.285710;,
  0.875000;0.285710;,
  1.000000;0.285710;,
  0.000000;0.428570;,
  0.125000;0.428570;,
  0.250000;0.428570;,
  0.375000;0.428570;,
  0.500000;0.428570;,
  0.625000;0.428570;,
  0.750000;0.428570;,
  0.875000;0.428570;,
  1.000000;0.428570;,
  0.000000;0.571430;,
  0.125000;0.571430;,
  0.250000;0.571430;,
  0.375000;0.571430;,
  0.500000;0.571430;,
  0.625000;0.571430;,
  0.750000;0.571430;,
  0.875000;0.571430;,
  1.000000;0.571430;,
  0.000000;0.714290;,
  0.125000;0.714290;,
  0.250000;0.714290;,
  0.375000;0.714290;,
  0.500000;0.714290;,
  0.625000;0.714290;,
  0.750000;0.714290;,
  0.875000;0.714290;,
  1.000000;0.714290;,
  0.000000;0.857140;,
  0.125000;0.857140;,
  0.250000;0.857140;,
  0.375000;0.857140;,
  0.500000;0.857140;,
  0.625000;0.857140;,
  0.750000;0.857140;,
  0.875000;0.857140;,
  1.000000;0.857140;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}