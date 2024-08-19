#pragma once

class AttributeComponent {
private:
	// Leveling
	unsigned char		level;
	unsigned int		exp;

	// Attributes
	unsigned char		strength;
	unsigned char		agility;
	unsigned char		intelligence;

	// Stats
	unsigned int		hp;
	unsigned int		hpMax;

	// Inits
public:
	AttributeComponent();
	virtual ~AttributeComponent();

	// Accessors
	unsigned char		getLevel();
	unsigned int		getHp();
	unsigned int		getHpMax();

	// Core
	void			update();
};
