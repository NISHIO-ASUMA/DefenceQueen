//=============================
//
// アウトラインシェーダー
// Author : Asuma Nishio
//
//=============================

//=============================
// シェーダー内グローバル変数
//=============================
float4x4 g_mtxWorld;        // ワールドマトリックス
float4x4 g_mtxViewProj;     // ビューとプロジェクションの掛け合わせ
float g_fOutlineWidth;      // アウトラインの太さ
float4 g_Color;             // カラー情報

//=============================
// 入出力構造体
//=============================
struct VS_IN
{
    float3 pos : POSITION0;
    float3 normal : NORMAL;
};

struct VS_OUT
{
    float4 pos : POSITION0;
    float4 color : COLOR0;
};

//==================================
// 頂点シェーダーエントリーポイント
//==================================
VS_OUT VS_Main(VS_IN v_in)
{
    // 変数
    VS_OUT v_out;
    
    // ワールド座標に変換する
    float3 WorldPos = mul(float4(v_in.pos, 1.0f), g_mtxWorld).xyz;
    
    // 法線の設定
    float3 WorldNormal = mul((float3x3) g_mtxWorld,v_in.normal);
    WorldNormal = normalize(WorldNormal);
    
    // 幅の分押し出す
    WorldPos += WorldNormal * g_fOutlineWidth;
    
    // クリップ座標を設定
    v_out.pos = mul(float4(WorldPos, 1.0f), g_mtxViewProj);
    
    // カラー設定
    v_out.color = g_Color;
    
    // 結果を返す
    return v_out;
}

//=======================================
// ピクセルシェーダーエントリ－ポイント
//=======================================
float4 PS_Main(float4 in_color : COLOR0) : COLOR0
{
    // color値を返す
    return in_color;
}

//=============================
// テクニック宣言
//=============================
technique OutLine
{
    pass P0
    {
        VertexShader = compile VS_3_0 VS_Main();
        PixelShader = compile PS_3_0 PS_Main();
    }
}