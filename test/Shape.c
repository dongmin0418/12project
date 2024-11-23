#include "Shape.h"



float crossProduct(float ax, float ay, float bx, float by) {
    return ax * by - ay * bx;
}

// 도형 내부 체크 함수
bool isInsideSquare(Vector3D p, Vector3D a, Vector3D b, Vector3D c, Vector3D d) {
    float cross1 = crossProduct(b.x - a.x, b.y - a.y, p.x - a.x, p.y - a.y);
    float cross2 = crossProduct(c.x - b.x, c.y - b.y, p.x - b.x, p.y - b.y);
    float cross3 = crossProduct(d.x - c.x, d.y - c.y, p.x - c.x, p.y - c.y);
    float cross4 = crossProduct(a.x - d.x, a.y - d.y, p.x - d.x, p.y - d.y);
    return (cross1 > 0 && cross2 > 0 && cross3 > 0 && cross4 > 0) ||
        (cross1 < 0 && cross2 < 0 && cross3 < 0 && cross4 < 0);
}

bool isInsideTriangle(Vector3D p, Vector3D a, Vector3D b, Vector3D c) {
    float cross1 = crossProduct(b.x - a.x, b.y - a.y, p.x - a.x, p.y - a.y);
    float cross2 = crossProduct(c.x - b.x, c.y - b.y, p.x - b.x, p.y - b.y);
    float cross3 = crossProduct(a.x - c.x, a.y - c.y, p.x - c.x, p.y - c.y);
    return (cross1 > 0 && cross2 > 0 && cross3 > 0) ||
        (cross1 < 0 && cross2 < 0 && cross3 < 0);
}

bool isInsideCircle(Vector3D p, Vector3D center, float radius) {
    float distance = sqrt(pow(p.x - center.x, 2) + pow(p.y - center.y, 2));
    return distance < radius;
}