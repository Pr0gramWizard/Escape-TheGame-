#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec4 clipSpace;
out vec2 textureCoords;
out vec3 fromLightVector[4];
out vec3 lakeNormal;
out vec3 fragPos;
out vec3 viewPos;

//spotlight color
out vec3 spotColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition[4];
uniform float fogDensity;
uniform float fogGradient;

//spotlight uniforms
uniform vec3 lakeSpotLightPosition;
uniform vec3 lakeSpotLightColor;
uniform vec3 lakeSpotLightTarget;
uniform float lakeSpotLightFactor;

const float dudvTiling = 5.0;

const float uDiffuseMaterial = 0.7;
const float uSpecularMaterial = 0.95;
const float uSpecularityExponent = 20.0;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0f);
	clipSpace = projection * view * worldPosition;
	fragPos = vec3(worldPosition);
	viewPos = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz;
	for(int i = 0; i < 4; i++){
		fromLightVector[i] =  worldPosition.xyz - lightPosition[i];
	}
	lakeNormal = mat3(transpose(inverse(model))) * normal;

	textureCoords = texCoords * dudvTiling;

    gl_Position = clipSpace;

	
	//calculate light in eye space
	vec3 lakeSpotLightPositionEye = vec3(view * vec4(lakeSpotLightPosition,1.0));
	vec3 lakeSpotLightTargetEye = vec3(view * vec4(lakeSpotLightTarget,1.0));;

	//spotlight calculation
	mat4 modelview = view * model;
    vec3 vertPos = vec3(modelview * vec4(position,1.0));
    vec3 view = normalize (-vertPos);
    vec3 light = normalize(lakeSpotLightPositionEye - vertPos);
    vec3 halfway = normalize(light + view);

    vec3 diffuseColor = uDiffuseMaterial * lakeSpotLightColor * dot(lakeNormal, (lakeSpotLightPositionEye - vertPos))/length(lakeSpotLightPositionEye - vertPos);
    vec3 specularColor = uSpecularMaterial * lakeSpotLightColor * pow(max(dot(lakeNormal, halfway),0.0), uSpecularityExponent);

    vec3 target = lakeSpotLightTargetEye;
    vec3 lightDirection = target-lakeSpotLightPositionEye;
    float spotlight = pow(dot(normalize(lightDirection), normalize(vertPos - lakeSpotLightPositionEye)), lakeSpotLightFactor);
    spotColor = spotlight * (diffuseColor + specularColor);
}