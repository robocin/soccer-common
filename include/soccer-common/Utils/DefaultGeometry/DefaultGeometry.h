#ifndef SOCCER_COMMON_DEFAULTGEOMETRY_H
#define SOCCER_COMMON_DEFAULTGEOMETRY_H

#include "soccer-common/Geometry/Geometry.h"

#ifndef SOCCER_COMMON_DEFAULTGEOMETRY_H_UNDEF_POINT
/*!
 * @brief Point2D<float> will be used as standard 2D point.
 */
using Point [[maybe_unused]] = Point2D<float>;
#endif

#ifndef SOCCER_COMMON_DEFAULTGEOMETRY_H_UNDEF_REAL_T
/*!
 * @brief real_type will be used as standard real type.
 */
using real_t = typename Point::type;
#endif

#endif // SOCCER_COMMON_DEFAULTGEOMETRY_H
