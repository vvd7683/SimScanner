#include "sectionitem.h"

SectionItem::SectionItem(SSSection &sec_init,
                         QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    section(sec_init)
{

}
