#pragma once
class SystemMain final {
public:
	SystemMain() = default;
	~SystemMain() = default;
	bool init() const;
	void deInit() const;
	void main() const;
};