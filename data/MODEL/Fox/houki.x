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
 46;
 -1.46973;3.38564;-23.46370;,
 0.49730;3.38564;-23.46370;,
 0.49730;1.27636;-23.46370;,
 -1.46973;1.27636;-23.46370;,
 0.49730;3.38564;-23.46370;,
 0.98352;3.38564;23.46370;,
 0.98352;1.27636;23.46370;,
 0.49730;1.27636;-23.46370;,
 0.98352;3.38564;23.46370;,
 -0.98352;3.38564;23.46370;,
 -0.98352;1.27636;23.46370;,
 0.98352;1.27636;23.46370;,
 -0.98352;3.38564;23.46370;,
 -1.46973;3.38564;-23.46370;,
 -1.46973;1.27636;-23.46370;,
 -0.98352;1.27636;23.46370;,
 0.49730;3.38564;-23.46370;,
 -1.46973;3.38564;-23.46370;,
 -1.46973;1.27636;-23.46370;,
 0.49730;1.27636;-23.46370;,
 -5.96764;11.52850;-39.52254;,
 -0.53790;2.16380;-19.95682;,
 1.63942;12.34103;-39.74766;,
 -0.53790;2.16380;-19.95682;,
 7.58779;7.53669;-40.08398;,
 -0.53790;2.16380;-19.95682;,
 8.39298;-0.07036;-40.33437;,
 -0.53790;2.16380;-19.95682;,
 3.58331;-6.02400;-40.35224;,
 -0.53790;2.16380;-19.95682;,
 -4.02375;-6.83657;-40.12706;,
 -0.53790;2.16380;-19.95682;,
 -9.97212;-2.03217;-39.79075;,
 -0.53790;2.16380;-19.95682;,
 -10.77729;5.57492;-39.54039;,
 -0.53790;2.16380;-19.95682;,
 -5.96764;11.52850;-39.52254;,
 -1.19217;2.75227;-39.93740;,
 -5.96764;11.52850;-39.52254;,
 1.63942;12.34103;-39.74766;,
 7.58779;7.53669;-40.08398;,
 8.39298;-0.07036;-40.33437;,
 3.58331;-6.02400;-40.35224;,
 -4.02375;-6.83657;-40.12706;,
 -9.97212;-2.03217;-39.79075;,
 -10.77729;5.57492;-39.54039;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 3;20,21,22;,
 3;22,23,24;,
 3;24,25,26;,
 3;26,27,28;,
 3;28,29,30;,
 3;30,31,32;,
 3;32,33,34;,
 3;34,35,36;,
 3;37,38,39;,
 3;37,39,40;,
 3;37,40,41;,
 3;37,41,42;,
 3;37,42,43;,
 3;37,43,44;,
 3;37,44,45;,
 3;37,45,38;;
 
 MeshMaterialList {
  4;
  22;
  1,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.752800;0.197600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.501600;0.432800;0.156800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  23;
  0.000000;0.000000;-1.000000;,
  0.999946;0.000000;-0.010361;,
  0.000000;0.000000;1.000000;,
  -0.999946;0.000000;0.010360;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.412500;0.771815;0.483886;,
  0.267895;0.844495;0.463746;,
  0.799932;0.414777;0.433670;,
  0.871951;-0.265622;0.411273;,
  0.441761;-0.798130;0.409676;,
  -0.238635;-0.870811;0.429815;,
  -0.770673;-0.441090;0.459894;,
  -0.842691;0.239309;0.482290;,
  -0.032714;0.029423;-0.999032;,
  -0.032711;0.029426;-0.999032;,
  -0.032712;0.029429;-0.999032;,
  -0.032713;0.029425;-0.999032;,
  -0.032711;0.029422;-0.999032;,
  -0.032713;0.029422;-0.999032;,
  -0.032718;0.029422;-0.999031;,
  -0.032718;0.029419;-0.999032;,
  -0.032715;0.029420;-0.999032;;
  22;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  3;6,7,7;,
  3;7,7,8;,
  3;8,9,9;,
  3;9,9,10;,
  3;10,11,11;,
  3;11,11,12;,
  3;12,13,13;,
  3;13,13,6;,
  3;14,15,16;,
  3;14,16,17;,
  3;14,17,18;,
  3;14,18,19;,
  3;14,19,20;,
  3;14,20,21;,
  3;14,21,22;,
  3;14,22,15;;
 }
 MeshTextureCoords {
  46;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}