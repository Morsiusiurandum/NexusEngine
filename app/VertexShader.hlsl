cbuffer CBF
{
    row_major matrix transform;
}


float4 main(float2 pos:Position) : SV_Position
{
    pos = mul(float4(pos.x,pos.y,0.0f,1.0f),transform);
    
    return float4(pos.x,pos.y,0.0f,1.0f);
}
