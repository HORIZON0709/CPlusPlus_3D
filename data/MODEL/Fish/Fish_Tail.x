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
 156;
 0.48560;20.59669;13.41244;,
 0.48560;19.86641;10.11736;,
 -0.47998;19.86641;10.11736;,
 -0.47998;20.59669;13.41244;,
 0.48561;-0.05525;-0.06689;,
 0.48561;-0.05587;11.60567;,
 -0.47997;-0.05587;11.60567;,
 -0.47998;-0.05525;-0.06689;,
 0.48560;4.10902;1.77687;,
 -0.47998;4.10902;1.77687;,
 -0.47998;7.18945;2.29508;,
 0.48560;7.18945;2.29508;,
 0.48561;4.07271;10.19418;,
 0.48561;4.11954;9.65860;,
 0.48561;4.11954;9.65860;,
 0.48561;-0.05587;11.60567;,
 0.48561;4.15382;9.26755;,
 0.48561;4.15382;9.26755;,
 0.48561;-0.05587;11.60567;,
 0.48560;4.24745;8.19667;,
 0.48560;4.24745;8.19667;,
 0.48561;-0.05587;11.60567;,
 0.48561;4.46310;5.73123;,
 0.48561;4.46310;5.73123;,
 0.48561;-0.05587;11.60567;,
 -0.47998;4.11954;9.65860;,
 -0.47998;4.07271;10.19418;,
 -0.47998;4.15377;9.26752;,
 -0.47997;-0.05587;11.60567;,
 -0.47998;4.11954;9.65860;,
 -0.47998;4.24745;8.19662;,
 -0.47997;-0.05587;11.60567;,
 -0.47998;4.15377;9.26752;,
 -0.47998;4.46310;5.73123;,
 -0.47997;-0.05587;11.60567;,
 -0.47998;4.24745;8.19662;,
 -0.47998;4.46310;5.73123;,
 -0.47997;-0.05587;11.60567;,
 0.48560;10.09937;3.31748;,
 -0.47998;10.09937;3.31748;,
 -0.47998;12.81793;4.27273;,
 0.48560;12.81793;4.27273;,
 0.48561;9.57838;9.27265;,
 0.48561;9.46839;10.52979;,
 0.48561;9.70810;7.79010;,
 0.48561;9.57838;9.27265;,
 0.48561;9.86892;5.95238;,
 0.48561;9.70810;7.79010;,
 0.48561;9.86892;5.95238;,
 -0.47997;9.46839;10.52979;,
 -0.47998;9.57838;9.27265;,
 -0.47998;9.57838;9.27265;,
 -0.47998;9.70810;7.79010;,
 -0.47998;9.70810;7.79010;,
 -0.47998;9.86892;5.95238;,
 -0.47998;9.86892;5.95238;,
 0.48561;15.05761;5.65473;,
 -0.47998;15.05761;5.65473;,
 -0.47998;17.18597;6.96802;,
 0.48561;17.18597;6.96802;,
 0.48561;14.73364;9.35813;,
 0.48561;14.57416;11.18108;,
 0.48560;14.88865;7.58602;,
 0.48561;14.73364;9.35813;,
 0.48560;14.88865;7.58602;,
 -0.47997;14.57416;11.18108;,
 -0.47998;14.73364;9.35813;,
 -0.47998;14.73364;9.35813;,
 -0.47998;14.88865;7.58602;,
 -0.47998;14.88865;7.58602;,
 0.48561;18.48435;8.49343;,
 -0.47998;18.48435;8.49343;,
 0.48561;18.39739;9.48768;,
 0.48561;18.16210;12.17664;,
 0.48561;18.39739;9.48768;,
 -0.47998;18.16210;12.17664;,
 -0.47998;18.39739;9.48768;,
 -0.47998;18.39739;9.48768;,
 0.48560;-20.59185;13.41241;,
 -0.47998;-20.59185;13.41241;,
 -0.47998;-19.86154;10.11736;,
 0.48560;-19.86154;10.11736;,
 0.48561;0.06023;-0.06689;,
 -0.47998;0.06023;-0.06689;,
 -0.47997;0.06083;11.60567;,
 0.48561;0.06083;11.60567;,
 0.48560;-4.10408;1.77687;,
 -0.47998;-4.10408;1.77687;,
 0.48560;-7.18449;2.29508;,
 -0.47998;-7.18449;2.29508;,
 0.48561;-4.06775;10.19418;,
 0.48561;-4.11458;9.65861;,
 0.48561;-4.11458;9.65861;,
 0.48561;-4.14886;9.26755;,
 0.48561;0.06083;11.60567;,
 0.48561;-4.14886;9.26755;,
 0.48560;-4.24251;8.19667;,
 0.48561;0.06083;11.60567;,
 0.48560;-4.24251;8.19667;,
 0.48561;-4.45815;5.73123;,
 0.48561;0.06083;11.60567;,
 0.48561;-4.45815;5.73123;,
 0.48561;0.06083;11.60567;,
 -0.47998;-4.11458;9.65861;,
 -0.47998;-4.06774;10.19418;,
 -0.47998;-4.14881;9.26752;,
 -0.47998;-4.11458;9.65861;,
 -0.47997;0.06083;11.60567;,
 -0.47998;-4.24251;8.19662;,
 -0.47998;-4.14881;9.26752;,
 -0.47997;0.06083;11.60567;,
 -0.47998;-4.45815;5.73123;,
 -0.47998;-4.24251;8.19662;,
 -0.47997;0.06083;11.60567;,
 -0.47998;-4.45815;5.73123;,
 -0.47997;0.06083;11.60567;,
 0.48560;-10.09440;3.31748;,
 -0.47998;-10.09440;3.31748;,
 0.48560;-12.81293;4.27273;,
 -0.47998;-12.81293;4.27273;,
 0.48561;-9.57337;9.27265;,
 0.48561;-9.46337;10.52979;,
 0.48561;-9.70311;7.79010;,
 0.48561;-9.57337;9.27265;,
 0.48561;-9.86393;5.95238;,
 0.48561;-9.70311;7.79010;,
 0.48561;-9.86393;5.95238;,
 -0.47997;-9.46337;10.52979;,
 -0.47998;-9.57337;9.27265;,
 -0.47998;-9.57337;9.27265;,
 -0.47998;-9.70311;7.79010;,
 -0.47998;-9.70311;7.79010;,
 -0.47998;-9.86393;5.95238;,
 -0.47998;-9.86393;5.95238;,
 0.48561;-15.05262;5.65473;,
 -0.47998;-15.05262;5.65473;,
 0.48561;-17.18106;6.96802;,
 -0.47998;-17.18106;6.96802;,
 0.48561;-14.72862;9.35813;,
 0.48561;-14.56914;11.18108;,
 0.48560;-14.88366;7.58602;,
 0.48561;-14.72862;9.35813;,
 0.48560;-14.88366;7.58602;,
 -0.47997;-14.56914;11.18108;,
 -0.47998;-14.72862;9.35813;,
 -0.47998;-14.72862;9.35813;,
 -0.47998;-14.88366;7.58602;,
 -0.47998;-14.88366;7.58602;,
 0.48561;-18.47950;8.49343;,
 -0.47998;-18.47950;8.49343;,
 0.48561;-18.39249;9.48768;,
 0.48561;-18.15721;12.17664;,
 0.48561;-18.39249;9.48768;,
 -0.47998;-18.15721;12.17664;,
 -0.47998;-18.39249;9.48768;,
 -0.47998;-18.39249;9.48768;;
 
 118;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;8,9,10,11;,
 3;12,5,13;,
 3;14,15,16;,
 3;17,18,19;,
 3;20,21,22;,
 3;8,11,23;,
 4;8,23,24,4;,
 3;25,6,26;,
 3;27,28,29;,
 3;30,31,32;,
 3;33,34,35;,
 3;36,10,9;,
 4;36,9,7,37;,
 4;12,26,6,5;,
 4;38,11,10,39;,
 4;38,39,40,41;,
 4;42,43,12,13;,
 4;44,45,14,16;,
 4;46,47,17,19;,
 3;38,41,48;,
 4;38,48,20,22;,
 3;38,22,11;,
 4;49,50,25,26;,
 4;51,52,27,29;,
 4;53,54,30,32;,
 3;55,40,39;,
 4;55,39,10,33;,
 3;55,33,35;,
 4;43,49,26,12;,
 4;56,41,40,57;,
 4;56,57,58,59;,
 4;60,61,43,42;,
 4;62,63,45,44;,
 3;56,59,64;,
 4;56,64,47,46;,
 3;56,46,41;,
 4;65,66,50,49;,
 4;67,68,52,51;,
 3;69,58,57;,
 4;69,57,40,54;,
 3;69,54,53;,
 4;61,65,49,43;,
 4;70,59,58,71;,
 4;70,71,2,1;,
 4;72,1,0,73;,
 4;72,73,61,60;,
 3;70,1,74;,
 4;70,74,63,62;,
 3;70,62,59;,
 4;75,3,2,76;,
 4;75,76,66,65;,
 3;77,2,71;,
 4;77,71,58,68;,
 3;77,68,67;,
 4;73,0,3,75;,
 4;73,75,65,61;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,83,82;,
 4;86,88,89,87;,
 3;90,91,85;,
 3;92,93,94;,
 3;95,96,97;,
 3;98,99,100;,
 3;86,101,88;,
 4;86,82,102,101;,
 3;103,104,84;,
 3;105,106,107;,
 3;108,109,110;,
 3;111,112,113;,
 3;114,87,89;,
 4;114,115,83,87;,
 4;90,85,84,104;,
 4;116,117,89,88;,
 4;116,118,119,117;,
 4;120,91,90,121;,
 4;122,93,92,123;,
 4;124,96,95,125;,
 3;116,126,118;,
 4;116,99,98,126;,
 3;116,88,99;,
 4;127,104,103,128;,
 4;129,106,105,130;,
 4;131,109,108,132;,
 3;133,117,119;,
 4;133,111,89,117;,
 3;133,112,111;,
 4;121,90,104,127;,
 4;134,135,119,118;,
 4;134,136,137,135;,
 4;138,120,121,139;,
 4;140,122,123,141;,
 3;134,142,136;,
 4;134,124,125,142;,
 3;134,118,124;,
 4;143,127,128,144;,
 4;145,129,130,146;,
 3;147,135,137;,
 4;147,132,119,135;,
 3;147,131,132;,
 4;139,121,127,143;,
 4;148,149,137,136;,
 4;148,81,80,149;,
 4;150,151,78,81;,
 4;150,138,139,151;,
 3;148,152,81;,
 4;148,140,141,152;,
 3;148,136,140;,
 4;153,154,80,79;,
 4;153,143,144,154;,
 3;155,149,80;,
 4;155,146,137,149;,
 3;155,145,146;,
 4;151,153,79,78;,
 4;151,139,143,153;;
 
 MeshMaterialList {
  5;
  118;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.583200;0.583200;0.620800;1.000000;;
   5.000000;
   0.400000;0.400000;0.400000;;
   0.072900;0.072900;0.077600;;
  }
  Material {
   0.000000;0.000000;0.549000;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.808200;0.808200;0.000000;1.000000;;
   5.000000;
   0.100000;0.100000;0.100000;;
   0.089800;0.089800;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   2.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  106;
  0.000000;-1.000000;-0.000054;,
  0.000000;0.976310;-0.216377;,
  0.000000;0.895339;-0.445385;,
  0.000000;0.651259;-0.758856;,
  0.000000;0.430804;-0.902446;,
  0.000000;0.249605;-0.968348;,
  1.000000;0.000000;0.000000;,
  0.000000;0.287619;-0.957745;,
  -1.000000;-0.000000;0.000001;,
  -1.000000;-0.000001;0.000001;,
  -1.000000;-0.000001;-0.000000;,
  -1.000000;-0.000001;-0.000000;,
  1.000000;-0.000001;-0.000002;,
  1.000000;-0.000000;-0.000002;,
  1.000000;0.000001;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000001;,
  0.000000;0.331498;-0.943456;,
  -1.000000;0.000000;0.000003;,
  -1.000000;0.000000;0.000002;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;-0.000002;,
  1.000000;-0.000000;-0.000001;,
  0.000000;0.525123;-0.851026;,
  -1.000000;-0.000001;0.000003;,
  -1.000000;-0.000000;0.000001;,
  1.000000;-0.000001;0.000001;,
  1.000000;0.000002;-0.000000;,
  0.000000;0.761522;-0.648139;,
  -1.000000;-0.000001;0.000001;,
  1.000000;0.000002;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  0.000000;1.000000;-0.000052;,
  0.000000;-0.976307;-0.216389;,
  0.000000;-0.895338;-0.445388;,
  0.000000;-0.651245;-0.758868;,
  0.000000;-0.430804;-0.902446;,
  0.000000;-0.249606;-0.968348;,
  0.000000;-0.287617;-0.957745;,
  -1.000000;0.000000;0.000001;,
  -1.000000;0.000001;0.000001;,
  -1.000000;0.000001;-0.000000;,
  -1.000000;0.000001;-0.000000;,
  1.000000;0.000001;-0.000002;,
  1.000000;0.000000;-0.000002;,
  1.000000;-0.000001;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000001;,
  0.000000;-0.331500;-0.943455;,
  -1.000000;-0.000000;0.000003;,
  -1.000000;-0.000000;0.000002;,
  1.000000;0.000000;-0.000002;,
  1.000000;0.000000;-0.000001;,
  0.000000;-0.525115;-0.851031;,
  -1.000000;0.000001;0.000003;,
  -1.000000;0.000000;0.000001;,
  1.000000;0.000001;0.000001;,
  1.000000;-0.000002;-0.000000;,
  0.000000;-0.761517;-0.648145;,
  -1.000000;0.000001;0.000001;,
  1.000000;-0.000002;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.404850;-0.914383;,
  1.000000;0.000000;-0.000001;,
  1.000000;0.000001;-0.000001;,
  1.000000;0.000000;-0.000002;,
  1.000000;0.000001;-0.000001;,
  -1.000000;-0.000001;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000001;0.000000;,
  -0.000001;0.133256;0.991082;,
  -0.000002;0.323499;0.946228;,
  1.000000;0.000000;-0.000001;,
  1.000000;0.000000;-0.000003;,
  0.000000;-0.094357;0.995538;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000002;0.000002;,
  0.000000;-0.197463;0.980310;,
  1.000000;0.000004;0.000000;,
  1.000000;0.000003;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.361790;0.932260;,
  0.000000;-0.452628;0.891699;,
  0.000000;-0.404846;-0.914385;,
  1.000000;-0.000000;-0.000001;,
  1.000000;-0.000001;-0.000001;,
  1.000000;-0.000000;-0.000002;,
  1.000000;-0.000001;-0.000001;,
  -1.000000;0.000001;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000001;0.000000;,
  -0.000001;-0.133256;0.991082;,
  -0.000002;-0.323500;0.946228;,
  1.000000;-0.000000;-0.000001;,
  1.000000;-0.000000;-0.000003;,
  0.000000;0.094357;0.995538;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000002;0.000002;,
  0.000000;0.197459;0.980311;,
  1.000000;-0.000004;-0.000000;,
  1.000000;-0.000004;-0.000000;,
  1.000000;-0.000000;0.000000;,
  0.000000;0.361777;0.932264;,
  0.000000;0.452613;0.891707;;
  118;
  4;1,2,2,1;,
  4;0,0,0,0;,
  4;7,64,64,7;,
  4;7,7,5,5;,
  3;6,65,6;,
  3;6,65,12;,
  3;12,65,13;,
  3;13,65,14;,
  3;66,67,14;,
  4;66,14,65,68;,
  3;9,69,8;,
  3;10,69,9;,
  3;11,69,10;,
  3;15,69,11;,
  3;15,21,70;,
  4;15,70,71,69;,
  4;72,72,73,73;,
  4;18,5,5,18;,
  4;18,18,4,4;,
  4;16,6,6,6;,
  4;17,16,6,12;,
  4;22,17,12,13;,
  3;74,75,22;,
  4;74,22,13,14;,
  3;74,14,67;,
  4;19,20,9,8;,
  4;20,21,10,9;,
  4;21,21,11,10;,
  3;21,21,21;,
  4;21,21,21,15;,
  3;21,15,11;,
  4;76,76,72,72;,
  4;24,4,4,24;,
  4;24,24,3,3;,
  4;23,6,6,16;,
  4;27,23,16,17;,
  3;77,78,27;,
  4;77,27,17,22;,
  3;77,22,75;,
  4;25,26,20,19;,
  4;26,21,21,20;,
  3;21,21,21;,
  4;21,21,21,21;,
  3;21,21,21;,
  4;79,79,76,76;,
  4;29,3,3,29;,
  4;29,29,2,2;,
  4;31,80,81,28;,
  4;31,28,6,23;,
  3;82,80,31;,
  4;82,31,23,27;,
  3;82,27,78;,
  4;30,21,21,32;,
  4;30,32,26,25;,
  3;32,21,21;,
  4;32,21,21,21;,
  3;32,21,26;,
  4;83,84,84,83;,
  4;83,83,79,79;,
  4;34,34,35,35;,
  4;33,33,33,33;,
  4;39,39,85,85;,
  4;39,38,38,39;,
  3;6,6,86;,
  3;6,44,86;,
  3;44,45,86;,
  3;45,46,86;,
  3;87,46,88;,
  4;87,89,86,46;,
  3;41,40,90;,
  3;42,41,90;,
  3;43,42,90;,
  3;47,43,90;,
  3;47,91,21;,
  4;47,90,92,91;,
  4;93,94,94,93;,
  4;50,50,38,38;,
  4;50,37,37,50;,
  4;48,6,6,6;,
  4;49,44,6,48;,
  4;53,45,44,49;,
  3;95,53,96;,
  4;95,46,45,53;,
  3;95,88,46;,
  4;51,40,41,52;,
  4;52,41,42,21;,
  4;21,42,43,21;,
  3;21,21,21;,
  4;21,47,21,21;,
  3;21,43,47;,
  4;97,93,93,97;,
  4;55,55,37,37;,
  4;55,36,36,55;,
  4;54,48,6,6;,
  4;58,49,48,54;,
  3;98,58,99;,
  4;98,53,49,58;,
  3;98,96,53;,
  4;56,51,52,57;,
  4;57,52,21,21;,
  3;21,21,21;,
  4;21,21,21,21;,
  3;21,21,21;,
  4;100,97,97,100;,
  4;60,60,36,36;,
  4;60,35,35,60;,
  4;62,59,101,102;,
  4;62,54,6,59;,
  3;103,62,102;,
  4;103,58,54,62;,
  3;103,99,58;,
  4;61,63,21,21;,
  4;61,56,57,63;,
  3;63,21,21;,
  4;63,21,21,21;,
  3;63,57,21;,
  4;104,104,105,105;,
  4;104,100,100,104;;
 }
 MeshTextureCoords {
  156;
  0.500000;0.000000;,
  0.550000;0.000000;,
  0.550000;1.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.525000;0.000000;,
  0.525000;1.000000;,
  0.750000;1.000000;,
  0.724300;0.000000;,
  0.724300;1.000000;,
  0.700000;1.000000;,
  0.700000;0.000000;,
  0.521030;0.000000;,
  0.529170;0.000000;,
  0.570830;0.000000;,
  0.575000;0.000000;,
  0.579910;0.000000;,
  0.620090;0.000000;,
  0.625000;0.000000;,
  0.631750;0.000000;,
  0.668250;0.000000;,
  0.675000;0.000000;,
  0.687850;0.000000;,
  0.712150;0.000000;,
  0.725000;0.000000;,
  0.529170;1.000000;,
  0.521030;1.000000;,
  0.579910;1.000000;,
  0.575000;1.000000;,
  0.570830;1.000000;,
  0.631750;1.000000;,
  0.625000;1.000000;,
  0.620090;1.000000;,
  0.687850;1.000000;,
  0.675000;1.000000;,
  0.668250;1.000000;,
  0.712150;1.000000;,
  0.725000;1.000000;,
  0.674150;0.000000;,
  0.674150;1.000000;,
  0.650000;1.000000;,
  0.650000;0.000000;,
  0.536910;0.000000;,
  0.513670;0.000000;,
  0.589000;0.000000;,
  0.563090;0.000000;,
  0.644270;0.000000;,
  0.611000;0.000000;,
  0.655730;0.000000;,
  0.513670;1.000000;,
  0.536910;1.000000;,
  0.563090;1.000000;,
  0.589000;1.000000;,
  0.611000;1.000000;,
  0.644270;1.000000;,
  0.655730;1.000000;,
  0.624360;0.000000;,
  0.624360;1.000000;,
  0.600000;1.000000;,
  0.600000;0.000000;,
  0.543430;0.000000;,
  0.507470;0.000000;,
  0.596670;0.000000;,
  0.556570;0.000000;,
  0.603330;0.000000;,
  0.507470;1.000000;,
  0.543430;1.000000;,
  0.556570;1.000000;,
  0.596670;1.000000;,
  0.603330;1.000000;,
  0.575780;0.000000;,
  0.575780;1.000000;,
  0.548070;0.000000;,
  0.503050;0.000000;,
  0.551930;0.000000;,
  0.503050;1.000000;,
  0.548070;1.000000;,
  0.551930;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.550000;1.000000;,
  0.550000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.525000;1.000000;,
  0.525000;0.000000;,
  0.724300;0.000000;,
  0.724300;1.000000;,
  0.700000;0.000000;,
  0.700000;1.000000;,
  0.521030;0.000000;,
  0.529170;0.000000;,
  0.570830;0.000000;,
  0.579910;0.000000;,
  0.575000;0.000000;,
  0.620090;0.000000;,
  0.631750;0.000000;,
  0.625000;0.000000;,
  0.668250;0.000000;,
  0.687850;0.000000;,
  0.675000;0.000000;,
  0.712150;0.000000;,
  0.725000;0.000000;,
  0.529170;1.000000;,
  0.521030;1.000000;,
  0.579910;1.000000;,
  0.570830;1.000000;,
  0.575000;1.000000;,
  0.631750;1.000000;,
  0.620090;1.000000;,
  0.625000;1.000000;,
  0.687850;1.000000;,
  0.668250;1.000000;,
  0.675000;1.000000;,
  0.712150;1.000000;,
  0.725000;1.000000;,
  0.674150;0.000000;,
  0.674150;1.000000;,
  0.650000;0.000000;,
  0.650000;1.000000;,
  0.536910;0.000000;,
  0.513670;0.000000;,
  0.589000;0.000000;,
  0.563090;0.000000;,
  0.644270;0.000000;,
  0.611000;0.000000;,
  0.655730;0.000000;,
  0.513670;1.000000;,
  0.536910;1.000000;,
  0.563090;1.000000;,
  0.589000;1.000000;,
  0.611000;1.000000;,
  0.644270;1.000000;,
  0.655730;1.000000;,
  0.624360;0.000000;,
  0.624360;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.543430;0.000000;,
  0.507470;0.000000;,
  0.596670;0.000000;,
  0.556570;0.000000;,
  0.603330;0.000000;,
  0.507470;1.000000;,
  0.543430;1.000000;,
  0.556570;1.000000;,
  0.596670;1.000000;,
  0.603330;1.000000;,
  0.575780;0.000000;,
  0.575780;1.000000;,
  0.548070;0.000000;,
  0.503050;0.000000;,
  0.551930;0.000000;,
  0.503050;1.000000;,
  0.548070;1.000000;,
  0.551930;1.000000;;
 }
}