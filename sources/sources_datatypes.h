#ifndef SOURCES_DATA_TYPES_H
#define SOURCES_DATA_TYPES_H

#include <vector>
#include <string>



struct MarpleData {
    std::string marpleSigmaFileName = "";
    std::string marpleIonFileName = "";
};

enum class lagType {
    DISABLED,
    PLANE,
    SPHERE
};

struct Source {
    /**
    * \struct Source
    *
    * \brief родительская структура источников.
    */

    const std::string sourceName; /*!< Имя источника. */

    Source(std::string name) : sourceName(name) {}

    std::string sType; /*!< Тип источника. */
    std::vector<std::string> spNames; /*!< Массив имён файлов спектров источника. */
    std::vector<int> spNumbers; /*!< Массив номеров спектров источника. */
};

struct SurfaceSource : public Source {
    /**
    * \struct SurfaceSource
    *
    * \brief Поверхностный источник.
    */

    SurfaceSource(std::string sourceName) : Source(sourceName) {}

    int layerIndexFrom = -1;  /*!< Номер слой из которого направлен источник. */
    int layerIndexTo = -1;  /*!< Номер слой в который направлен источник. */
    int particleIndex = -1; /*!< Номер частицы. */
    std::vector<int> direction; /*!< Массив для определения направления движения. */
};

struct BoundariesSource : public Source {
    /**
    * \struct BoundariesSource
    *
    * \brief Источник с границы.
    */

    BoundariesSource(std::string sourceName) : Source(sourceName) {}

    int direction = -1;  /*!< направление источника. */
    int particleIndex = -1; /*!< Номер частицы. */
};

struct VolumeSource : public Source {
    /**
    * \struct VolumeSource
    *
    * \brief Объёмный источник.
    */

    VolumeSource(std::string sourceName) : Source(sourceName) {}

    int layerIndex = -1; /*!< Номер слоя. */
    int particleIndex = -1; /*!< Номер частицы. */
};

struct Volume78Source : public Source {
    /**
    * \struct Volume78Source
    *
    * \brief Объёмный источник для частиц 7 и 8.
    */
    Volume78Source(std::string sourceName) : Source(sourceName) {}

    int layerIndex = -1; /*!< Номер слоя. */
    int particleIndex = -1;  /*!< Номер частицы. */
    std::string distributionFileName; /*!< Массив имён файлов распределений. */
};

struct Distribution : public Source {
    /**
    * \struct Distribution
    *
    * \brief Структура для помещения токов и энерговыделений.
    */

    Distribution(std::string sourceName) : Source(sourceName) {}

    int layerIndex = -1; /*!< Номер слоя. */
    int particleIndex = -1; /*!< Номер частицы. */
};

struct Influence {
    /**
    * \struct Influence
    *
    * \brief Абстракция "воздействие" хранит в себе общую временную функцию и задержку для
    * набора источников.
    */

    const std::string influenceName; /*!< Название воздействия. */
    int influenceNumber = -1; /*!< Номер воздействия. */
    double amplitude = 0; /*!< Амплитуда воздействия. */
    int tfCount = 0;  /*!< Чисто значений временной функции. */


    Influence(std::string name) : influenceName(name) {
    }


    std::vector<double> tfTime; /*!< Массив времён, где определено значение временной функции. */
    std::vector<double> tfValue; /*!< Массив определния значений временной функции. */

    std::vector<Distribution *> Distributions; /*!< Хранилище источников типа Distribution. */
    std::vector<VolumeSource *> VolumeSources; /*!< Хранилище источников типа VolumeSource. */
    std::vector<Volume78Source *> Volume78Sources;  /*!< Хранилище источников типа Volume78Source. */
    std::vector<BoundariesSource *> BoundariesSources; /*!< Хранилище источников типа BoundariesSource. */
    std::vector<SurfaceSource *> SurfaceSources; /*!< Хранилище источников типа SurfaceSource. */


};

struct Lag {
    lagType type = lagType::DISABLED;

    // определяющие параметры геометрии источника
    // если источник близко (форма фронта - сфера) это его координаты
    // если далеко (форма фронта - плоскость) это вектор направления распросранения
    double param[3]{0.0, 0.0, 0.0};

    // вспомогательные параметры
    // точка расчетной области, первой попадающаяся на пути плоского фронта
    // в момент времени 0 фронт ее проходит
    double plane_param[3]{0.0, 0.0, 0.0};

};



#endif //SOURCES_DATA_TYPES_H