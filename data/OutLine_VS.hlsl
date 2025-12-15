//=====================================
//
// 頂点部分のアウトラインシェーダー
// Author : Asuma Nishio
//
//=====================================

//*************************************
// シェーダー内グローバル変数
//*************************************
float4x4 g_mtxWorld; // ワールドマトリックス
float4x4 g_mtxViewProj; // ビューとプロジェクションの掛け合わせ
float g_fOutlineWidth; // アウトラインの太さ

//=============================
// 入出力構造体
//=============================
struct VS_IN
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
};

struct VS_OUT
{
    float4 pos : POSITION;
};

//==================================
// 頂点シェーダーエントリーポイント
//==================================
VS_OUT VS_Main(VS_IN v_in)
{
    VS_OUT Out;

    // 各頂点のローカル座標方向への拡大
    float4 pos = v_in.pos + float4(v_in.normal.xyz * g_fOutlineWidth, 0);

    // WVP変換
    Out.pos = mul(pos, g_mtxViewProj);

    return Out;
}