#ifndef UIVIEW_H
#define UIVIEW_H

#include <QGraphicsView>

class UIView : public QGraphicsView {
    Q_OBJECT
  public:
    UIView(QWidget *parent);
    UIView(QGraphicsScene *scene, QWidget *parent);

  public slots:
    void slot_dataAdded();
};

#endif // UIVIEW_H
