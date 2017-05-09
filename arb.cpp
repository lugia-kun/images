
#include <iostream>
#include "common.hpp"

class Arb : public ApplicationBase
{
public:
    Arb(int argc, char **argv) : ApplicationBase(argc, argv)
    {}

    virtual void display();
};

void Arb::display() {
    glClearColor(0.3, 0.5, 0.8, 0.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3ub(0xFF , 0 , 0);
    glVertex2f(0 , 0);
    glColor3f(0 , 0 , 1);
    glVertex2f(-1 , 0.9);
    glVertex2f(1 , 0.9);

    glColor3i(2147483647 , 0 , 0);
    glVertex2f(0 , 0);
    glColor3b(0 , 127 , 0);
    glVertex2f(-1 , -0.9);
    glVertex2f(1 , -0.9);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    GLVector3d t, u, v;

    t.setX(0.01);
    u.setV(0.22, 0.42, 0.22);
    v = t.mapTo(u);
    std::cout << v << std::endl;
    std::cout << v.unit() << std::endl;

    Arb a(argc, argv);

    glutInit(&argc, argv);
    a.setup();
    glutMainLoop();
    return 0;
}
