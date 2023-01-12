#version 330 core
    out vec4 FragColor;

    in vec3 angleColor;
    in vec2 textureCoords;
    in vec3 normal;
    in vec3 fragPos;

    struct Material 
    {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float shiness;
    };

    struct Light
    {
	    vec3 position;
	    vec3 ambient;
	    vec3 diffuse;
	    vec3 specular;
    };

    uniform Material material;
    uniform Light light;
    uniform vec3 viewPos;
    
    // uniform sampler2D box_texture;
    // uniform sampler2D face_texture;
    
    void main()
    {
        // Ambient
	    // float ambientStrength = 0.2f;
	    // vec3 ambient = lightColor * ambientStrength;
        vec3 ambient = light.ambient * material.ambient;

	    // Diffuse
	    vec3 norm = normalize(normal);
	    vec3 lightDir = normalize(light.position-fragPos);
	    float diff = max(dot(norm,lightDir),0.0f);
	    // vec3 diffuse = lightColor * diff;
        vec3 diffuse = light.diffuse * (diff * material.diffuse);

        // Specular
	    // float specularStrength = 0.5f;
	    vec3 viewDir = normalize(viewPos - fragPos);
	    vec3 reflectDir = reflect(-lightDir,norm);
	    // float spec = pow(max(dot(viewDir,reflectDir),0.0f), shiness);
        float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shiness);
	    //vec3 specular = lightColor * spec * specularStrength;
        vec3 specular = light.specular * (spec * material.specular);

	    // vec3 result = (ambient + diffuse + specular) * objectColor;
        vec3 result = ambient + diffuse + specular;
	    FragColor = vec4(result,1.0f);

    }