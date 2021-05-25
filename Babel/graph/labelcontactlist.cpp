#include "labelcontactlist.h"
#include <QLabel>

LabelContactList::LabelContactList(QWidget *parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setText("Contacts list");
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
