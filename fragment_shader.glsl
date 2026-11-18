#version 330 core
//Uniforms
uniform vec3 u_light1Orientation;
uniform vec3 u_light1Ambient;
uniform vec3 u_light1Diffuse;
uniform vec3 u_light1Specular;
uniform bool u_light1Enabled;

in vec3 vs_position;
in vec3 vs_normal;

out vec4 FragColor;

void main()
{
    FragColor =  vec4(u_light1Ambient, 1.0);

    vec3 N = normalize(vs_normal.xyz);
    vec3 L = normalize(-vs_position);

    vec3 color = u_light1Ambient * vec3(1.0, 1.0, 1.0);
    vec3 diffuseColor, specularColor;

    if (u_light1Enabled)
    {
        // Diffuse
        float diffuse = max(dot(N, L), 0.0);

        // Specular
        vec3 V = normalize(-vs_position.xyz);
        vec3 R = reflect(-L, N);

        float specular = pow(max(dot(V, R), 0.0), 32.0);

        diffuseColor = diffuse * u_light1Diffuse;
        specularColor = specular * u_light1Specular;

        color += diffuseColor;
        color += specularColor;
    }
    FragColor = vec4(color, 1.0);
}
