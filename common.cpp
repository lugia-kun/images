
#include "common.hpp"

#include <cstdio>
#include <functional>

int ApplicationBase::setup()
{
    glutInitDisplayMode(GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("glut window");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos.v());

    glutDisplayFunc(m_disp);
    glutKeyboardFunc(m_kbdf);

    return 0;
}

void ApplicationBase::setLightPos(const GLVector4f &lp)
{
    m_lightPos = lp;
    if (glIsEnabled(GL_LIGHT0)) {
        glLightfv(GL_LIGHT0, GL_POSITION, lp.v());
    }
}

void ApplicationBase::keyboard(unsigned char key, int x, int y)
{
    using namespace std;

    FILE *fp;
    int state = GL2PS_OVERFLOW, buffsize = 0;

    (void) x; (void) y;  /* not used */
    switch(key){
    case 'q':
        exit(0);
        break;
    case 's':
        fp = fopen("out.eps", "wb");
        while (state == GL2PS_OVERFLOW) {
            buffsize += 1024*1024;
            gl2psBeginPage("test", "gl2psTestSimple", NULL,
                           GL2PS_EPS, GL2PS_SIMPLE_SORT,
                           GL2PS_DRAW_BACKGROUND | GL2PS_USE_CURRENT_VIEWPORT,
                           GL_RGBA, 0, NULL, 0, 0, 0, buffsize, fp, "out.eps");
            display();
            state = gl2psEndPage();
        }
        fclose(fp);
        printf("Done!\n");
        break;
    }
}
