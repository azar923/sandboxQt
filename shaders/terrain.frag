#version 400                                                                        
                                                                                    
in vec3 Position_FS_in;
in vec3 Normal_FS_in;
in vec3 WorldPos_FS_in;
in vec2 TexCoord_FS_in;

in vec2 flowCoords, rippleCoords;
in vec4 projCoords;

uniform mat4 gWorld;
uniform sampler2D grass;
uniform sampler2D sand;
uniform sampler2D stone;
uniform sampler2D snow;
uniform sampler2D water;
uniform sampler2D reflection;

uniform int waterEnd;
uniform int sandEnd;
uniform int grassEnd;
uniform int stoneEnd;

uniform float alpha;
uniform float beta;

layout (location = 0) out vec4 FragColor; 

struct DirectionalLight
{
        vec3 Color;
        float AmbientIntensity;
        vec3 Direction;
        float DiffuseIntensity;
};

uniform DirectionalLight gDirectionalLight;

uniform vec3 gEyeWorldPos;
uniform float gMatSpecularIntensity;
uniform float gSpecularPower;

vec4 CalculateDirectionalLight(DirectionalLight Light)
{
        vec3 Normal = normalize(Normal_FS_in);
        vec4 AmbientColor = vec4(Light.Color, 1.0) * Light.AmbientIntensity;

        vec3 LightDirection = -Light.Direction;

        float DiffuseFactor = dot(Normal, LightDirection);

        vec4 DiffuseColor = vec4(0.0, 0.0, 0.0, 0.0);
        vec4 SpecularColor = vec4(0.0, 0.0, 0.0, 0.0);

    if (DiffuseFactor > 0)
        {
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.DiffuseIntensity *  DiffuseFactor;
                vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos_FS_in);
                vec3 LightReflect = normalize(reflect(LightDirection, Normal));
                float SpecularFactor = dot(VertexToEye, LightReflect);
                SpecularFactor = pow(SpecularFactor, gSpecularPower);

                if (SpecularFactor > 0)
                {
                        if (Light.DiffuseIntensity > 0.0)
                        {
                                SpecularColor = vec4(Light.Color, 1.0) * gMatSpecularIntensity * SpecularFactor;
                        }
                }
        }


        vec4 DirectionalColor = (AmbientColor + DiffuseColor + SpecularColor);

        return DirectionalColor;
}

void main()                                                                         
{
    vec2 rippleEffect = 0.02 * texture2D(reflection, rippleCoords * 0.1).xy;
    vec2 dist = texture2D(water, flowCoords * 0.1  + rippleEffect).xy;
    dist = (dist * 2.0 - vec2(1.0)) * 0.1;
    vec2 uv = projCoords.xy;
    uv = clamp((uv + 1.0) * 0.5 + dist * 0.4, 0.0, 1.0);

    vec4 base = texture2D(water, uv);
    vec4 refl = texture2D(reflection, uv);

    vec4 DirectionalColor = CalculateDirectionalLight(gDirectionalLight);
    int zone_length = 50;

    int waterzone_begin = 0;
    int waterzone_end = waterEnd;
    int waterzone_max = 0;
    int waterzone = waterzone_end - waterzone_begin;

    int sandzone_begin = waterzone_end / 2 ;
    int sandzone_end = sandEnd;
    int sandzone_max = (sandzone_end - sandzone_begin) / 2 + sandzone_begin;
    int sandzone = sandzone_end - sandzone_begin;

    int grasszone_begin = sandzone_max;
    int grasszone_end = grassEnd;
    int grasszone_max = (grasszone_end - grasszone_begin) / 2 + grasszone_begin;
    int grasszone = grasszone_end - grasszone_begin;

    int stonezone_begin = grasszone_max;
    int stonezone_end = stoneEnd;
    int stonezone_max = (stonezone_end - stonezone_begin) / 2 + stonezone_begin;
    int stonezone = stonezone_end - stonezone_begin;

    int snowzone_begin = stonezone_max;
    int snowzone_end = 255;
    int snowzone_max = 255;
    int snowzone = snowzone_end - snowzone_begin;



    float waterWeight = clamp (1.0 - abs(Position_FS_in.z - 0.0) / waterzone, 0.0, 1.0);
    float sandWeight =  clamp (1.0 - abs(Position_FS_in.z - sandzone_max) / (sandzone / 2), 0.0, 1.0);
    float landWeight =  clamp (1.0 - abs(Position_FS_in.z - grasszone_max) / (grasszone / 2), 0.0, 1.0);
    float rockWeight =  clamp (1.0 - abs(Position_FS_in.z - stonezone_max) / (stonezone / 2), 0.0, 1.0);
    float snowWeight =  clamp(1.0 -  abs(Position_FS_in.z - 255) / (255 - stonezone_max), 0.0, 1.0);

    float total = snowWeight + rockWeight + landWeight + sandWeight + waterWeight ;

    snowWeight  /= total;
    rockWeight  /= total;
    landWeight  /= total;
    sandWeight  /= total;
    waterWeight /= total;

    FragColor =  texture2D(snow,  TexCoord_FS_in.xy)   *  snowWeight;
    FragColor += texture2D(stone, TexCoord_FS_in.xy)   *  rockWeight;
    FragColor += texture2D(grass, TexCoord_FS_in.xy)   *  landWeight;
    FragColor += texture2D(sand,  TexCoord_FS_in.xy)   *  sandWeight;
    FragColor += mix (base, refl , 0.4)   *  waterWeight;

    FragColor *= DirectionalColor;

    FragColor = alpha * FragColor - beta;

}                                        
                                     
