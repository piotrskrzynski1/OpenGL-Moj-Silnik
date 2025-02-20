#version 330 core
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;
uniform Material material;
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// ambient
	vec3 ambient = material.ambient * light.ambient;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = (diff* material.diffuse) * light.diffuse;

	vec3 viewDir = normalize(viewPos-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = specular+ambient+diffuse;
	FragColor = vec4(result,1.0); //* mix(texture(Texture1,TexCoord),texture(Texture2,TexCoord),0.8);
}