#ifndef SOCCER_COMMON_FIELD_H
#define SOCCER_COMMON_FIELD_H

namespace Common {
  template <class T>
  class Field {
   private:
    T m_length;
    T m_width;

    T m_goalDepth;
    T m_goalWidth;

   public:
    constexpr Field(const T& length, const T& width, const T& goalDepth, const T& goalWidth) :
        m_length(length),
        m_width(width),
        m_goalDepth(goalDepth),
        m_goalWidth(goalWidth) {
    }

    constexpr T length() const {
      return m_length;
    }
    constexpr T width() const {
      return m_width;
    }
    constexpr T goalDepth() const {
      return m_goalDepth;
    }
    constexpr T goalWidth() const {
      return m_goalWidth;
    }
  };
} // namespace Common

#endif // SOCCER_COMMON_FIELD_H
