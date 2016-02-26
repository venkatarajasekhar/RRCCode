#include "UIView.h"
#include <iostream>

UIView::UIView(QWidget *parent) : QGraphicsView(parent) {

}

UIView::UIView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {

}

void UIView::slot_dataAdded() {

}

