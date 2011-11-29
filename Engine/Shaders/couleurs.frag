#version 140

in vec3 color;
in vec3 normal;
uniform vec3 camVector;

void main()
{
    gl_FragColor = vec4(color * clamp(dot(normal, -normalize(camVector)), 0.0, 1.0) , 1.0);
}
