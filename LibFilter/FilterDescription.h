#ifndef FILTERDESCRIPTION
#define FILTERDESCRIPTION

#include <QString>
#include <QPixmap>
#include "FilterId.h"
#include "FilterPortDescription.h"

struct FilterDescription {
    FilterId id;
    QString name;
    QPixmap icon;
    FilterPortDescriptionVector inputs;
    FilterPortDescriptionVector outputs;
};

#endif // FILTERDESCRIPTION

