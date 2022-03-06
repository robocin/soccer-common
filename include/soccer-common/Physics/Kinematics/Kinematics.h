//
// Created by jose-cruz on 16/06/2021.
//

#ifndef SOCCER_COMMON_KINEMATICS_H
#define SOCCER_COMMON_KINEMATICS_H

#include <optional>
#include "soccer-common/Geometry/Geometry.h"
#include "soccer-common/Extends/QPoint/ExtendsQPoint.h"

namespace Kinematics {
  struct UniformRectilinearMotion {
    /*!
     * @brief s = so + v * t
     */
    static constexpr real_t position(real_t so, real_t v, real_t t) {
      return so + v * t;
    }
    template <class PT>
    static constexpr PT position(const std::optional<PT>& so, const PT& v, real_t t) {
      return PT(position(so ? so->x() : 0.0, v.x(), t), position(so ? so->y() : 0.0, v.y(), t));
    }
    template <class PT>
    static constexpr PT position(const PT& so, const PT& v, real_t t) {
      return PT(position(so.x(), v.x(), t), position(so.y(), v.y(), t));
    }
    template <class PT>
    static constexpr PT position(const std::optional<PT>& so, const PT& v, const PT& t) {
      return PT(position(so ? so->x() : 0.0, v.x(), t.x()),
                position(so ? so->y() : 0.0, v.y(), t.y()));
    }
    template <class PT>
    static constexpr PT position(const PT& so, const PT& v, const PT& t) {
      return PT(position(so.x(), v.x(), t.x()), position(so.y(), v.y(), t.y()));
    }

    /*!
     * @brief
     * s = so + v * t <br>
     * s - so = v * t <br>
     * (s - so) / t = v <br>
     * v = (s - so) / t
     */
    static constexpr real_t velocity(real_t s, real_t so, real_t t) {
      return Math::isNull(t) ? 0.0 : (s - so) / t;
    }
    template <class PT>
    static constexpr PT velocity(const PT& s, const std::optional<PT>& so, real_t t) {
      return PT(velocity(s.x(), so ? so->x() : 0.0, t), velocity(s.y(), so ? so->y() : 0.0, t));
    }
    template <class PT>
    static constexpr PT velocity(const PT& s, const PT& so, real_t t) {
      return PT(velocity(s.x(), so.x(), t), velocity(s.y(), so.y(), t));
    }
    template <class PT>
    static constexpr PT velocity(const PT& s, const std::optional<PT>& so, const PT& t) {
      return PT(velocity(s.x(), so ? so->x() : 0.0, t.x()),
                velocity(s.y(), so ? so->y() : 0.0, t.y()));
    }
    template <class PT>
    static constexpr PT velocity(const PT& s, const PT& so, const PT& t) {
      return PT(velocity(s.x(), so.x(), t.x()), velocity(s.y(), so.y(), t.y()));
    }

    /*!
     * @brief
     * s = so + v * t <br>
     * t * v = s - so <br>
     * t = (s - so) / v
     */
    static constexpr real_t time(real_t s, real_t so, real_t speed) {
      return Math::isNull(speed) ? 0.0 : (s - so) / speed;
    }
    template <class PT>
    static constexpr real_t time(const PT& s, const PT& so, real_t speed) {
      return Math::isNull(speed) ? 0.0 : Geometry2D::norm(s - so) / speed;
    }
    template <class PT>
    static constexpr PT time(const PT& s, const PT& so, const PT& v) {
      return PT(time(s.x(), so.x(), v.x()), time(s.y(), so.y(), v.y()));
    }
  };

  using URM = UniformRectilinearMotion;

  struct UniformlyAcceleratedRectilinearMotion {
    /*!
     * @brief s = so + vo * t + (a * t * t) / 2
     */
    static constexpr real_t position(real_t so, real_t vo, real_t a, real_t t) {
      return so + vo * t + (a * t * t) / 2.0;
    }
    template <class PT>
    static constexpr PT position(const std::optional<PT>& so, const PT& vo, const PT& a, real_t t) {
      return PT(position(so ? so->x() : 0.0, vo.x(), a.x(), t),
                position(so ? so->y() : 0.0, vo.y(), a.y(), t));
    }
    template <class PT>
    static constexpr PT position(const PT& so, const PT& vo, const PT& a, real_t t) {
      return PT(position(so.x(), vo.x(), a.x(), t), position(so.y(), vo.y(), a.y(), t));
    }
    template <class PT>
    static constexpr PT
    position(const std::optional<PT>& so, const PT& vo, const PT& a, const PT& t) {
      return PT(position(so ? so->x() : 0.0, vo.x(), a.x(), t.x()),
                position(so ? so->y() : 0.0, vo.y(), a.y(), t.y()));
    }
    template <class PT>
    static constexpr PT position(const PT& so, const PT& vo, const PT& a, const PT& t) {
      return PT(position(so.x(), vo.x(), a.x(), t.x()), position(so.y(), vo.y(), a.y(), t.y()));
    }

    /*!
     * @brief v = vo + a * t
     */
    static constexpr real_t velocity(real_t vo, real_t a, real_t t) {
      return vo + a * t;
    }
    template <class PT>
    static constexpr PT velocity(const std::optional<PT>& vo, const PT& a, real_t t) {
      return PT(velocity(vo ? vo->x() : 0.0, a.x(), t), velocity(vo ? vo->y() : 0.0, a.y(), t));
    }
    template <class PT>
    static constexpr PT velocity(const PT& vo, const PT& a, real_t t) {
      return PT(velocity(vo.x(), a.x(), t), velocity(vo.y(), a.y(), t));
    }
    template <class PT>
    static constexpr PT velocity(const std::optional<PT>& vo, const PT& a, const PT& t) {
      return PT(velocity(vo ? vo->x() : 0.0, a.x(), t.x()),
                velocity(vo ? vo->y() : 0.0, a.y(), t.y()));
    }
    template <class PT>
    static constexpr PT velocity(const PT& vo, const PT& a, const PT& t) {
      return PT(velocity(vo.x(), a.x(), t.x()), velocity(vo.y(), a.y(), t.y()));
    }

    /*!
     * @brief v = vo + a * t <br>
     * a * t = v - vo <br>
     * t = (v - vo) / a
     */
    static constexpr real_t time(real_t v, real_t vo, real_t a) {
      return Math::isNull(a) ? 0.0 : (v - vo) / a;
    }
    template <class PT>
    static constexpr PT time(const std::optional<PT>& v, const PT& vo, const PT& a) {
      return PT(time(v ? v->x() : 0.0, vo.x(), a.x()), time(v ? v->y() : 0.0, vo.y(), a.y()));
    }
    template <class PT>
    static constexpr PT time(const PT& v, const PT& vo, const PT& a) {
      return PT(time(v.x(), vo.x(), a.x()), time(v.y(), vo.y(), a.y()));
    }

    /*!
     * @brief
     * v = vo + a * t <br>
     * a * t = v - vo <br>
     * a = (v - vo) / t
     */
    static constexpr real_t acceleration(real_t v, real_t vo, real_t t) {
      return Math::isNull(t) ? 0.0 : (v - vo) / t;
    }
    template <class PT>
    static constexpr PT acceleration(const PT& v, const std::optional<PT>& vo, real_t t) {
      return PT(acceleration(v.x(), vo ? vo->x() : 0.0, t),
                acceleration(v.y(), vo ? vo->y() : 0.0, t));
    }
    template <class PT>
    static constexpr PT acceleration(const PT& v, const PT& vo, real_t t) {
      return PT(acceleration(v.x(), vo.x(), t), acceleration(v.y(), vo.y(), t));
    }
    template <class PT>
    static constexpr PT acceleration(const PT& v, const std::optional<PT>& vo, const PT& t) {
      return PT(acceleration(v.x(), vo ? vo->x() : 0.0, t.x()),
                acceleration(v.y(), vo ? vo->y() : 0.0, t.y()));
    }
    template <class PT>
    static constexpr PT acceleration(const PT& v, const PT& vo, const PT& t) {
      return PT(acceleration(v.x(), vo.x(), t.x()), acceleration(v.y(), vo.y(), t.y()));
    }

    struct Torricelli {
      /*!
       * @brief v^2 = vo^2 + 2 * a * Δs
       */
      static constexpr real_t velocitySquared(real_t vo, real_t a, real_t displacement) {
        return vo * vo + 2.0 * a * displacement;
      }
      template <class PT>
      static constexpr PT
      velocitySquared(const std::optional<PT>& vo, const PT& a, const PT& displacement) {
        return PT(velocitySquared(vo ? vo->x() : 0.0, a.x(), displacement.x()),
                  velocitySquared(vo ? vo->y() : 0.0, a.y(), displacement.y()));
      }
      template <class PT>
      static constexpr PT velocitySquared(const PT& vo, const PT& a, const PT& displacement) {
        return PT(velocitySquared(vo.x(), a.x(), displacement.x()),
                  velocitySquared(vo.y(), a.y(), displacement.y()));
      }

      /*!
       * @brief v = √(vo^2 + 2 * a * Δs)
       */
      static constexpr real_t velocity(real_t vo, real_t a, real_t displacement) {
        return Math::sqrt(velocitySquared(vo, a, displacement));
      }
      template <class PT>
      static constexpr PT
      velocity(const std::optional<PT>& vo, const PT& a, const PT& displacement) {
        return PT(velocity(vo ? vo->x() : 0.0, a.x(), displacement.x()),
                  velocity(vo ? vo->y() : 0.0, a.y(), displacement.y()));
      }
      template <class PT>
      static constexpr PT velocity(const PT& vo, const PT& a, const PT& displacement) {
        return PT(velocity(vo.x(), a.x(), displacement.x()),
                  velocity(vo.y(), a.y(), displacement.y()));
      }

      /*!
       * @brief
       * v^2 = vo^2 + 2 * a * Δs <br>
       * 2 * a * Δs = v^2 - vo^2 <br>
       * a = (v^2 - vo^2) / (2 * Δs)
       */
      static constexpr real_t acceleration(real_t v, real_t vo, real_t displacement) {
        return (v * v - vo * vo) / (2.0 * displacement);
      }
      template <class PT>
      static constexpr PT
      acceleration(const PT& v, const std::optional<PT>& vo, const PT& displacement) {
        return PT(acceleration(v.x(), vo ? vo->x() : 0.0, displacement.x()),
                  acceleration(v.y(), vo ? vo->y() : 0.0, displacement.y()));
      }
      template <class PT>
      static constexpr PT acceleration(const PT& v, const PT& vo, const PT& displacement) {
        return PT(acceleration(v.x(), vo.x(), displacement.x()),
                  acceleration(v.y(), vo.y(), displacement.y()));
      }

      /*!
       * @brief Δs = (v^2 - vo^2) / (2 * a)
       */
      static constexpr real_t displacement(real_t v, real_t vo, real_t a) {
        return (v * v - vo * vo) / (2.0 * a);
      }
      template <class PT>
      static constexpr PT displacement(const PT& v, const std::optional<PT>& vo, const PT& a) {
        return PT(displacement(v.x(), vo ? vo->x() : 0.0, a.x()),
                  displacement(v.y(), vo ? vo->y() : 0.0, a.y()));
      }
      template <class PT>
      static constexpr PT displacement(const PT& v, const PT& vo, const PT& a) {
        return PT(displacement(v.x(), vo.x(), a.x()), displacement(v.y(), vo.y(), a.y()));
      }
    };
  };

  using UARM = UniformlyAcceleratedRectilinearMotion;
} // namespace Kinematics

#endif // SOCCER_COMMON_KINEMATICS_H
