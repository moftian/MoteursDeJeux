#include "plane.h"

Plane::Plane()
    :m_count(0)
{
    m_data.resize(4056*8);
    const float step = 0.5f;
    const float half = 8 * step;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            quad(i*step-half, j*step-half,
                 (i+1)*step-half, j*step-half,
                 (i+1)*step-half, (j+1)*step-half,
                 i*step-half, (j+1)*step-half);
        }
    }
}


void Plane::add(const QVector3D &v, const QVector3D &n,  const QVector2D &t)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    *p++ = t.x();
    *p++ = t.y();
    m_count += 8;
}

void Plane::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.05f), n, QVector2D(0, 1));
    add(QVector3D(x4, y4, -0.05f), n, QVector2D(0, 0));
    add(QVector3D(x2, y2, -0.05f), n, QVector2D(1, 1));

    add(QVector3D(x3, y3, -0.05f), n, QVector2D(1, 0));
    add(QVector3D(x2, y2, -0.05f), n, QVector2D(1, 1));
    add(QVector3D(x4, y4, -0.05f), n, QVector2D(0, 0));

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, 0.05f), n, QVector2D(0, 0));
    add(QVector3D(x1, y1, 0.05f), n, QVector2D(0, 1));
    add(QVector3D(x2, y2, 0.05f), n, QVector2D(1, 1));

    add(QVector3D(x2, y2, 0.05f), n, QVector2D(1, 1));
    add(QVector3D(x3, y3, 0.05f), n, QVector2D(1, 0));
    add(QVector3D(x4, y4, 0.05f), n, QVector2D(0, 0));
}
