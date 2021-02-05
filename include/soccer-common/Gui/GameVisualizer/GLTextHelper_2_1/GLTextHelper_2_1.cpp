#include "GLTextHelper_2_1.h"

qreal GLTextHelper_2_1::textWidth(const QString& text) {
  qreal ret = 0;
  for (int i = 0; i < text.size(); ++i) {
    ret += glyphs[text[i]].width();
    if (i + 1 < text.size()) {
      ret += local.spacing;
    }
  }
  return ret;
}

qreal GLTextHelper_2_1::textHeight(const QString& text) {
  qreal ret = 0;
  for (int i = 0; i < text.size(); ++i) {
    ret = std::max(ret, glyphs[text[i]].height());
  }
  return ret;
}

qreal GLTextHelper_2_1::textAscent(const QString& text) {
  qreal ret = 0;
  for (int i = 0; i < text.size(); ++i) {
    ret = std::max(ret, glyphs[text[i]].ascent());
  }
  return ret;
}

qreal GLTextHelper_2_1::textDescent(const QString& text) {
  qreal ret = 0;
  for (int i = 0; i < text.size(); ++i) {
    ret = std::max(ret, glyphs[text[i]].descent());
  }
  return ret;
}

void GLTextHelper_2_1::putChar(const QChar& ch) {
  callListAndIncrementZ(glyphs[ch].displayListId());
}

GLTextHelper_2_1::GLTextHelper_2_1() : glyphs(this) {
}

void GLTextHelper_2_1::setFont(const QFont& font) {
  glyphs.setFont(font);
}

void GLTextHelper_2_1::setTextSpacing(qreal spacing) {
  local.spacing = spacing;
}
