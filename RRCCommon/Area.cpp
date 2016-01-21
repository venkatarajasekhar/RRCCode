#include "Area.h"

Area::Area() : Position(0, 0) {
    m_width = 0;
    m_height = 0;
}

Area::Area(float x, float y, float width, float height) : Position(x, y) {
    m_width = width;
    m_height = height;
}

Area::~Area() {

}

float Area::width() const {
    return m_width;
}

void Area::setWidth(float width) {
    m_width = width;
}
float Area::height() const {
    return m_height;
}

void Area::setHeight(float height) {
    m_height = height;
}

bool Area::isInsideArea(Position pos) {
    if (m_x <= pos.x() && pos.x() <= m_x + m_width && m_y <= pos.y() && pos.y() <= m_y + m_height) {
        return true;
    } else {
        return false;
    }
}



