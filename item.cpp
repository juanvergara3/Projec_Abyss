#include "item.h"

Item::Item(QObject *parent, std::string name, std::string stat, int value) : QObject(parent) {
    this->stat = stat;
    this->value = value;

    this->name = new QLabel;
    this->name->setText(name.c_str());
    this->name->setFont(QFont("System"));
    this->name->setGeometry(0, 0, this->name->text().length()*8, 20);
    this->name->setStyleSheet("QLabel { background-color : white; color : black; }");
    this->name->setVisible(false);

    width = 16;
    height = 16;

}
Item::~Item(){
    delete name;
}

QRectF Item::boundingRect() const{
    return QRectF(0, 0, width, height);
}
void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    painter->setBrush(Qt::red);
    //painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

int Item::getPosx() const {
    return posx;
}
int Item::getPosy() const {
    return posy;
}
int Item::getWidth() const {
    return width;
}
int Item::getHeight() const {
    return height;
}

QLabel *Item::getName() const
{
    return name;
}

void Item::updateLabel(int x, int y)
{
    name->setGeometry(x, y - height - 4, name->width(), name->height());
    name->update();
}
std::string Item::getStat() const {
    return stat;
}
int Item::getValue() const {
    return value;
}
