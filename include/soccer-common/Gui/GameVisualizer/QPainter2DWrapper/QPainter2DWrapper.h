#ifndef VSS_UNIFICATION_QPAINTER2DWRAPPER_H
#define VSS_UNIFICATION_QPAINTER2DWRAPPER_H

#include "soccer-common/Gui/GameVisualizer/Painter2DBase/Painter2DBase.h"
#include <QPainter>
#include <QBrush>

class QPainter2DWrapper: public Painter2DBase {
    QPainter* p = nullptr;
    QBrush* br = nullptr;
public:

    void setPainter(QPainter* painter){
        p = painter;
    }

    void setBrush(QBrush* brush){
        br = brush;
    }

    inline void drawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c, const QColor& color) override {
        br->setColor(color);

        QPointF tri[] = {
            a,b,c
        };

        p->drawConvexPolygon(tri, 3);
    }

    inline void drawFilledQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d, const QColor& color) override {
        br->setColor(color);
        QPointF quad[] = {a,b,c,d};
        p->drawPolygon(quad, 4);
    }

    inline void drawFilledRectangle(const Vertex& topLeft, const Vertex& bottomRight, const QColor& color) override {
        br->setColor(color);
        const auto& rect = QRectF(topLeft, bottomRight);
        p->drawRect(rect);
    }
    
    inline void drawPolygon(Polygon polygon, const QColor& color, qreal thickness) override {
        br->setColor(color);
        auto* points = new QPointF[polygon.size()];
        for(int i=0; i<polygon.size(); i++){
            points[i] = polygon[i];
        }
        p->drawPolygon(points, polygon.size());
        if(thickness != 0)
            return;
    }

    inline void drawFilledConvexPolygon(Polygon polygon, const QColor& color) override {
        br->setColor(color);
        auto* points = new QPointF[polygon.size()];
        for(int i=0; i<polygon.size(); i++){
            points[i] = polygon[i];
        }
        p->drawConvexPolygon(points, polygon.size());
    }

    inline void drawFilledPolygon(Polygon polygon, const QColor& color) override {
        br->setColor(color);
        auto* points = new QPointF[polygon.size()];
        for(int i=0; i<polygon.size(); i++){
            points[i] = polygon[i];
        }
        p->drawPolygon(points, polygon.size());
    }

    inline void drawPolyline(Polygon polyline, const QColor& color, qreal thickness) override {
        br->setColor(color);
        auto* points = new QPointF[polyline.size()];
        for(int i=0; i<polyline.size(); i++){
            points[i] = polyline[i];
        }
        p->drawPolyline(points, polyline.size());
        if(thickness != 0)
            return;
    }

    inline void drawLine(const Vertex& a, const Vertex& b, const QColor& color, qreal thickness) override {
        br->setColor(color);
        p->drawLine(a, b);
        if(thickness != 0)
            return;
    }

    inline void drawFilledCircle(const Vertex& origin, qreal radius, const QColor& color) override {
        br->setColor(color);
        p->drawEllipse(origin, radius, radius);
    }

    inline QColor backgroundColor() override {
        return p->background().color();
    }

    inline void drawText(const QString& text, const Vertex& position, qreal size, const QColor& color, qreal angle = 0.0, HAlign hAlign = HAlign::Center, VAlign vAlign = VAlign::Middle) override {
        br->setColor(color);
        p->drawText(position,text);
    }

    ~QPainter2DWrapper(){
        delete p;
        delete br;
    }
};

#endif // VSS_UNIFICATION_QPAINTER2DWRAPPER_H