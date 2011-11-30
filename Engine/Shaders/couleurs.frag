#version 140

//in vec3 color;
in vec3 normal;
in vec3 texco;
uniform vec3 camVector;
uniform sampler2D texture2d;

void main()
{
    gl_FragColor = texture2D(texture2d, texco.xy) * clamp(dot(normal, -normalize(camVector)), 0.0, 1.0);
}
