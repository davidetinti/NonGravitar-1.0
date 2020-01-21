#pragma once
#include "TripleBullets.hpp"

class Nave{
    
private:
    
    static constexpr float TOTAL_LIFE = 100;
    static constexpr float TOTAL_FUEL = 100;
    static const int HIT_TIMER_MS = 600;

protected:
    Resources *src;
    bool is_red;
    bool IsDead;
    bool AtPlanet;
    float life_left;
    float fuel_left;
    double TopSpeed;
	double CurrentSpeed;
    float SpaceshipAcceleration;
    double X_planet,Y_planet,dx,dy;
    double Time_btw_hitS;
    double Time_btw_pushesMS;
    double angle_entering_planet;
    int punti;
    int thrust_int;
    double raggiox,raggioy;
    Texture *Nave_tx,*Bar_tx,*raggio_tx,*thrust_tx;
    Animation* tractor_beam;
    
public:
    bool in_boss;
    Clock last_hit;
    Clock PushClock;
    Sprite nave;
    Sprite raggio;
    Bullets *SingleShot;
    Bullets *Laser;
	Sprite thrust;
    
    // COSTRUTTORI ===================================
    Nave();
    Nave(Resources *src);
    
    // SETTERS E GETTERS =============================
    bool getIsDead();
    void setIsDead(bool a);
    bool getAtPlanet();
    void setAtPlanet(bool atplanet);
    double getLifebar();
    double getFuelbar();
    void setFuelbar(double fuelbar);
    void setTopSpeed(double speed);
    void setSpaceshipAcceleration(float acceleration);
    double getX_planet();
    double getY_planet();
    int getPunti();
    void setPunti(int punti);
	void setDxDy(double newDx, double newDy);
	void addToDxDy(double offsetDx, double offsetDy);
	double getAnglePlanet();
	void decayThrustInt();
    
    // FUNZIONI ======================================
    void armi(Terreno *terrain);
    bool raggioTraente();
	void getHit(int damage, int hitType = 0);
	void push_back(int distance, int dir = 0);
    void gestisci();
    void handleThrust();
    void movements();
    void braceForEntry(Vector2f planetPos);
    void resetStats();
};
