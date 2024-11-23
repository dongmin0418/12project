#pragma once

#ifndef SHAPE_H  
#define SHAPE_H
#include <stdio.h>
#include <stdbool.h>
#include <math.h> 

typedef struct {
    float x, y, z;
} Vector3D;

float crossProduct(float ax, float ay, float bx, float by);

bool isInsideSquare(Vector3D p, Vector3D a, Vector3D b, Vector3D c, Vector3D d);

bool isInsideTriangle(Vector3D p, Vector3D a, Vector3D b, Vector3D c);

bool isInsideCircle(Vector3D p, Vector3D center, float radius);


#endif
