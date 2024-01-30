#include <iostream>
#include <fstream>
#include <cmath>
#include <GLFW/glfw3.h>
#include <glad/glad.h>



double f(double x) {
    return sin(x) + 0.1 * x * x;  // Adjust the function definition
}

double calculateDerivative(double x) {
    const double h = 0.001;
    return (f(x + h) - f(x - h)) / (2 * h);
}

void renderFunction(double a, double b) {
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5, -2, 4, -1, 1);  // Adjust the range based on your function's values

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the function as a line strip
    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw the function as a line strip with colors
    glBegin(GL_LINE_STRIP);
    for (double x = a; x <= b; x += 0.1) {
        double y = f(x);
        double derivative = calculateDerivative(x);
        glColor3f((derivative >= 0.0) ? 0.0f : 1.0f, (derivative >= 0.0) ? 1.0f : 0.0f, 0.0f);
        glVertex2d(x, y);
    }
    glEnd();
    glFlush();

    // Output vertex data to a text file
    std::ofstream outFile("vertex_data.txt");
    int numPoints = static_cast<int>((b - a) / 0.1) + 1;
    outFile << numPoints << std::endl;
    for (double x = a; x <= b; x += 0.1) {
        double y = f(x);
        double derivative = calculateDerivative(x);
        outFile << x << " " << y << " " << derivative << std::endl;
    }
    outFile.close();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Function Graph", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL extensions with glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    double a = 0.0;  // Set the lower bound of the domain
    double b = 5.0;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        renderFunction(a,b);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

