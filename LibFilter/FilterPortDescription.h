#ifndef FILTERPORTDESCRIPTION
#define FILTERPORTDESCRIPTION

#include <QString>

// Description of a filter port
struct FilterPortDescription {
    QString name;
    QString type;
};

// Vector of filter port descriptions
typedef QVector<FilterPortDescription> FilterPortDescriptionVector;


#endif // FILTERPORTDESCRIPTION

