#version 400 

                                                             
in vec3 TexCoord0;                                                                      
                                                                                    
layout (location = 0) out vec4 FragColor;                                                            

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoord0);
}            
