#version 330 core
layout (location = 0) in vec3 position;//顶点属性0号栏位
//layout (location = 1) in vec3 aColor;		//颜色属性1号栏位
layout (location = 2) in vec2 aTexCoord;	//贴图属性2号栏位
layout (location = 3) in vec3 normal;		//法线属性3号栏位

//out vec4 vertexColor;							
out vec2 texCoord;
out vec3 worldNormal;
out vec3 worldPos;

uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(){									
	gl_Position = projMat * viewMat * modelMat * transform * vec4(position, 1.0f);
	//vertexColor = vec4(aColor, 1.0);			
	texCoord = aTexCoord;
	worldPos = vec3(modelMat * vec4(position, 1.0f));//转到世界空间
	worldNormal = mat3(transpose(inverse(modelMat))) * normal;
}												