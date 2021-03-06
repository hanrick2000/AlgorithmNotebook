#include <bits/stdc++.h>
using namespace std;
#define ll long long

// --------------------------------------------------------------------

typedef ll T;
struct Point {
    int x;
    int y;

    Point operator-(Point a) {return {x-a.x, y-a.y};}
    bool operator==(Point a) {return x==a.x&&y==a.y;}
    bool operator<(Point a) {
        return x<a.x || (x==a.x && y < a.y);
    }
};

T cross(Point a, Point b) {return a.x*b.y - a.y*b.x;}
T orient(Point a, Point b, Point c) {return cross(b-a, c-a);}

// Tested: https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_A

vector<Point> convex_hull(vector<Point> points) {
    int n = points.size();
    if(n <= 1) return points;
    vector<Point> hull;

    // Sorting Points
    sort(points.begin(), points.end());

    // it=0: Upper Hull
    // it=1: Lower Hull
    for(int it = 0; it < 2; ++it) {
        int sz = hull.size();
        for(int i = 0; i < n; ++i) {
            // if colineal are needed, use < and remove repeated points
            while(hull.size()>=sz+2 && orient(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        // Eliminating repeating points, start and end point
        hull.pop_back();
        reverse(points.begin(), points.end());
    }

    // removing duplicate points
    if(hull.size()==2 && hull[0]==hull[1]) hull.pop_back();

    return hull;
}
