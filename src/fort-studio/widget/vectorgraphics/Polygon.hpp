#pragma once


#include <QGraphicsPolygonItem>
#include "Shape.hpp"

#include <memory>

class Handle;

class Polygon : public Shape, public QGraphicsPolygonItem {
public:
	Polygon(const QVector<QPointF> & points,
	        QColor color,
	        QGraphicsItem * parent = nullptr);

	virtual ~Polygon();

	void addToScene(QGraphicsScene * scene);

	QVector<QPointF> vertices() const;

	Handle * appendPoint(const QPointF & point);

	void close();

protected:
	void paint(QPainter * painter,
	           const QStyleOptionGraphicsItem * option,
	           QWidget * widget) override;

	void mousePressEvent(QGraphicsSceneMouseEvent * e) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent * e) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * e) override;

private:
	void update(size_t i);
	void moveUpdate(const QPointF & newPos);
private:
	QVector<Handle*> d_handles;
	std::shared_ptr<QPointF> d_moveEvent;
};
