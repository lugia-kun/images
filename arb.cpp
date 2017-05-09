
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

    glLineWidth(6.);
    gl2psLineWidth(6.);
    gl2psLineCap(GL2PS_LINE_CAP_SQUARE);
    gl2psLineJoin(GL2PS_LINE_JOIN_ROUND);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.5, 0.8, 0.0);
    glVertex3f(-0.35, 0.98, 0.2);
    glVertex3f(-0.2, 0.8, 0.0);
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
