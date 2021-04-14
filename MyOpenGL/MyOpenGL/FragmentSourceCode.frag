#version 330 core

out vec4 FragColor;

//in vec4 vertexColor;
in vec2 texCoord;
in vec3 worldNormal;
in vec3 worldPos;


struct Material{
	//vec3 diffuse;
	sampler2D diffuse;
	//vec3 specular;
	sampler2D specular;
	float glossPower;
};

uniform Material material;

struct Light{
	vec3 position;

	vec3 color;
	vec3 ambient;
};

uniform Light light;

//uniform sampler2D myTextureA;
//uniform sampler2D myTextureB;

uniform vec3 viewPos;


void main(){
	//vec4 textureMix = mix(texture(myTextureA, texCoord), texture(myTextureB, texCoord), 0.2); 
	vec3 normalDir = normalize(worldNormal);
	vec3 lightDir = normalize(light.position - worldPos);
	vec3 viewDir = normalize(viewPos - worldPos);
	vec3 reflectDir = normalize(reflect(-lightDir,normalDir));

	vec3 textureDiffuse = vec3(texture(material.diffuse, texCoord));
	vec3 textureSpecular = vec3(texture(material.specular, texCoord));

	vec3 ambient = light.ambient * textureDiffuse;

	vec3 diffuse = max(dot(normalDir,lightDir),0.0f) * light.color * textureDiffuse;

	float specPower = pow(max(dot(viewDir,reflectDir),0.0f),material.glossPower);

	vec3 specular = specPower * light.color * textureSpecular * 0.5f ;

	FragColor = vec4(diffuse + ambient + specular ,1.0f);
}