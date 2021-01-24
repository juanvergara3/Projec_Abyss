#include "item.h"

std::string Item::getSprite_name() const
{
    return sprite_name;
}

Item::Item(QWidget *parent, std::string name, float m_health, float health_, float damage_, float s_speed, float m_speed, float j_speed, float g_player_, float g_proyectiles_, float r_player_, float r_proyectile_, float e, std::string s_mode, std::string sprite)
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

    this->sprite = new QPixmap(sprite.c_str());
    this->sprite_name = sprite;

    this->name_label = new QLabel;
    //if(parent != nullptr)
        //this->name->setParent(parent);
    this->name = name;
    this->name_label ->setText(name.c_str());
    this->name_label ->setFont(QFont("System"));
    this->name_label ->setGeometry(0, 0, this->name_label ->text().length()*8, 20);
    this->name_label ->setStyleSheet("QLabel { background-color : rgba(33, 33, 33, 100); color : white; }");
    this->name_label ->setVisible(false);

    width = 32;
    height = 32;
}

Item::~Item(){
    delete name_label;
    delete sprite;
}

QRectF Item::boundingRect() const{
    return QRectF(0, 0, width, height);
}
void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    //painter->setBrush(Qt::red);
    painter->drawPixmap(0, 0, sprite->scaledToWidth(width), 0, 0, 128, 128);
    //painter->drawRect(boundingRect());
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

void Item::updateLabel(int x, int y) {
    name_label ->setGeometry(x, y - height - 4, name_label ->width(), name_label ->height());
    name_label ->update();
}

QLabel *Item::getName_label() const
{
    return name_label;
}
std::string Item::getName() const
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
