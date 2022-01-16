

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
cbuffer WorldBuffer : register( b0 )
{
	matrix World;
}

cbuffer ViewBuffer : register( b1 )
{
	matrix View;
}

cbuffer ProjectionBuffer : register( b2 )
{
	matrix Projection;
}

// マテリアルバッファ
struct MATERIAL
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	int			noTexSampling;
	float		Dummy[2];//16byte境界用
};

cbuffer MaterialBuffer : register( b3 )
{
	MATERIAL	Material;
}

// ライト用バッファ
struct LIGHT
{
	float4		Direction[10];
	float4		Position[10];
	float4		Diffuse[10];
	float4		Ambient[10];
	float4		Attenuation[10];
	int4		Flags[10];
	int			Enable;
	int			Dummy[3];//16byte境界用
};

cbuffer LightBuffer : register( b4 )
{
	LIGHT		Light;
}

struct FOG
{
	float4		Distance;
	float4		FogColor;
	int			Enable;
	float		Dummy[3];//16byte境界用
};

// フォグ用バッファ
cbuffer FogBuffer : register( b5 )
{
	FOG			Fog;
};

// 縁取り用バッファ
cbuffer Fuchi : register(b6)
{
	int			fuchi;
	int			fill[3];
};


cbuffer CameraBuffer : register(b7)
{
	float4 Camera;
}



//=============================================================================
// 頂点シェーダ
//=============================================================================
void VertexShaderPolygon( in  float4 inPosition		: POSITION0,
						  in  float4 inNormal		: NORMAL0,
						  in  float4 inDiffuse		: COLOR0,
						  in  float2 inTexCoord		: TEXCOORD0,

						  out float4 outPosition	: SV_POSITION,
						  out float4 outNormal		: NORMAL0,
						  out float2 outTexCoord	: TEXCOORD0,
						  out float4 outDiffuse		: COLOR0,
						  out float4 outWorldPosition : POSITION0
)
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	outPosition = mul(inPosition, wvp);
	outNormal = normalize(mul(float4(inNormal.xyz, 0.0f), World));
	outTexCoord = inTexCoord;

	
	outWorldPosition = mul(inPosition, World);


	if (Light.Enable == 0) 
	{
		outDiffuse = inDiffuse * Material.Diffuse;
	}
	else
	{
		float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 outColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

		for (int i = 0; i < 10; i++)
		{
			if (Light.Flags[i].x == 1)
			{
				float4 worldNormal, normal;
				normal = float4(inNormal.xyz, 0.0);
				worldNormal = mul(normal, World);
				worldNormal = normalize(worldNormal);

				float light = 0.5 - 0.5 * dot(Light.Direction[i].xyz, worldNormal.xyz);

				color = inDiffuse * Material.Diffuse * light * Light.Diffuse[i];
				color += inDiffuse * Material.Ambient * Light.Ambient[i];
			}
			else if (Light.Flags[i].x == 2)
			{
				float4 worldNormal, normal;
				normal = float4(inNormal.xyz, 0.0);
				worldNormal = mul(normal, World);
				worldNormal = normalize(worldNormal);

				float3 posWorld = mul(inPosition, World);
				float3 lightDir;
				lightDir = normalize(posWorld - Light.Position[i]);
				float light = -1.0 * dot(lightDir.xyz, worldNormal.xyz);

				color = inDiffuse * Material.Diffuse * light * Light.Diffuse[i];
				color += inDiffuse * Material.Ambient * Light.Ambient[i];
				float distance = length(posWorld - Light.Position[i]);

				float att = saturate((Light.Attenuation[i].x - distance) / Light.Attenuation[i].x);
				color *= att;
			}
			else
			{
				color = float4(0.0f, 0.0f, 0.0f, 0.0f);
			}

			outColor += color;
		}

		outColor += Material.Emission;
		


		outDiffuse = saturate(outColor);
		outDiffuse.a = inDiffuse.a * Material.Diffuse.a;
		
	}
}



//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void PixelShaderPolygon( in  float4 inPosition		: SV_POSITION,
						 in  float4 inNormal		: NORMAL0,
						 in  float2 inTexCoord		: TEXCOORD0,
						 in  float4 inDiffuse		: COLOR0,
						 in  float4 inWorldPosition : POSITION0,

						 out float4 outDiffuse		: SV_Target )
{
	float4 color;

	if (Material.noTexSampling == 0)
	{
		color = g_Texture.Sample(g_SamplerState, inTexCoord);

		color *= inDiffuse;
	}
	else
	{
		color = inDiffuse;
	}

	

	if (Fog.Enable == 1)
	{
		float z = inPosition.z*inPosition.w;
		float f = (Fog.Distance.y - z) / (Fog.Distance.y - Fog.Distance.x);
		f = saturate(f);
		outDiffuse = f * color + (1 - f)*Fog.FogColor;
		outDiffuse.a = color.a;
	}
	else
	{
		outDiffuse = color;
	}


	

	//縁取り
	//if (fuchi == 1)
	//{
	//	float angle = dot(normalize(inWorldPosition.xyz - Camera.xyz), normalize(inNormal));
	//	//if ((angle < 0.5f)&&(angle > -0.5f))
	//	if (angle > -0.3f)
	//	{
	//		outDiffuse.rb  = 1.0f;
	//		outDiffuse.g = 0.0f;			
	//	}
	//}




}
