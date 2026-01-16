//=========================================================
//
// インスタンシング [ Instancing.hlsl ]
// Author : Asuma Nishio
//
//=========================================================

//*********************************************************
// シェーダー内グローバル宣言空間
//*********************************************************
float4x4 g_mtxview;			// ビューマトリックス
float4x4 g_mtxprojection;	// プロジェクションマトリックス

float4 g_LightAmbient;		// 環境光
float3 g_LigthDirection;	// ライトの向き

//*********************************************************
// 頂点シェーダー入力構造体
//*********************************************************
struct VS_INPUT
{
	float4 pos : POSITION;	// 座標
	float4 color : COLOR;	// カラー変数
	float3 normal : NORMAL;	// 法線

	float4 world0 : TEXCOORD0;
	float4 world1 : TEXCOORD1;
	float4 world2 : TEXCOORD2;
	float4 world3 : TEXCOORD3;
};
//*********************************************************
// 頂点シェーダー出力構造体
//*********************************************************
struct VS_OUT
{
	float4 pos : POSITION;	// 座標
	float4 color : COLOR;	// カラー変数
	float3 normal : NORMAL;	// 法線
};

//=========================================================
// 頂点シェーダーメインエントリーポイント関数
//=========================================================
VS_OUT VS_Main(VS_INPUT input)
{
	// 出力構造体変数
	VS_OUT output;

	// ワールドマトリックスを設定する
	float4x4 mtxWorld = float4x4
	(
		input.world0,
		input.world1,
		input.world2,
		input.world3
	);

	// ワールド座標を計算
	float4 worldPos = mul(input.pos, mtxWorld);
	
	// ビュー変換座標を計算
	float4 viewPos = mul(worldPos, g_mtxview);
	
	// 出力座標に変換
	output.pos = mul(viewPos, g_mtxprojection);
	
	// カラー設定
	output.color = input.color;
	
	// 法線設定
    output.normal = input.normal;
	
	// 最終出力変数を返す
	return output;
}
//=========================================================
// ピクセルシェーダーメインエントリーポイント関数
//=========================================================
float4 PS_Main(VS_OUT output) : COLOR
{
	// カラーを返す
	return output.color;
}

//=========================================================
// テクニック宣言
//=========================================================
technique Instancing
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS_Main();
		PixelShader = compile ps_3_0 PS_Main();
	}
}