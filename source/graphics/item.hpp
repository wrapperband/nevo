#pragma once

#include <QGraphicsItem>

#include <la/vec.hpp>

#include <world/organism.hpp>
#include <world/spawn.hpp>

#include <view/item.hpp>


class ItemPlant : public Item {
public:
	constexpr static const char *COLOR = "#22CC22";
	
	ItemPlant(Plant *p) : Item(p) {
		color = QColor(COLOR);
	}
};

class ItemAnimal : public Item {
public:
	constexpr static const char 
		*ACOLOR = "#CCCCCC",
		*HCOLOR = "#FFFF22",
		*CCOLOR = "#FF2222";
	
	vec2 dir = vec2(1, 0);
	
	ItemAnimal(Animal *a) : Item(a) {
		if(dynamic_cast<Herbivore*>(a)) {
			color = QColor(HCOLOR);
		} else if(dynamic_cast<Carnivore*>(a)) {
			color = QColor(CCOLOR);
		} else {
			color = QColor(ACOLOR);
		}
	}
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		Item::paint(painter, option, widget);
		painter->drawLine(v2q(nullvec2), v2q(size*dir));
	}
	
	void sync(Entity *e) override {
		Item::sync(e);
		dir = dynamic_cast<Animal*>(e)->dir;
	}
};

class ItemSpawn : public Item {
public:
	ItemSpawn(Spawn *s) : Item(s) {
		if(dynamic_cast<SpawnAnimal*>(s)) {
			if(dynamic_cast<SpawnHerbivore*>(s)) {
				color = QColor(ItemAnimal::HCOLOR);
			} else if(dynamic_cast<SpawnCarnivore*>(s)) {
				color = QColor(ItemAnimal::CCOLOR);
			} else {
				color = QColor(ItemAnimal::ACOLOR);
			}
		} else if(dynamic_cast<SpawnPlant*>(s)) {
			color = QColor(ItemPlant::COLOR);
		} else {
			color = QColor(Item::COLOR);
		}
	}
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override {
		if(size > 0.0) {
			QColor c = color;
			c.setAlpha(127);
			QPen pen;
			pen.setWidth(4);
			pen.setCosmetic(true);
			pen.setColor(c);
			pen.setStyle(Qt::DotLine);
			painter->setPen(pen);
			painter->drawEllipse(boundingRect());
		}
	}
};
