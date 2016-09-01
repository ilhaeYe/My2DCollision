#ifndef COLLISION_CHECK_H
#define COLLISION_CHECK_H

#include "Shape.h"

// AABB
bool AABBCollisionCheck(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
bool AABBCollisionCheck(vector<AABB> v1, vector<AABB> v2);
bool AABBCollisionCheck(AABB aabb1, AABB aabb2);
bool IsGreaterPoint(const Point& p1, const Point& p2);

// OBB (SAT)
//bool SATCollisionCheck(const DamageZonePolygon& dzp, const Shape& shape);
//bool SATCollisionCheck(const DamageZonePolygon& dzp, const MyPolygon& p);
bool SATCollisionCheck(std::shared_ptr<DamageZonePolygon> dzp, std::shared_ptr<MyPolygon> p);
bool SATCollisionCheck(std::shared_ptr<MyPolygon> p1, const MyPolygon& p2);
bool SATCollisionCheck(std::shared_ptr<MyPolygon> p, const Circle& c);
bool SATCollisionCheck(vector<Point> p1, vector<Point> p2);

AABB GetAABB(vector<Point> vertices, const Point & axisVec);
AABB GetAABB(const Circle& c, const Point & axisVec);
vector<Point> GetProjectedVertices(vector<Point> vertices, const Point& axisVector);
vector<Point> GetEdgesVector(const MyPolygon& p);
Point GetGapVector(const Point& p1, const Point& p2);








//bool SATCollisionCheck(std::shared_ptr<DamageZonePolygon> s1, std::shared_ptr<Shape> s2);
//bool SATCollisionCheck(std::shared_ptr<MyPolygon> p, std::shared_ptr<Circle> c);
//bool SATCollisionCheck(std::shared_ptr<MyPolygon> p1, std::shared_ptr<MyPolygon> p2);
//bool SATCollisionCheck(vector<Point> v1, vector<Point> v2);
//bool SATCollisionCheck(const Point& p1, const Point& p2);


//bool SATCollisionCheck(const DamageZonePolygon& dzp, const Shape& shape);
//bool SATCollisionCheck(const MyPolygon& p1, const MyPolygon& p2);
//bool SATCollisionCheck(vector<Point> p1, vector<Point> p2);
//
//AABB GetAABB(vector<Point> vertices, const Point & normalVector);
//vector<Point> GetProjectedVertices(vector<Point> vertices, const Point& normalVector);
//vector<Point> GetEdgesVector(const MyPolygon& p);
//vector<Point> GetNormalVectors(vector<Point> edges1, vector<Point> edges2);
//vector<Point> GetNormalVectors(vector<Point> edges);

#endif // !COLLISION_CHECK_H



//#ifndef COLLISION_CHECK_H
//#define COLLISION_CHECK_H
//
//#include "Shape.h"
//
////bool AABBCollisionCheck(const Shape& s1, const Shape& s2);
//bool AABBCollisionCheck(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
//bool AABBCollisionCheck(vector<AABB> v1, vector<AABB> v2);
//bool AABBCollisionCheck(AABB aabb1, AABB aabb2);
//bool IsGreaterPoint(const Point& p1, const Point& p2);
//
//bool SATCollisionCheck(const DamageZonePolygon& dzp, const MyPolygon& p);
//bool SATCollisionCheck(const MyPolygon& p1, const MyPolygon& p2);
//bool SATCollisionCheck(const MyPolygon& p, const Circle& c);
//bool SATCollisionCheck(vector<Point> p1, vector<Point> p2);
//
//AABB GetAABB(vector<Point> vertices, const Point & axisVec);
//AABB GetAABB(const Circle& c, const Point & axisVec);
//vector<Point> GetProjectedVertices(vector<Point> vertices, const Point& axisVector);
//vector<Point> GetEdgesVector(const MyPolygon& p);
//Point GetGapVector(const Point& p1, const Point& p2);
//
//#endif // !COLLISION_CHECK_H