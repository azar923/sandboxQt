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
    float waterWeight = clamp (1.0 - abs(Position_FS_in.z - 0.0) / 40.0, 0.0, 1.0);
    float sandWeight =  clamp (1.0 - abs(Position_FS_in.z - 60.0) / 40.0, 0.0, 1.0);
    float landWeight =  clamp (1.0 - abs(Position_FS_in.z - 120.0) / 50.0, 0.0, 1.0);
    float rockWeight =  clamp (1.0 - abs(Position_FS_in.z - 170.0) / 30.0, 0.0, 1.0);
    float snowWeight =  clamp(1.0 -  abs(Position_FS_in.z - 255.0) / 100.0, 0.0, 1.0);

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

    FragColor = 1.5 * FragColor - 0.25;

}                                        
