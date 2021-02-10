//
// Created by boris on 08.02.19.
//

#include <cmath>
#include "PolygonTools.hpp"

double PolygonTools::getAreaPolygon(const BimPolygonRing::VecSP &aPolygon)
{
    // Create array
    PolygonT polygon = toEarcutPolygons(aPolygon);
    std::vector<u_int_16> indices = mapbox::earcut<u_int_16>(polygon);

    //Вычисляем площадь по формуле S=(p(p-ab)(p-bc)(p-ca))^0.5;
    //p=(ab+bc+ca)0.5
    double areaElement = 0;
    std::vector<std::array<PointT, 3>> triangles = toTrianglePolygon(polygon);
    for (const auto &triangle : triangles)
    {
        const PointT &a = triangle.at(0);
        const PointT &b = triangle.at(1);
        const PointT &c = triangle.at(2);
        double ab = getLengthSide(a, b);
        double bc = getLengthSide(b, c);
        double ca = getLengthSide(c, a);
        double p = (ab + bc + ca) * 0.5;
        areaElement += std::sqrt(p * (p - ab) * (p - bc) * (p - ca));
    }

    return areaElement;
}

PolygonTools::PolygonT PolygonTools::toEarcutPolygons(const BimPolygonRing::VecSP &aPolygon)
{
    PolygonT polygon;

    for (const auto &i : aPolygon)
    {
        const BimPolygonRing &bpr = i.VC();
        std::vector<PolygonTools::PointT> points;
        for (const auto &j : bpr.getPoints())
        {
            const BimPolygonPoint &bpp = j.VC();
            points.push_back({bpp.getX(), bpp.getY()});
        }
        polygon.push_back(points);
    }

    return polygon;
}

double PolygonTools::getLengthSide(const PolygonTools::PointT &aP1, const PolygonTools::PointT &aP2)
{
    return std::sqrt(std::pow(aP1.at(0) - aP2.at(0), 2) + std::pow(aP1.at(1) - aP2.at(1), 2));
}

bool PolygonTools::pointInPolygon(const PolygonTools::PointT &aP, const PolygonTools::PolygonT &aPolygon)
{
    std::vector<std::array<PointT, 3>> triangles = toTrianglePolygon(aPolygon);
    bool result = false;
    for (const auto &triangle : triangles)
    {
        const PointT &A = triangle.at(0);
        const PointT &B = triangle.at(1);
        const PointT &C = triangle.at(2);
        result = isPointInTriangle(A.at(0), A.at(1), B.at(0), B.at(1), C.at(0), C.at(1), aP.at(0), aP.at(1));
        if (result == 1) break;
    }

    return result;
}

std::vector<std::array<PolygonTools::PointT, 3>> PolygonTools::toTrianglePolygon(const PolygonT &aPolygon) {
    std::vector<u_int_16> indices = mapbox::earcut<u_int_16>(aPolygon);

    std::vector<std::array<PointT, 3>> triangles;
    for(size_t k = 0; k < indices.size(); k += 3)
    {
        const PolygonTools::PointT &a = aPolygon.at(0).at(indices.at(k));
        const PolygonTools::PointT &b = aPolygon.at(0).at(indices.at(k + 1));
        const PolygonTools::PointT &c = aPolygon.at(0).at(indices.at(k + 2));
        triangles.push_back({a, b, c});
    }

    return triangles;
}

bool PolygonTools::isPointInTriangle(double aAx, double aAy, double aBx, double aBy, double aCx, double aCy, double aPx,
                                     double aPy)
{
    int q1 = wherePoint(aAx, aAy, aBx, aBy, aPx, aPy);
    int q2 = wherePoint(aBx, aBy, aCx, aCy, aPx, aPy);
    int q3 = wherePoint(aCx, aCy, aAx, aAy, aPx, aPy);

    return (q1 >= 0 and q2 >= 0 and q3 >= 0);
}

int PolygonTools::wherePoint(double aAx, double aAy, double aBx, double aBy, double aPx, double aPy)
{
    double s = (aBx - aAx) * (aPy - aAy) - (aBy - aAy) * (aPx - aAx);
    if (s > 0) return 1;        // Точка слева от вектора AB
    else if(s < 0) return -1;   // Точка справа от вектора AB
    else return 0;              // Точка на векторе, прямо по вектору или сзади вектора
}

// signed area of a triangle
inline double area(const PolygonTools::PointT &aA, const PolygonTools::PointT &aB, const PolygonTools::PointT &aC)
{
    return (aB.at(0) - aA.at(0)) * (aC.at(1) - aA.at(1)) - (aB.at(1) - aA.at(1)) * (aC.at(0) - aA.at(0));
}

// https://e-maxx.ru/algo/segments_intersection_checking
inline bool intersect_1(double a, double b, double c, double d)
{
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

// check if two segments intersect
bool PolygonTools::intersect(const PointT &aA, const PointT &aB, const PointT &aC, const PointT &aD)
{
    return intersect_1(aA.at(0), aB.at(0), aC.at(0), aD.at(0))
        && intersect_1(aA.at(1), aB.at(1), aC.at(1), aD.at(1))
        && area(aA, aB, aC) * area(aA, aB, aD) <= 0
        && area(aC, aD, aA) * area(aC, aD, aB) <= 0;
}
// Определение точки на линии, расстояние до которой от заданной точки является минимальным из существующих
PolygonTools::PointT PolygonTools::nearestPoint(const PointT& aPoint, const LineT& aLine)
{
    struct pt_t a = {aLine.at(0).at(0), aLine.at(0).at(1)};
    struct pt_t b = {aLine.at(1).at(0), aLine.at(1).at(1)};

    if (getLengthSide(aLine.at(0), aLine.at(1)) < 1e-9)
    {
        return aLine.at(0);
    }

    double A = aPoint.at(0) - a.x;
    double B = aPoint.at(1) - a.y;
    double C = b.x - a.x;
    double D = b.y - a.y;

    double dot = A * C + B * D;
    double len_sq = C * C + D * D;
    double param = -1;

    if (len_sq != 0)
    {
        param = dot / len_sq;
    }

    double xx, yy;

    if (param < 0)
    {
        xx = a.x;
        yy = a.y;
    } else if (param > 1)
    {
        xx = b.x;
        yy = b.y;
    } else
    {
        xx = a.x + param * C;
        yy = a.y + param * D;
    }

    return PointT{xx, yy};
}

/*  { С какой стороны вектора лежит точка?                                     }
    { ------------------------------------------------------------------------ }
    { Если vector(a) и vector(b) - вектора a и b соответственно, то:           }
    {                                                                          }
    { vector(a)*vector(b) = ax*by - ay*bx = a*b*sin(beta-alfa)                 }
    { ax,ay,bx,by - координаты концов векторов                                 }
    { a - длина вектора a                                                      }
    { b - длина вектора b                                                      }
    { alfa - угол альфа для вектора a                                          }
    { beta - угол бета для вектора b                                           }
    {                                                                          }
    { Вывод: при общей начальной точке двух векторов их векторное произведение }
    {        больше нуля, если второй вектор направлен влево от первого,       }
    {        и меньше нуля, если вправо.                                       }
    {                                                                          }
    { Если известны две точки, то вектор, основанный на них можно получить     }
    { вычитанием двух векторов направленных из начала координат:               }
    { Например, есть точка A и точка B                                         }
    { вектор|AB| = Вектор|B| - Вектор|A|, иным словом AB_x = Bx-Ax, AB_y= By-Ay}
    {                                                                          }
    { Таким образом, получается:                                               }
    { Если есть вектор |AB|, заданный координатами ax,ay,bx,by и точка px,py,  }
    { то для того чтобы узнать лежит ли она слева или справа, надо узнать знак }
    { произведения:                                                            }
    { (bx-ax)*(py-ay)-(by-ay)*(px-ax)                                          }
    { ------------------------------------------------------------------------ }
*/
