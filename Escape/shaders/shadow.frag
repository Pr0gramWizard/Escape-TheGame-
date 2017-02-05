#version 330 core
in vec4 FragPos;

uniform vec3 lightPosition;
uniform float farplane;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(FragPos.xyz - lightPosition);
    
    // map to [0;1] range by dividing by farplane
    lightDistance = lightDistance / farplane;
    
    // Write this as modified depth
    gl_FragDepth = lightDistance;
}  