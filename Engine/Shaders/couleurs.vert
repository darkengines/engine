#version 140

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_Texture;
out vec3 texco;
out vec3 normal;
out vec3 cam;
uniform mat4 modelView;
uniform mat4 projection;
uniform mat4 camera;


void main()
{
    gl_Position = projection*camera*modelView*vec4(in_Vertex, 1.0);
	normal = normalize(mat3(modelView)*in_Normal);
    //color = in_Color;
	texco.xy = in_Texture;
}
