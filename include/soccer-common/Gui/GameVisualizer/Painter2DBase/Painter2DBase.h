#ifndef SOCCER_COMMON_PAINTER2DBASE_H
#define SOCCER_COMMON_PAINTER2DBASE_H

#include <QColor>
#include "soccer-common/Gui/GameVisualizer/PainterGeometry/PainterGeometry.h"
#include "soccer-common/Gui/GameVisualizer/PainterText/PainterText.h"

class Painter2DBase {
public:
    virtual inline void drawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c, const QColor& color) {}
    virtual inline void drawFilledQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d, const QColor& color) {}
    virtual inline void drawFilledRectangle(const Vertex& topLeft, const Vertex& bottomRight, const QColor& color) {}
    virtual inline void drawPolygon(Polygon polygon, const QColor& color, qreal thickness) {}
    virtual inline void drawFilledConvexPolygon(Polygon polygon, const QColor& color) {}
    virtual inline void drawFilledPolygon(Polygon polygon, const QColor& color) {}
    virtual inline void drawPolyline(Polygon polyline, const QColor& color, qreal thickness) {}
    virtual inline void drawLine(const Vertex& a, const Vertex& b, const QColor& color, qreal thickness) {}
    virtual inline void drawFilledCircle(const Vertex& origin, qreal radius, const QColor& color) {}
    virtual inline QColor backgroundColor() {}
    virtual inline void drawText(const QString& text, const Vertex& position, qreal size, const QColor& color, qreal angle = 0.0, HAlign hAlign = HAlign::Center, VAlign vAlign = VAlign::Middle) {}
};

#endif