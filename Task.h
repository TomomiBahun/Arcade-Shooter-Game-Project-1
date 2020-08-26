#pragma once

/* parent class of all game properties(player, enemies, bullets...)*/
class Task
{
public:
	Task() = default;
	virtual ~Task() = default;
	virtual bool update() = 0; // pure virtual function: force the subclass implement this
	virtual void draw() const = 0;
};