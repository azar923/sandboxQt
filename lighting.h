#ifndef LIGHTING_H
#define LIGHTING_H
#include <vector>
#include "math_3d.h"

class Lighting
{
public:
    Lighting(int N_point_lights);
    Lighting();

    struct DirectionalLight
    {
        Vector3f Color;
        float AmbientIntensity;
        Vector3f Direction;
        float DiffuseIntensity;
    };

    struct PointLight
    {
        Vector3f Color;
        Vector3f Position;
        float AmbientIntensity;
        float DiffuseIntensity;

        float constant;
        float linear;
        float exp;
    };

    float specularPower;

    void setDirectionalLight(float AmbientIntensity = 0.35, Vector3f Color = Vector3f(1.0, 1.0, 1.0), float DiffuseIntensity = 1.0, Vector3f Direction = Vector3f(0.1,1.0,0.1));

    void addPointLight(float AmbientIntensity = 0.0,
                                Vector3f Color = Vector3f(1.0, 0.0, 0.0),
                                float DiffuseIntensity = 0.0,
                                Vector3f position = Vector3f(-0.5,-0.5, 2.0),
                                float constant = 0.0,
                                float linear = 0.001,
                                float exp = 0.00001);

    std::vector<PointLight> pointLights;
    DirectionalLight dirLight;

};

#endif // LIGHTING_H