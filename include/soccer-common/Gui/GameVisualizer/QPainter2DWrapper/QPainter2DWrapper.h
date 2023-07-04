#ifndef VSS_UNIFICATION_QPAINTER2DWRAPPER_H
#define VSS_UNIFICATION_QPAINTER2DWRAPPER_H

#include "soccer-common/Gui/GameVisualizer/Painter2DBase/Painter2DBase.h"
#include <QPainter>
#include <QBrush>

class QPainter2DWrapper: public Painter2DBase {
    QPainter* p = nullptr;

public:

    void setPainter(QPainter* painter){
        p = painter;
    }

    inline void drawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c, const QColor& color) override {
        QBrush br = QBrush(color);
        p->setBrush(br);

        QPointF tri[] = {
            a,b,c
        };

        p->drawConvexPolygon(tri, 3);
    }

    inline void drawFilledQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d, const QColor& color) override {
        QBrush br = QBrush(color);
        p->setBrush(br);
        QPointF quad[] = {a,b,c,d};
        p->drawPolygon(quad, 4);
    }

    inline void drawFilledRectangle(const Vertex& topLeft, const Vertex& bottomRight, const QColor& color) override {
        QBrush br = QBrush(color);
        p->setBrush(br);
        const auto& rect = QRectF(topLeft, bottomRight);
        p->drawRect(rect);
    }
    
    inline void drawPolygon(Polygon polygon, const QColor& color, qreal thickness) override {
        QPen currPen = p->pen();
        p->setBrush(Qt::NoBrush);
        p->setPen(QPen(color, thickness));
        auto* points = new QPointF[polygon.size()];
        for(int i=0; i<polygon.size(); i++){
            points[i] = polygon[i];
        }
        p->drawPolygon(points, polygon.size());
        p->setPen(currPen);
    }

    inline void drawFilledConvexPolygon(Polygon polygon, const QColor& color) override {
        QBrush br = QBrush(color);
        p->setBrush(br);
        auto* points = new QPointF[polygon.size()];
        for(int i=0; i<polygon.size(); i++){
            points[i] = polygon[i];
        }
        p->drawConvexPolygon(points, polygon.size());
    }

    inline void drawFilledPolygon(Polygon polygon, const QColor& color) override {
        QBrush br = QBrush(color);
        p->setBrush(br);
        auto* points = new QPointF[polygon.size()];
        for(int i=0; i<polygon.size(); i++){
            points[i] = polygon[i];
        }
        p->drawPolygon(points, polygon.size());
    }

    inline void drawPolyline(Polygon polyline, const QColor& color, qreal thickness) override {
        QPen currPen = p->pen();
        p->setBrush(Qt::NoBrush);
        p->setPen(QPen(color, thickness));
        auto* points = new QPointF[polyline.size()];
        for(int i=0; i<polyline.size(); i++){
            points[i] = polyline[i];
        }
        p->drawPolyline(points, polyline.size());
        p->setPen(currPen);
    }

    inline void drawLine(const Vertex& a, const Vertex& b, const QColor& color, qreal thickness) override {
        QPen currPen = p->pen();
        p->setBrush(Qt::NoBrush);
        p->setPen(QPen(color, thickness));
        p->drawLine(a, b);
        p->setPen(currPen);
    }

    inline void drawFilledCircle(const Vertex& origin, qreal radius, const QColor& color) override {
        QBrush br = QBrush(color);
        p->setBrush(br);
        p->drawEllipse(origin, radius, radius);
    }

    inline QColor backgroundColor() override {
        return p->background().color();
    }

    inline void drawText(const QString& text, const Vertex& position, qreal size, const QColor& color, qreal angle = 0.0, HAlign hAlign = HAlign::Center, VAlign vAlign = VAlign::Middle) override {
        QPen currPen = p->pen();
        p->setBrush(Qt::NoBrush);
        p->setPen(QPen(color, size));
        
        p->rotate(angle);
        p->drawText(position,text);
        p->rotate(-angle);

        p->setPen(currPen);
    }

    ~QPainter2DWrapper() = default;
};

#endif // VSS_UNIFICATION_QPAINTER2DWRAPPER_H
