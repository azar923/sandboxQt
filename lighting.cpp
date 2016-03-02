#include "lighting.h"

Lighting::Lighting()
{
    specularPower = 16.0;
}

void Lighting::setDirectionalLight(float AmbientIntensity, Vector3f Color, float DiffuseIntensity, Vector3f Direction)
{
    dirLight.AmbientIntensity = AmbientIntensity;
    dirLight.Color = Color;
    dirLight.DiffuseIntensity = DiffuseIntensity;
    dirLight.Direction = Direction;
}

void Lighting::addPointLight(float AmbientIntensity, Vector3f Color ,float DiffuseIntensity, Vector3f position, float constant,float linear, float exp)
{
    PointLight light;
    light.AmbientIntensity = AmbientIntensity;
    light.Color = Color;
    light.DiffuseIntensity = DiffuseIntensity;
    light.Position = position;
    light.constant = constant;
    light.linear = linear;
    light.exp = exp;
    pointLights.push_back(light);
}

