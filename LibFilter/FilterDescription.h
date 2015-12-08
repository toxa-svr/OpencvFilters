#ifndef FILTERDESCRIPTION
#define FILTERDESCRIPTION

#include <QString>
#include <QPixmap>
#include "FilterId.h"

struct FilterDescription {
    FilterId id;
    QString name;
    QPixmap icon;
};

#endif // FILTERDESCRIPTION

