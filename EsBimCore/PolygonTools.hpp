/* Copyright (c) 2019 Boris Chirkov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */

#pragma once

#include "./JsonView/BimPolygonRing.hpp"
/**
 * @brief The PolygonTools class
 *
 * Класс статических методов для работы с полигонами
 */
class PolygonTools
{
    struct pt_t
    {
        double x;
        double y;
    };

public:
    using PointT = std::array<double, 2>; ///< Описание одной точки (x, y)
    using LineT = std::array<PointT, 2>; ///< Описание линии (pt1, pt2)
    using PolygonT = std::vector<std::vector<PointT>>; ///< Описание структуры полигона

public:
    PolygonTools(const PolygonTools& aPolygonTools)
    {}

public:
    /**
     * @brief pointInPolygon Метод проверки принадлежности точки полигону
     * @param aP Проверяемая точка
     * @param aPolygon Проверяемый полигон
     * @return True, если точка принадлежит полигону aPolygon, False - не принадлежит
     */
    static bool         pointInPolygon(const PointT &aP, const PolygonT &aPolygon);
    /**
     * @brief getAreaPolygon Метод получения площади элемента
     * @param aPolygon Используемый полигон
     * @return Площадь полигона в квадратных метрах
     */
    static double       getAreaPolygon(const BimPolygonRing::VecSP &aPolygon);
    /**
     * @brief toEarcutPolygons Подготовка данных из ПИМ к обработке библиотекой Earcut
     * @param aPolygon Используемый полигон
     * @return Полигон в формате PolygonT
     */
    static PolygonT     toEarcutPolygons(const BimPolygonRing::VecSP &aPolygon);
    /**
     * @brief getLengthSide Метод определения расстояния между точками
     * @param aP1 Первая точка
     * @param aP2 Вторая точка
     * @return Расстояние между точками в метрах
     */
    static double       getLengthSide(const PointT &aP1, const PointT &aP2);

    static bool         intersect(const PointT &aA, const PointT &aB, const PointT &aC, const PointT &aD);

    static PointT       nearestPoint(const PointT& aPoint, const LineT &aLine);

private:
    /**
     * @brief isPointInTriangle Метод проверки принадлежности точки заданному по точкам треугольнику
     * @return True, если точка в треугольнике, False - нет
     */
    static bool                                 isPointInTriangle(double aAx, double aAy, double aBx, double aBy, double aCx, double aCy, double aPx, double aPy);
    /**
     * @brief toTrianglePolygon Метод триангуляции полигона
     * @param aPolygon Триангулируемый полигон
     * @return Список треугольников, составляющих полигон
     */
    static std::vector<std::array<PointT, 3>>   toTrianglePolygon(const PolygonT &aPolygon);
    /**
     * @brief wherePoint Метод проверки положения точки относительно вектора AB
     * @return 1 - точка слева от вектора, -1 - точка справа, 0 - точка на векторе
     */
    static int                                  wherePoint(double aAx, double aAy, double aBx, double aBy, double aPx, double aPy);
};
