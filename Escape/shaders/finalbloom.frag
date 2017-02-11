#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform sampler2D burning;
uniform bool bloom;
uniform float exposure;
uniform bool isBurning;
uniform float gamma;

void main()
{             
    vec3 hdrColor = texture(scene, TexCoords).rgb;      
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    if(bloom) 
        hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0f);


	if(isBurning){
	    vec4 burn = texture(burning, TexCoords);
		if(burn.a > 0.5){
			FragColor = mix(FragColor, texture(burning, TexCoords), 0.8);
		}else{
			FragColor = mix(FragColor, vec4(1.0,0.0,0.0,1.0), 0.4);
		}
	}
	
}