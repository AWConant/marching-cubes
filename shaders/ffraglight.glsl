#version 410

uniform vec4 vColor;  // ambient and diffuse color
uniform vec4 vSColor; // specular color

in vec3 N;
in vec3 L;
in vec3 E;

out vec4 fragColor;

void main() {
  vec4 ambient, diffuse, specular;

  vec3 NN = normalize(N);
  vec3 EE = normalize(E);
  vec3 LL = normalize(L);
  vec3 H = normalize(LL + EE);

  float Kd = max(dot(LL, NN), 0.0);
  float Ks = pow(max(dot(NN, H), 0.0), 80);

  ambient = vColor * 0.2;
  diffuse = vColor * Kd * 0.5;
  specular = vec4(0, 0, 0, 1);
  if (dot(LL, NN) > 0) {
    specular = vSColor * Ks * 0.3;
  }

  fragColor = vec4((ambient + diffuse + specular).xyz, 1);
  // fragColor = vec4(0.5*(NN+vec3(1,1,1)),1);
}
