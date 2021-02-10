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

#include "PeopleTraffic.hpp"
#include <math.h>

void calculateModelingStep(EsBimBinding::SP& aBim, EsCfgModel::SP &aModelCfg);

PeopleTraffic::PeopleTraffic(EsBimBinding::SP aBim,
                             Safety::SP aSafety,
                             const EsCfgModel::SP aModelCfg) :
                                                                bim(aBim),
                                                                safetyZone(aSafety),
                                                                modelCfg(aModelCfg)
{
    calculateModelingStep(bim, modelCfg);
}

PeopleTraffic::PeopleTraffic(const PeopleTraffic &aPeopleTraffic) :
    bim(aPeopleTraffic.bim.Clone()),
    safetyZone(aPeopleTraffic.safetyZone.Clone()),
    modelCfg(aPeopleTraffic.modelCfg.Clone()),
    blockedElements(aPeopleTraffic.blockedElements)
{}

void addPeople(BaseElement::SP &aElement, double aNumberOfPeople)
{
    double newNumOfPeople = aElement.Vn().getNumOfPeople() + aNumberOfPeople;
    aElement.Vn().setNumOfPeople(newNumOfPeople);
}

void removePeople(BaseElement::SP &aElement, double aNumberOfPeople)
{
    double newNumOfPeople = aElement.Vn().getNumOfPeople() - aNumberOfPeople;
    aElement.Vn().setNumOfPeople(newNumOfPeople);
}

void passedPeopleThroughDoor(Door::SP &aDoor, double aNumberOfPeople)
{
    double newNumOfPeople = aDoor.Vn().getPassedPeople() + aNumberOfPeople;
    aDoor.Vn().setPassedPeople(newNumOfPeople);
}

void countingNumberOfPeople(EsBimBinding::SP& aBim, double& aNumOfPeople)
{
    aNumOfPeople = 0;
    for (auto& item : aBim.Vn().getElements())
    {
        aNumOfPeople += item.second.Vn().getNumOfPeople();
    }
}

void calculateModelingStep(EsBimBinding::SP& aBim, EsCfgModel::SP &aModelCfg)
{
    double averageSize = aBim.Vn().getArea() / aBim.Vn().getElements().size();
    double hxy = std::sqrt(averageSize);                                // характерный размер области, м

    if (aModelCfg.VCn().getModelingStep() - std::numeric_limits<double>::epsilon() < 0) //epsilon = 2.22045e-016
    {
        aModelCfg.Vn().setModelingStep((hxy / aModelCfg.VCn().getVelocityMax()) * 0.1);    // Шаг моделирования, мин
    }

    std::cout << "[PeopleTraffic::calculateModelingStep::"<<__LINE__<<"]: " << "Характерный размер области, м.: "_sv << hxy << std::endl;
    std::cout << "[PeopleTraffic::calculateModelingStep::"<<__LINE__<<"]: " << "Шаг моделирования, мин.: "_sv << aModelCfg.VCn().getModelingStep()
              << " (" << aModelCfg.VCn().getModelingStep() * 60 << " сек.)" << std::endl;
}

/**
 * Функция скорости. Базовая зависимость, которая позволяет определить скорость людского
 * потока по его плотности
 * @brief velocity
 * @param aV0   начальная скорость потока
 * @param aA    коэффициент вида пути
 * @param aD    текущая плотность людского потока на участке, чел./м2
 * @param aD0   допустимая плотность людского потока на участке, чел./м2
 * @return      скорость, м/мин.
 */
double velocity(double aV0, double aA, double aD, double aD0)
{
    return aV0 * (1.0 - aA * std::log(aD / aD0));
}

/**
 * @brief speedThroughDoor
 * @param aWidth            ширина проема, м
 * @param aDensityInElem    плотность в элементе, чел/м2
 * @return                  скорость потока в проеме в зависимости от плотности, м/мин
 */
double speedThroughDoor(double aWidth, double aDensityInElem, double aVMax)
{
    double v0 = aVMax;
    double d0 = 0.65;
    double a = 0.295;
    double v0k = -1;

    if (aDensityInElem > d0)
    {
        double m = (aDensityInElem > 5) ? (1.25 - 0.05 * aDensityInElem) : 1;
        v0k = velocity(v0, a, aDensityInElem, d0) * m;

        if (aDensityInElem >= 9 && aWidth < 1.6)
        {
            v0k = 10 * (2.5 + 3.75 * aWidth) / d0;
        }
    } else
    {
        v0k = v0;
    }
    assert(v0k > 0);
    return v0k;
}

/**
 * @param dElem плотность в элементе, из которого выходит поток
 * @return Скорость потока по горизонтальному пути, м/мин
 */
double speedInRoom(double aDensityInElem, double aVMax)
{
    double v0 = aVMax; // м/мин
    double d0 = 0.51;
    double a = 0.295;

    return aDensityInElem > d0 ? velocity(v0, a, aDensityInElem, d0) : v0;
}

/**
 * @param aDirect направление движения (direct = 1 - вверх, = -1 - вниз)
 * @param aDensityInElem  плотность в элементе
 * @return Скорость потока при движении по лестнице в зависимости от
 * плотности, м/мин
 */
double speedOnStair(double aDensityInElem, int aDirect)
{
    double d0 = 0, v0 = 0, a = 0;

    if (aDirect > 0)
    {
        d0 = 0.67;
        v0 = 50;
        a = 0.305;
    }
    else if (aDirect < 0)
    {
        d0 = 0.89;
        v0 = 80;
        a = 0.4;
    }

    return aDensityInElem > d0 ? velocity(v0, a, aDensityInElem, d0) : v0;
}

/**
 * Метод определения скорости движения людского потока по разным зонам
 *
 * @param aReceivingElement    зона, в которую засасываются люди
 * @param aGiverElement        зона, из которой высасываются люди
 * @return Скорость людского потока в зоне
 */
double speedInElement(  const BaseElement::SP &aReceivingElement,  // принимающая зона
                        const BaseElement::SP &aGiverElement,      // отдающая зона
                        const EsCfgModel::SP &aModelCfg)                           // максимальная скорость
{
    double densityInGiverElement = aGiverElement.VCn().getNumOfPeople() / aGiverElement.VCn().getAreaPolygon();
    // По умолчанию, используется скорость движения по горизонтальной поверхности
    double vZone = speedInRoom(densityInGiverElement, aModelCfg.VCn().getVelocityMax());

    double l1 = aReceivingElement.VCn().getLevel();
    double l2 = aGiverElement.VCn().getLevel();
    double dh = l1 - l2;                            // Разница высот зон

    // Если принимающее помещение является лестницей и находится на другом уровне,
    // то скорость будет рассчитываться как по наклонной поверхности
    if (std::abs(dh) > 1e-3 and aReceivingElement.VCn().getSign() == BimElementSign::Staircase)
    {
        // Иначе определяем направление движения по лестнице
        // -1 вниз, 1 вверх
        //         ______   aGiverItem
        //        /                         => direction = -1
        //       /
        // _____/           aReceivingItem
        //      \
        //       \                          => direction = 1
        //        \______   aGiverItem
        int direction = (dh > 0) ? -1 : 1;
        vZone = speedOnStair(densityInGiverElement, direction);
    }

    return vZone;
}

double speedOnExit( const BaseElement::SP &aReceivingElement,  // принимающая зона
                          BaseElement::SP &aGiverElement,      // отдающая зона
                    const double &aDoorWidth,
                    const EsCfgModel::SP &aModelCfg)
{
    // Определение скорости на выходе из отдающего помещения
    double vZone = speedInElement(aReceivingElement, aGiverElement, aModelCfg);
    double densityInGiverElement = aGiverElement.VCn().getNumOfPeople() / aGiverElement.VCn().getAreaPolygon();
    double vTransition = speedThroughDoor(aDoorWidth, densityInGiverElement, aModelCfg.VCn().getVelocityMax());
    double vAtExit = std::min(vZone, vTransition);

    assert(vAtExit > 0 && " Speed less than 0 ");
    return vAtExit;
}

double changeNumOfPeople(const BaseElement::SP &aGiverElement,
                         double aWidthDoor,
                         double aExitSpeed,     // Скорость перехода в принимающую зону
                         const EsCfgModel::SP &aModelCfg)
{
    double areaElement = aGiverElement.VCn().getAreaPolygon();
    double densityInElement = aGiverElement.VCn().getNumOfPeople() / areaElement;
    // Величина людского потока, через проем шириной aWidthDoor, чел./мин
    double P = densityInElement * aExitSpeed * aWidthDoor;
    // Зная скорость потока, можем вычислить конкретное количество человек,
    // которое может перейти в принимющую зону (путем умножения потока на шаг моделирования)
    double dN = P * aModelCfg.VCn().getModelingStep();

    return dN;
}

// Потенциал должен считаться до эвакуации из помещения или после?
double potentialElement(double aReceivingPotential, double aGiverAreaPolygon, double aExitSpeed)
{
    return aReceivingPotential + std::sqrt(aGiverAreaPolygon) / aExitSpeed;
}

/**
 * @brief movePeople
 * @param aReceivingItem    принимающее помещение
 * @param aGiverItem        отдающее помещение
 * @param aDoor             дверь между этими помещениями
 * @param aModelingConfig   настройки моделирования
 * @return  количество людей
 */
double movePeople( const BaseElement::SP &aReceivingItem,  // принимающая зона
                         BaseElement::SP &aGiverItem,      // отдающая зона
                   const BaseDoor::SP &aDoor,
                   const EsCfgModel::SP &aModelCfg)
{
    double areaElement = aGiverItem.VCn().getAreaPolygon();
    double peopleInGiverElement = aGiverItem.VCn().getNumOfPeople();
    double densityInElement = peopleInGiverElement / areaElement;
    double densityMin = aModelCfg.VCn().getDensityMin() > 0 ?
                aModelCfg.VCn().getDensityMin() : 0.5 / areaElement;

    // Ширина перехода между зонами зависит от количества человек,
    // которое осталось в помещении. Если там слишком мало людей,
    // то они переходя все сразу, чтоб не дробить их
    double doorWidth = aDoor.VCn().getWidth();//(densityInElement > densityMin) ? aDoor.VCn().getWidth() : std::sqrt(areaElement);
    double eSpeed = speedOnExit(aReceivingItem, aGiverItem, doorWidth, aModelCfg);

    // Подсчет потенциала
    double potentialGiverZone = potentialElement(aReceivingItem.VCn().getPotential(), areaElement, eSpeed);
    assert(potentialGiverZone > 0 && " PotentialGiverZone less than 0 ");

    // Если потенциал принимающего помещения больше, чем отдающего,
    // то людей не перемещаем
    if (aGiverItem.Vn().getPotential() <= potentialGiverZone)
    {
        return 0;
    }
    // иначе вычисляем задаем новый потенциал и вычисляем количество перемещаемых людей
    aGiverItem.Vn().setPotential(potentialGiverZone);

    // Доля вышедших людей
    double partFlowPeople = (densityInElement > densityMin)
            ? changeNumOfPeople(aGiverItem, doorWidth, eSpeed, aModelCfg)
            : peopleInGiverElement;

    //double partFlowPeople = changeNumOfPeople(aGiverItem, doorWidth, eSpeed, aModelCfg);

    // Кол. людей, которые могут покинуть помещение
    double ddPeople = (peopleInGiverElement > partFlowPeople) ? partFlowPeople : peopleInGiverElement;

    // Т.к. зона вне здания принята безразмерной,
    // в нее может войти максимально возможное количество человек
    if (aReceivingItem.VCn().getSign() == BimElementSign::Outside)
    {
        return ddPeople;
    }
    // Все другие зоны могут принять ограниченное количество человек.
    // Т.о. нужно проверить может ли принимающая зона вместить еще людей.
    // capacityRecivingElement - количество людей, которое еще может
    // вместиться до достижения максимальной плотности
    // => если может вместить больше, чем может выйти, то вмещает всех вышедших,
    // иначе вмещает только возможное количество.
    else
    {
        double maxNumOfPeople = aModelCfg.VCn().getDensityMax() * aReceivingItem.VCn().getAreaPolygon();
        double currentReceivingNumOfPeople = aReceivingItem.VCn().getNumOfPeople();
        double capacityRecivingElement = maxNumOfPeople - currentReceivingNumOfPeople;
        // Такая ситуация возникает при плотности в принимающем помещении более Dmax чел./м2
        // Фактически capacityRecivingElement < 0 означает, что помещение не может принять людей
        if (capacityRecivingElement < 0)
        {
            return 0;
        }
        double changePeople = (capacityRecivingElement > ddPeople) ? ddPeople : capacityRecivingElement;

        return changePeople;
    }
}

/**
 * @brief elementIsNotBlocked
 * @param aBlockedList
 * @param aElementUuid
 * @param aCurrentTime
 * @return true - если элемент не заблокирован.
 * Заблокированный элемент нельзя добавлять в очередь на обработку
 */
bool elementIsNotBlocked(const std::unordered_map<GpUUID, double>& aBlockedList,
                         const GpUUID& aElementUuid,
                         double aCurrentTime)
{
    std::unordered_map<GpUUID, double>::const_iterator t = aBlockedList.find(aElementUuid);
    return aBlockedList.empty() or
            t == aBlockedList.end() or
            t->second - aCurrentTime > 0
            ? true : false;
}

bool elementIsNotIncludeToListOfProcessing( const std::vector<BaseElement::SP>& aElementsToProcess,
                                            const BaseElement::SP& aGiverItem)
{
    return std::count(aElementsToProcess.begin(), aElementsToProcess.end(), aGiverItem) == 0;
}

/**
 * Формируются очереди, по которым в дальнейшем идет обход по зданию
 *
 * @param aQueue
 */
void PeopleTraffic::startFillQueue(std::vector<PeopleTraffic::Queue> &aQueues,
                                   double& aNumOfPeople,
                                   double aTimeStep)
{
    BaseElement::SP receivingElement = safetyZone;
    for (auto &d : bim.Vn().getDoorsOut())
    {
        const GpUUID& idQueue = d.first;
        BaseElement::SP& giverElement = bim.Vn().getElements().at(d.second.Vn().getOutputs().at(0));

        double ddPeople = movePeople(receivingElement, giverElement, d.second, modelCfg);
        removePeople(giverElement, ddPeople);               // Уменьшение количества людей в обрабатываемой зоне
        addPeople(receivingElement, ddPeople);
        //aNumOfPeople -= ddPeople;                         // Изменение количества людей в здании
        //passedPeopleThroughDoor(d.second, ddPeople);      // Увеличение счетчика людей, прошедших через дверь d
        giverElement.Vn().setQueueVisit(idQueue);           // Помещение освобождается через выход idQueue
        d.second.Vn().setTay(d.second.Vn().getTay() + 1);
        giverElement.Vn().setTay(d.second.Vn().getTay());

        // Очередь создается при условии, что помещение рядом с выходом не заблокировано
        if (elementIsNotBlocked(getBlockedElements(), giverElement.Vn().getId(), aTimeStep))
        {
            Queue q;
            q.uuid = idQueue;
            q.elements = {giverElement};
            q.potential = giverElement.Vn().getPotential();

            aQueues.push_back(q);       // Формирование списка очередей
        }
    }
}

/**
 * Перемещение людей на один шаг
 *
 * @param aTimeStep
 *
 * TODO
 * Эвакуация с первого этажа через окно
 * (добавить окна как двери, но видимо им требуются другие параметры скорости)
 * Определить направление движения из каждой комнаты
 * Эвакуация в безопасное помещение
 */
void PeopleTraffic::traffic1(double &aTimeStep, double& aNumOfPeople)
{
    auto CompQueue      = [](const Queue& left, const Queue& right){ return left.potential < right.potential; };
    auto CompElements   = [](const BaseElement::SP& left, const BaseElement::SP& right) { return left.VCn().getPotential() < right.VCn().getPotential(); };

    std::vector<Queue> queues;
    startFillQueue(queues, aNumOfPeople, aTimeStep);
    std::sort(queues.begin(), queues.end(), CompQueue);

    while (!queues.empty())
    {
        Queue& queueProcessed = queues.front();                                 // Первая очередь из списка
        QE& elementsToProcess = queueProcessed.elements;                        // Элементы для обработки (принимающие зоны)
        while (!elementsToProcess.empty())                                      // Обходим элементы очереди
        {
            BaseElement::SP receivingElement = elementsToProcess.front();       // Елемент, в который переходят люди
            elementsToProcess.erase(elementsToProcess.begin());

            for (const GpUUID &doorInUuid : receivingElement.V().getOutputs())  // Обходим всех соседей элемента очереди через двери
            {
                Door::SP &doorIn = bim.Vn().getDoorsAll().at(doorInUuid);
                if (doorIn.Vn().getSign() == BimElementSign::DoorWayOut) continue;     // Прекращаем обработку двери, если это эвакуационный выход
                if (doorIn.Vn().getTay() >= receivingElement.Vn().getTay()) continue;

                // Находим элемент, который является соседом для текущего помещения
                BaseElement::SP giverItem = bim.Vn().getElements().at(doorIn.Vn().getOutputs().at(0));    // Елемент, из которого люди выходят
                if (giverItem.Vn().getId() == receivingElement.Vn().getId())
                {
                    giverItem = bim.Vn().getElements().at(doorIn.Vn().getOutputs().at(1));
                }

                double movedPeople = movePeople(receivingElement, giverItem, doorIn, modelCfg);       // Количество людей, перешедших в другое помещение
                removePeople(giverItem, movedPeople);
                addPeople(receivingElement, movedPeople);

                doorIn.Vn().setTay(doorIn.Vn().getTay() + 1);
                giverItem.Vn().setTay(doorIn.Vn().getTay());

                // Элемент попадает в список на обработку при условиях, что
                // у него более 2 дверей
                // он не заблокирован
                // он не в списке на обработку
                if (giverItem.V().getOutputs().size() >= 2 and
                        elementIsNotBlocked(getBlockedElements(), giverItem.Vn().getId(), aTimeStep) and
                        std::count(elementsToProcess.begin(), elementsToProcess.end(), giverItem) == 0)
                {
                    elementsToProcess.push_back(giverItem);
                }
            }

            if (elementsToProcess.empty()) // Если в очереди нет помещений на обработку, очередь удаляется
            {
                queues.erase(queues.begin());
                break;
            }

            std::sort(elementsToProcess.begin(), elementsToProcess.end(), CompElements);
            queueProcessed.potential = elementsToProcess.front().Vn().getPotential();

            std::sort(queues.begin(), queues.end(), CompQueue);
            if (queueProcessed.potential >= queues.front().potential)
            {
                break;
            }
        }
    }

    aTimeStep += modelCfg.VCn().getModelingStep() * 60;
}

void PeopleTraffic::traffic2(double &aTimeStep, double &aNumOfLockedUpPeople)
{
    auto CompElements   = [](const BaseElement::SP& left, const BaseElement::SP& right)
                            {
                                return left.VCn().getPotential() < right.VCn().getPotential();
                            };

    // Шаг 1.
    for (auto &e : bim.Vn().getElements())
    {
        e.second.Vn().setPotential(std::numeric_limits<double>::max());
        e.second.Vn().setTay(0);
    }
    for (auto &d : bim.Vn().getDoorsAll())
    {
        d.second.Vn().setTay(0);
    }

    // Шаг 2.
    size_t numOfUnprocessedDoors    = bim.Vn().getDoorsAll().size();
    size_t numOfUnprocessedElements = bim.Vn().getElements().size();
    aNumOfLockedUpPeople = 0;

    BaseElement::SP receivingElement = safetyZone;
    std::vector<BaseElement::SP> elementsToProcess;
    for(;;)
    {
        // Шаг 3.
        for (const GpUUID &d : receivingElement.V().getOutputs())
        {
            Door::SP door = bim.Vn().getDoorsAll().at(d);
            if (door.Vn().getTay() != 0) continue;

            BaseElement::SP giverItem = bim.Vn().getElements().at(door.Vn().getOutputs().at(0)); // 3.1
            if (door.Vn().getSign() != BimElementSign::DoorWayOut)
            {
                if (giverItem.Vn().getId() == receivingElement.Vn().getId())
                {
                    giverItem = bim.Vn().getElements().at(door.Vn().getOutputs().at(1));
                }
            }

            // Количество людей, перешедших в другое помещение
            double movedPeople = movePeople(receivingElement, giverItem, door, modelCfg); // 3.1.1
            addPeople(receivingElement, movedPeople);   // 3.1.2
            removePeople(giverItem,     movedPeople);   // 3.1.3

            giverItem.Vn().setTay(1);   // 3.1.3
            door.Vn().setTay(1);        // 3.2
            door.Vn().setWhereFromPeopleGo(giverItem.VCn().getId(), movedPeople);
            --numOfUnprocessedDoors;    // -//-

            // Шаг 5.
            if (giverItem.V().getOutputs().size() >= 2 and
                elementIsNotBlocked(getBlockedElements(), giverItem.Vn().getId(), aTimeStep) and
                elementIsNotIncludeToListOfProcessing(elementsToProcess, giverItem))
            {
                elementsToProcess.push_back(giverItem);
            }
        } // Шаг 4. -> Шаг 3.

        // Шаг 5.
        std::sort(elementsToProcess.begin(), elementsToProcess.end(), CompElements);

        if (!elementsToProcess.empty())
        {// Шаг 6.
            receivingElement = elementsToProcess.front();
            elementsToProcess.erase(elementsToProcess.begin());
        }

        // Шаг 7.
        if (numOfUnprocessedElements != 0)
        {
            --numOfUnprocessedElements;
            continue; // -> Шаг 3.
        }

        // Шаг 8.
        if (numOfUnprocessedDoors != 0)
        {
            for (auto &e : bim.Vn().getElements())
            {
                if (e.second.Vn().getTay() == 0)
                {
                    aNumOfLockedUpPeople += e.second.VCn().getNumOfPeople();
                }
            }
        }
        break; // -> Шаг 9.
    }

    // Шаг 9.
    aTimeStep += modelCfg.VCn().getModelingStep() * 60; // -> Шаг 8.
}

void PeopleTraffic::blockElement(const GpUUID &aElement, double aBlockedTime)
{
    blockedElements.emplace(aElement, aBlockedTime);
}
