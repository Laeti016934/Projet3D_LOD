#version 330 core
// TODO
// ajouter une variable uniform pour tous les sommets de type float permettant la mise à l'échelle
// ajouter une variable uniform pour tous les sommets de type vec3 permettant d'appliquer une translation au modèle
// i.e. a appliquer sur tous les sommets
//---------
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

//---------
// ajouter une variable o_color de type vec3 interpolée a envoyer au fragment shaderx

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 vs_position;
out vec3 vs_normal;

//------

void main()
{
    vs_position = (u_viewMatrix * u_modelMatrix * vec4(position, 1.0f)).xyz;
    vs_normal = normalize((transpose(inverse(u_viewMatrix * u_modelMatrix)) * vec4(normal, 0.0f)).xyz);

    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 1.0f);
}

