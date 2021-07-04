//
// Created by jose-cruz on 16/06/2021.
//

#ifndef SOCCER_COMMON_KINEMATICS_H
#define SOCCER_COMMON_KINEMATICS_H

#include <QtGlobal>
#include <optional>

namespace Kinematics {
  template <class PT>
  struct UniformMotion {
    /*!
     * @brief s = so + v * t
     */
    static constexpr PT position(qreal t, const PT& v, const std::optional<PT>& so = std::nullopt) {
      return so.value_or(PT()) + v * t;
    }

    /*!
     * @brief
     * s = so + vt <br>
     * s - so = vt <br>
     * (s - so) / t = v <br>
     * v = (s - so) / t
     */
    static constexpr PT velocity(const PT& s, qreal t, const std::optional<PT>& so = std::nullopt) {
      return qFuzzyIsNull(t) ? PT() : (s - so.value_or(s)) / t;
    }

    /*!
     * @brief
     * v = vo + at <br>
     * v - vo = at <br>
     * (v - vo) / t = a <br>
     * a = (v - vo) / t
     */
    static constexpr PT
    acceleration(const PT& v, qreal t, const std::optional<PT>& vo = std::nullopt) {
      return qFuzzyIsNull(t) ? PT() : (v - vo.value_or(v)) / t;
    }
  };
} // namespace Kinematics

#endif // SOCCER_COMMON_KINEMATICS_H
