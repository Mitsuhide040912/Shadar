#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>


#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;

class Texture;

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;//ベクトル
		XMFLOAT4 specular;//ベクトル
		XMFLOAT4 ambient;
		XMFLOAT4 shininess;//スカラー
		XMFLOAT4 factor;
	};

	struct CONSTBUFFER_MODEL
	{
		XMMATRIX	matWVP;//スクリーン変換マトリクス
		XMMATRIX	matW; //ワールド変換マトリクス
		XMMATRIX	matNormal;//法線ワールド変換用マトリクス
		XMFLOAT4	diffuseColor;//RGBの拡散反射係数（色）
		XMFLOAT4	diffuseFactor;//拡散光の反射係数
		XMFLOAT4    ambientColor;
		XMFLOAT4    specularColor;
		XMFLOAT4    shininess;
		int			isTextured;
	};

	struct VERTEX
	{
		XMVECTOR position;//位置
		XMVECTOR uv; //テクスチャ座標
		XMVECTOR normal; //法線ベクトル
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数
	int state_;

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	std::vector<MATERIAL> pMaterialList_;
	vector <int> indexCount_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};