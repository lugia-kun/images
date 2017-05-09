
extern "C" {
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <gl2ps.h>
}

#include <cmath>
#include <ostream>
#include <iomanip>
#include <initializer_list>
#include <vector>
#include <functional>

template <typename GLtype, int dimension = 4>
class GLVector {
    GLtype m_data[dimension];

public:
    typedef GLVector<GLtype, dimension> Type;
    const int Dimension = dimension;

    template <typename... Args>
    GLVector(Args... args) :
        m_data { args... }
    {}

    GLVector(const std::initializer_list<GLtype> &t) { setV(t); }
    GLVector(const std::vector<GLtype> &t) { setV(t); }
    GLVector(const Type &t) { setV(t); }

    void setV(const Type &t) {
        for (int i = 0; i < dimension; ++i) {
            m_data[i] = t.m_data[i];
        }
    }

    void setV(const std::vector<GLtype> &t)
    {
        int i;
        for (i = 0; i < dimension && i < t.size(); ++i) {
            m_data[i] = t[i];
        }
        for (; i < dimension; ++i) {
            m_data[i] = (GLtype)0.0;
        }
    }

    template <typename... Args>
    void setV(Args... args)
    {
        int i;
        std::vector<GLtype> t = { args... };
        setV(t);
    }

    void setV(const std::initializer_list<GLtype> &t)
    {
        std::vector<GLtype> tt(t);
        setV(tt);
    }

    const GLtype *v() const { return m_data; }
    GLtype *v() { return m_data; }

    Type operator+(const Type &o) const {
        std::vector<GLtype> t;
        t.resize(dimension);
        for (int i = 0; i < dimension; ++i) {
            t[i] = m_data[i] + o.m_data[i];
        }

        return Type(t);
    }

    Type operator-(const Type &o) const {
        std::vector<GLtype> t;
        t.resize(dimension);
        for (int i = 0; i < dimension; ++i) {
            t[i] = m_data[i] - o.m_data[i];
        }

        return Type(t);
    }

    Type operator*(GLtype f) const {
        std::vector<GLtype> t;
        t.resize(dimension);
        for (int i = 0; i < dimension; ++i) {
            t[i] = m_data[i] * f;
        }

        return Type(t);
    }

    Type operator-(int) const {
        std::vector<GLtype> t;
        t.resize(dimension);
        for (int i = 0; i < dimension; ++i) {
            t[i] = -m_data[i];
        }

        return Type(t);
    }

    GLtype innerProd(const Type &o) const {
        GLtype f;
        f = 0.0;
        for (int i = 0; i < dimension; ++i) {
            f += m_data[i] * o.m_data[i];
        }
        return f;
    }

    GLtype lengthSquared() const {
        GLtype f;
        f = 0.0;
        for (int i = 0; i < dimension; ++i) {
            f += m_data[i] * m_data[i];
        }
        return f;
    }

    GLtype length() const {
        return sqrt(lengthSquared());
    }

    Type mapTo(const Type &d) const {
        GLtype f;
        f = this->innerProd(d);
        f /= d.lengthSquared();
        return d * f;
    }

    Type unit() const {
        return *this * (1.0 / this->length());
    }

    Type &operator=(const Type &o) {
        for (int i = 0; i < dimension; ++i) {
            m_data[i] = o.m_data[i];
        }
        return *this;
    }
};


template <typename GLtype, int dim>
    GLVector<GLtype, dim> operator *(GLtype t,
                                     const GLVector<GLtype, dim> &o) {
    return o * t;
}

template <typename GLtype, int dim>
    std::ostream &operator <<(std::ostream &os,
                              const GLVector<GLtype, dim> &o) {
    os << std::string("(");
    for (int i = 0; i < dim - 1; ++i) {
        os << o.v()[i];
        os << std::string(", ");
    }
    os << o.v()[dim - 1];
    os << std::string(")");
    return os;
}

template <typename GLtype>
class GLVector4 : public GLVector<GLtype, 4>
{
    typedef GLVector4<GLtype>   ThisClass;
    typedef GLVector<GLtype, 4> SuperClass;

public:
    GLVector4() :
        SuperClass({0., 0., 0., 0.})
    {}

    GLVector4(GLtype x, GLtype y, GLtype z, GLtype w) :
        SuperClass(x, y, z, w)
    {}

    GLVector4(const std::initializer_list<GLtype> &t) : SuperClass(t)
    {}

    GLVector4(const SuperClass &o) : SuperClass(o)
    {}

    GLtype x() const { return this->v()[0]; }
    GLtype y() const { return this->v()[1]; }
    GLtype z() const { return this->v()[2]; }
    GLtype w() const { return this->v()[3]; }
    void setX(GLtype d) { this->v()[0] = d; }
    void setY(GLtype d) { this->v()[1] = d; }
    void setZ(GLtype d) { this->v()[2] = d; }
    void setW(GLtype d) { this->v()[3] = d; }

    ThisClass &operator =(const ThisClass &o) {
        SuperClass::operator=(o);
        return *this;
    }
};

typedef GLVector4<GLfloat>  GLVector4f;
typedef GLVector4<GLdouble> GLVector4d;

template <typename GLtype>
class GLVector3 : public GLVector<GLtype, 3>
{
    typedef GLVector3<GLtype>   ThisClass;
    typedef GLVector<GLtype, 3> SuperClass;

public:
    GLVector3() :
        GLVector<GLtype, 3>({0., 0., 0.})
    {}

    GLVector3(GLtype x, GLtype y, GLtype z) :
        GLVector<GLtype, 3>(x, y, z)
    {}

    GLVector3(const std::initializer_list<GLtype> &t) :
        GLVector<GLtype, 3>(t)
    {}

    GLVector3(const SuperClass &o) : SuperClass(o)
    {}

    GLtype x() const { return this->v()[0]; }
    GLtype y() const { return this->v()[1]; }
    GLtype z() const { return this->v()[2]; }
    void setX(GLtype d) { this->v()[0] = d; }
    void setY(GLtype d) { this->v()[1] = d; }
    void setZ(GLtype d) { this->v()[2] = d; }

    ThisClass &operator =(const ThisClass &o) {
        SuperClass::operator=(o);
        return *this;
    }
};

typedef GLVector3<GLfloat>  GLVector3f;
typedef GLVector3<GLdouble> GLVector3d;

class ApplicationBase {
    int m_argc;
    char **m_argv;
    GLVector4f m_lightPos;

    template <typename T>
    struct Callback;

    template <typename Ret, typename... Params>
    struct Callback<Ret(Params...)> {
        template <typename... Args>
        static Ret callback(Args... args) {
            func(args...);
        }
        static std::function<Ret(Params...)> func;
    };

    typedef Callback<void()> DisplayCallback;
    typedef Callback<void(unsigned char, int, int)> KeyboardCallback;
    typedef void (DisplayFunction)();
    typedef void (KeyboardFunction)(unsigned char, int, int);

    DisplayFunction  *m_disp;
    KeyboardFunction *m_kbdf;

public:
    ApplicationBase(int argc, char **argv) :
        m_argc(argc), m_argv(argv), m_lightPos(-1.f, 1.f, -1.f, 0.f)
    {
        DisplayCallback::func = std::bind(&ApplicationBase::display, this);
        m_disp = static_cast<DisplayFunction*>(DisplayCallback::callback);

        KeyboardCallback::func = std::bind(&ApplicationBase::keyboard, this,
                                           std::placeholders::_1,
                                           std::placeholders::_2,
                                           std::placeholders::_3);
        m_kbdf = static_cast<KeyboardFunction*>(KeyboardCallback::callback);
    }

    virtual void display() = 0;
    virtual void keyboard(unsigned char key, int x, int y);

    GLVector4f lightPos() const { return m_lightPos; }
    void setLightPos(const GLVector4f &lp);

    int setup();

    template <int dimension>
    void glVertexTd(const GLVector<GLdouble, dimension> &t) const
    {
        switch(dimension) {
        case 2:
            ::glVertex2dv(t.v());
            break;
        case 3:
            ::glVertex3dv(t.v());
            break;
        case 4:
            ::glVertex4dv(t.v());
            break;
        default:
            if (dimension > 4) {
                ::glVertex4dv(t.v());
            }
            break;
        }
    }

    void glVertex3f(GLfloat x, GLfloat y, GLfloat z) const
    {
        ::glVertex3f(x, y, z);
    }

    void glVertex3f(const GLVector4f &v) const
    {
        ::glVertex3fv(v.v());
    }

    void glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
    {
        ::glVertex4f(x, y, z, w);
    }

    void glVertex4f(const GLVector4f &v) const
    {
        ::glVertex4fv(v.v());
    }
};

template <typename Ret, typename... Params>
    std::function<Ret(Params...)>
    ApplicationBase::Callback<Ret(Params...)>::func;
