//=========================================================
//
// インスタンシングシェーダー [ Instancing.hlsl ]
// Author : Asuma Nishio
//
//=========================================================

//*********************************************************
// グローバル宣言空間
//*********************************************************
float4x4 g_mtxview; // ビューマトリックス
float4x4 g_mtxprojection; // プロジェクションマトリックス

//*********************************************************
// 入力構造体
//*********************************************************
struct VS_INPUT
{
    float4 pos : POSITION; // 座標

    float4 world0 : TEXCOORD0; // インスタンス用ワールド行列
    float4 world1 : TEXCOORD1;
    float4 world2 : TEXCOORD2;
    float4 world3 : TEXCOORD3;
};
//*********************************************************
// 出力構造体
//*********************************************************
struct VS_OUT
{
    float4 pos : POSITION; // 座標
};

//=========================================================
// メインエントリーポイント関数
//=========================================================
VS_OUT VS_Main(VS_INPUT input)
{
    // 構造体変数
    VS_OUT output;

    // ワールドマトリックスを設定する
    float4x4 mtxWorld = float4x4(
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
    
    return output;
}

//=========================================================
// テクニック宣言
//=========================================================
technique Instancing
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS_Main();
    }
}