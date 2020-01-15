#ifndef Nave_hpp
#define Nave_hpp

#include "TripleBullets.hpp"

class Nave{
    
protected:
    static constexpr float TOTAL_LIFE = 100;
    static constexpr float TOTAL_FUEL = 100;

    Resources *src;
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
    
    Clock DamageClock;
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
    bool getInGame();
    void setInGame(bool ingame);
    bool getAtPlanet();
    void setAtPlanet(bool atplanet);
    double getLifebar();
    void setLifebar(double lifebar);
    double getFuelbar();
    void setFuelbar(double fuelbar);
    double getTopSpeed();
    void setTopSpeed(double speed);
    float getSpaceshipAcceleration();
    void setSpaceshipAcceleration(float acceleration);
    double getX_planet();
    void setX_planet(double x);
    double getY_planet();
    void setY_planet(double y);
    int getPunti();
    void setPunti(int punti);
	void setDxDy(double newDx, double newDy);
	void addToDxDy(double offsetDx, double offsetDy);
	double getDx();
	double getDy();
	double getCurrentSpeed();
	void setCurrentSpeed(double speed);
	void setAnglePlanet(double angle);
	double getAnglePlanet();
	void setThrustInt(int boost);
	int getThrustInt();
	void decayThrustInt();
    
    // FUNZIONI ======================================
    void armi(Terreno *terrain);
    bool raggioTraente();
	void getHit(int damage, int hitType = 0);
	void push_back(int distance, int dir = 0);
    void gestisci();
    void handleThrust();
    void movements();
    void braceForEntry(Vector2f planetPos, int larghezza);
    void resetStats();
};

#endif /* Nave_hpp */
