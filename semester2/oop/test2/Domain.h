#pragma once
#include <string>
using namespace std;
class Engine
{
protected:
    double basePrice;
public:
    Engine() : basePrice(3000) {};
    virtual ~Engine() = default;
    virtual double getPrice() const {
        return this->basePrice;
    };
    virtual string toString() const = 0;

};

class ElectricEngine :public Engine {
private:
    int autonomy;
public:
    ElectricEngine(int autonomy) : Engine(), autonomy(autonomy) {}
    double getPrice() const override;
    string toString() const override;
};

class TurboEngine : public Engine {
public:
    double getPrice() const override;
    string toString() const override;
};