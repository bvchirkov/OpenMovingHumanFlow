/*Copyright (c) 2019 Boris Chirkov

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
THE SOFTWARE.
*/

// File created 08.04.2019

#pragma once

#include "PolygonTools.hpp"
#include "JsonView/BimElementSign.hpp"
/**
  @brief Базовая структура всех элементов здания

  Хранит поля, которые затем заполняются значениями из Json
  ПИМ здания.
*/
//             +-------+
//       +---->+ Base  <-------+
//       |     +-------+       |
//       |                     |
//       |                     |
// +----------+         +-------------+
// | BaseDoor |      +--> BaseElement <---+
// +-----^----+      |  +------^------+   |
//       |           |         |          |
//       |           |         |          |
//   +------+    +------+  +-------+ +--------+
//   | Door |    | Room |  | Stair | | Safety |
//   +------+    +------+  +-------+ +--------+

class Base
{
public:
    using SP        = GpSharedPtr<Base>;        ///< Shared Pointer
    using CSP       = GpSharedConstPtr<Base>;   ///< Const Shared Pointer
    using ItemsMapT = std::unordered_map<GpUUID, std::vector<GpUUID>>;

private:
    /**
     * @brief tay Признак посещения элемента
     *
     * Если tay равен 0, то элемент ни разу не посещался, если 1,
     * то был посещен при обходе графа.
     *
     * Если элемент был посещен, то второй заход в него запрещен.
     */
    size_t                                  tay     = 0;
    double									level   = -1;   ///< Уровень, на котором находится элемент
    mutable PolygonTools::PolygonT			polygon;        ///< Полигон элемента
    std::set<GpUUID>						visitedQueue;   ///< Список очередей, которые посетили элемент

public:
    Base() = default;
    Base(const Base& aBase);
	virtual ~Base() = default;

public:
    /**
     * @brief getId Идентификаторо элемента
     *
     * Генерируется в QGIS при создании ПИМ здания.
     * @return Уникальный идентификатор в формате GpUUID
     */
	virtual const GpUUID&                   getId()				const { THROW_NOT_IMPLEMENTED; }
    /**
     * @brief getName Название элемента
     *
     * Задается пользователем во время создания ПИМ здания
     * @return Название элемента в формате std::string_view
     */
    virtual std::string_view                getName()			const { THROW_NOT_IMPLEMENTED; }
    /**
     * @brief getSign Тип элемента
     *
     * Задается пользователем во время создания ПИМ здания
     * @return Тип элемента из BimElementSign
     */
    virtual BimElementSign                  getSign()			const { THROW_NOT_IMPLEMENTED; }
    /**
     * @brief getOutputs Список элементов, с которыми связан текущий элемент
     *
     * Формируется во время генерации ПИМ здания
     * @return Вектор идентификаторов
     */
    virtual const std::vector<GpUUID>&      getOutputs()		const { THROW_NOT_IMPLEMENTED; }
    /**
     * @brief getPolygonRings Описание геометрии элемента
     *
     * Формируется во время чтения ПИМ здания
     * @return Список точек полигона элемента
     */
    virtual const BimPolygonRing::VecSP&    getPolygonRings()	const { THROW_NOT_IMPLEMENTED; }

    /**
     * @brief getAreaPolygon
     * @return Площадь полигона в квадратных метрах
     */
	double									getAreaPolygon()	const;
    /**
     * @brief getPolygon
     * @return Список точек, образующих полигон элемента
     */
    const PolygonTools::PolygonT&           getPolygon()		const;
    /**
     * @brief setLevel Метод назначения уровня элементу
     * @param aLevel Уровень, на котором расположен элемент, в метрах
     */
	void                                    setLevel(double aLevel) { level = aLevel; }
    /**
     * @brief getLevel Метод получения уровня элемента
     * @return Уровень, на котором расположен элемент, в метрах
     */
	double                                  getLevel()			const { return level; }
    /**
     * @brief setQueueVisit Метод задания очереди, в которой обрабатывается элемент
     *
     * Очередь в данном случае определяется эвакуационным выходом. Сколько выходов, столько и
     * очередей.
     * @param aQueueName Идентификатор очереди
     */
	void                                    setQueueVisit(const GpUUID& aQueueName);
    /**
     * @brief isQueueVisit Метод определения участия элемента в очереди
     * @param aQueueName Идентификатор проверяемой очереди
     * @return True - элемент принадлежит очереди,
     *         False - не принадлежит
     */
	bool                                    isQueueVisit(const GpUUID& aQueueName) const;
    /**
     * @brief getQueueVisit Метод получения списка идентификаторов очередей, в которых
     * участвует элемент
     * @return Список идентификаторов
     */
	const std::set<GpUUID>&					getQueueVisit()		const;
    /**
     * @brief setTay Метод установки метки посещения элемента
     */
    void                                    setTay(size_t aTay)       { tay = aTay; }
    /**
     * @brief getTay Метод получения метки посещения элемента
     * @return величина tay
     */
    size_t                                  getTay()            const { return tay; }
};
