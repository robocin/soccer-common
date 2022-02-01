#ifndef SSL_UNIFICATION_EXTENDSQVECTOR3D_H
#define SSL_UNIFICATION_EXTENDSQVECTOR3D_H

#include "soccer-common/Extends/Detail/ExtendsDetail.h"
#include "soccer-common/Geometry/Geometry.h"

#include <QVector3D>

template <>
class Extends<QVector3D> : public QVector3D {
  using CoordType = Geometry3D::CoordType<QVector3D>;

 public:
};

using Point3D = Extends<QVector3D>;

#endif // SSL_UNIFICATION_EXTENDSQVECTOR3D_H
