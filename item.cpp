#include "item.h"

Item::Item(QObject *parent, std::string name, float m_health, float health_, float damage_, float s_speed, float m_speed, float j_speed, float g_player_, float g_proyectiles_, float r_player_, float r_proyectile_, float e, std::string s_mode)
{
    max_health = m_health;
    health = health_;
    damage = damage_;
    shot_speed = s_speed;
    movement_speed = m_speed;
    jump_Speed = j_speed;
    g_player = g_player_;
    g_proyectiles = g_proyectiles_;
    r_player = r_player_;
    r_proyectiles = r_proyectile_;
    e_player = e;
    Shooting_mode = s_mode;

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

void Item::updateLabel(int x, int y)
{
    name->setGeometry(x, y - height - 4, name->width(), name->height());
    name->update();
}

QLabel *Item::getName() const
{
    return name;
}
float Item::getMax_health() const
{
    return max_health;
}
float Item::getHealth() const
{
    return health;
}
float Item::getDamage() const
{
    return damage;
}
float Item::getShot_speed() const
{
    return shot_speed;
}
float Item::getMovement_speed() const
{
    return movement_speed;
}
float Item::getJump_Speed() const
{
    return jump_Speed;
}
float Item::getG_player() const
{
    return g_player;
}
float Item::getG_proyectiles() const
{
    return g_proyectiles;
}
float Item::getR_player() const
{
    return r_player;
}
float Item::getR_proyectiles() const
{
    return r_proyectiles;
}
float Item::getE_player() const
{
    return e_player;
}
std::string Item::getShooting_mode() const
{
    return Shooting_mode;
}
