#version 330 core

out vec4 color;

in float AttenuationFactor;
in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPosition; 
uniform vec3 lightColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    //float specularStrength = 0.5f;
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse/AttenuationFactor) * vec3(0.8,0.6,0.0);
    color = vec4(result, 1.0f);
} 