#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <shaders.h>
#include <shapes.h>
#include <smath.h>

#define WIDTH 800
#define HEIGHT 600

unsigned int transform_location;
mat4 transform_matrix;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void moveRectUp()
{
    vec3 translation_vector = {0.0f, 0.5f, 0.0f};
    mat4 translation_matrix;
    setIdentityMatrix(translation_matrix);
    translate(translation_matrix, translation_vector);
    multiplyMatrices(transform_matrix, translation_matrix, transform_matrix);
    glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
}

void moveRectDown()
{
    vec3 translation_vector = {0.0f, -0.5f, 0.0f};
    mat4 translation_matrix;
    setIdentityMatrix(translation_matrix);
    translate(translation_matrix, translation_vector);
    multiplyMatrices(transform_matrix, translation_matrix, transform_matrix);
    glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
}

void moveRectLeft()
{
    vec3 translation_vector = {-0.5f, 0.0f, 0.0f};
    mat4 translation_matrix;
    setIdentityMatrix(translation_matrix);
    translate(translation_matrix, translation_vector);
    multiplyMatrices(transform_matrix, translation_matrix, transform_matrix);
    glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
}

void moveRectRight()
{
    vec3 translation_vector = {0.5f, 0.0f, 0.0f};
    mat4 translation_matrix;
    setIdentityMatrix(translation_matrix);
    translate(translation_matrix, translation_vector);
    multiplyMatrices(transform_matrix, translation_matrix, transform_matrix);
    glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        switch(key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, 1);
                break;
            case GLFW_KEY_K:
                moveRectUp();
                break;
            case GLFW_KEY_J:
                moveRectDown();
                break;
            case GLFW_KEY_H:
                moveRectLeft();
                break;
            case GLFW_KEY_L:
                moveRectRight();
                break;
        }
    }
    
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // Set callback function for window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glfwSetKeyCallback(window, key_callback);

    // Initialize GLAD, needs to be done after setting the window context
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    int vertex_shader = load_shader("C:/Users/Legion Slim 5/dev/OpenGL/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    int fragment_shader = load_shader("C:/Users/Legion Slim 5/dev/OpenGL/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    int shader_program = create_shader_program();
    float rect_vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // rect top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // rect bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // rect bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // rect top left 
    }; 

    float tri_vertices[] = {
        0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // tri top right
        0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // tri top right
        -0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // tri top right
    };

    unsigned int rect_indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle
    };

    

    // Create a buffer and bind it as a GL_ARRAY_BUFFER, making it a Vertex Buffer Object
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    /*// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy dara from vertices to VBO using GL_STATIC_DRAW(data is set once, used many times)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Copy dara from indices to EBO using GL_STATIC_DRAW(data is set once, used many times)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Configure the attributes
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Unbind the VBO, it is already saved with VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

*/
    // Texture stuff
    unsigned int texture;
    glGenTextures(1, &texture); // Generates texture object
    glBindTexture(GL_TEXTURE_2D, texture); // Binds that object to GL_TEXTURE_2D target, as with all the other objects, now calls will be made to this target
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // Attaches the actual image to the texture object
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture\n");
    }

    stbi_image_free(data); // Free image memory

    

    // Shader program must be bound before setting the uniform
    glUseProgram(shader_program);
    /*
    mat4 scale_matrix;
    setIdentityMatrix(scale_matrix); 
    scale(scale_matrix, 1.5f);
    mat4 rotate_matrix;
    setIdentityMatrix(rotate_matrix); 
    rotate(rotate_matrix, radians(80.0f), Z);
    multiplyMatrices(transform_matrix, rotate_matrix, scale_matrix);
    transform_location = glGetUniformLocation(shader_program, "transform_matrix");
    glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
   */ 
    // PREVIOUS
    /* Loop until the user closes the window */
    /*
    while (!glfwWindowShouldClose(window))
    {
        // Not the best way to handle input
        //processInput(window);

        // Render here 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        //glBindTexture(GL_TEXTURE_2D, texture); // Binds that object to GL_TEXTURE_2D target, as with all the other objects, now calls will be made to this target
        mat4 scale_matrix;
        setIdentityMatrix(scale_matrix); 
        scale(scale_matrix, 1.5f);
        mat4 rotate_matrix;
        setIdentityMatrix(rotate_matrix); 
        rotate(rotate_matrix, radians(80.0f), Z);
        multiplyMatrices(transform_matrix, rotate_matrix, scale_matrix);
        transform_location = glGetUniformLocation(shader_program, "transform_matrix");
        glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        vec3 translation_vector = {0.5f, 0.0f, 0.0f};
        mat4 translate_matrix;
        setIdentityMatrix(translate_matrix);
        translate(translate_matrix, translation_vector);
        multiplyMatrices(transform_matrix, translate_matrix, transform_matrix);
        glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        mat4 translate_matrix;
        setIdentityMatrix(translate_matrix);
        translate(translate_matrix, translation_vector);
        multiplyMatrices(transform_matrix, translate_matrix, transform_matrix);
        glUniformMatrix4fv(transform_location, 1, GL_TRUE, &transform_matrix[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 6));
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
*/
    Batch batch;
    batch_init(&batch);

    while(!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);

        batch.vertex_count = 0;
        batch.index_count = 0;

        Rect rect1 = {
            rect_vertices,
            rect_indices,
            sizeof(rect_vertices),
            sizeof(rect_indices),
        };

        batch_add_rect(&batch, &rect1);

        batch_flush(&batch);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    // Clean up all the resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return 0;
}