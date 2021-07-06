#ifndef SOCCER_COMMON_FIELD_H
#define SOCCER_COMMON_FIELD_H

namespace Common {
  template <class T>
  class Field {
   private:
    T m_length;
    T m_width;

    T m_goalWidth;
    T m_goalDepth;

   public:
    constexpr Field(const T& length, const T& width, const T& goalWidth, const T& goalDepth) :
        m_length(length),
        m_width(width),
        m_goalWidth(goalWidth),
        m_goalDepth(goalDepth) {
    }

    constexpr T length() const {
      return m_length;
    }
    constexpr T width() const {
      return m_width;
    }
    constexpr T goalWidth() const {
      return m_goalWidth;
    }
    constexpr T goalDepth() const {
      return m_goalDepth;
    }

    template <class PT>
    constexpr bool contains(const PT& position) const {
      return (m_length < position.x() && position.x() < m_length) &&
             (m_width < position.y() && position.y() < m_width);
    }
  };
} // namespace Common

#endif // SOCCER_COMMON_FIELD_H
