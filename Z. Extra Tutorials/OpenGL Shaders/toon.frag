varying vec3 Normal;

void main()
{
    float intensity;
    vec4 color;
    vec3 n = normalize(Normal);

    intensity = dot(vec3(gl_LightSource[0].position), n);

    if (intensity > 0.95)
	color = vec4(1.0, 0.5, 0.5, 1.0);
    else if (intensity > 0.50)
	color = vec4(0.6, 0.3, 0.3, 1.0);
    else if (intensity > 0.25)
	color = vec4(0.4, 0.2, 0.2, 1.0);
    else 
	color = vec4(0.2, 0.1, 0.1, 1.0);

    gl_FragColor = color;
}