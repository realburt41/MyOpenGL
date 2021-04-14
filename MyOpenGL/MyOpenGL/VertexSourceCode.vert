#version 330 core
layout (location = 0) in vec3 position;//��������0����λ
//layout (location = 1) in vec3 aColor;		//��ɫ����1����λ
layout (location = 2) in vec2 aTexCoord;	//��ͼ����2����λ
layout (location = 3) in vec3 normal;		//��������3����λ

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
	worldPos = vec3(modelMat * vec4(position, 1.0f));//ת������ռ�
	worldNormal = mat3(transpose(inverse(modelMat))) * normal;
}												