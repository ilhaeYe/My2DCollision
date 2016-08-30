#ifndef COLLISION_CHECK_H
#define COLLISION_CHECK_H

#include "Shape.h"

// AABB
bool AABBCollisionCheck(const Shape* s1, const Shape* s2);
bool AABBCollisionCheck(const AABB& aabb1, const AABB& aabb2);
bool IsGreaterPoint(const Point& p1, const Point& p2);

// OBB (SAT)
bool SATCollisionCheck(const DamageZonePolygon* dzp, const MyPolygon* p);
bool SATCollisionCheck(const MyPolygon* p1, const MyPolygon* p2);
bool SATCollisionCheck(const MyPolygon* p, const Circle* c);
bool SATCollisionCheck(const Circle* c1, const Circle* c2);
bool SATCollisionCheck(const vector<Point>& v1, const vector<Point>& v2);

#endif // !COLLISION_CHECK_H

