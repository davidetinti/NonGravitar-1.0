#ifndef Nave_hpp
#define Nave_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include "Bullets.hpp"
#define _USE_MATH_DEFINES

using namespace sf;
using namespace std;

class Nave{
    
protected:
    
    bool IsDead;
    bool AtPlanet;
    float Lifebar;
    float Fuelbar;
    double TopSpeed;
	double CurrentSpeed;
    double SpaceshipAcceleration;
    double X_planet,Y_planet,dx,dy;
    double Time_btw_hitS;
    double Time_btw_pushesMS;
    int punti;
	double angle_entering_planet;
    int raggiox,raggioy;
    ptr_Texture Nave_tx,Bar_tx,raggio_tx,thrust_tx;
	int thrust_int;
    
public:
    
    Clock DamageClock;
    Clock PushClock;
    Sprite nave;
    Sprite raggio;
    Bullets SingleShot;
    Bullets Laser;
	Sprite thrust;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Nave();
    Nave(int lenght, int heigth, Risorse *src);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
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
    double getSpaceshipAcceleration();
    void setSpaceshipAcceleration(double acceleration);
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
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void armi(RenderWindow *window, Terreno *terrain, Time perFrame);
    void raggiotraente(RenderWindow *window);
	void getHit(int damage, int hitType = 0);
	void push_back(int distance);
    void gestisci();
};

#endif /* Nave_hpp */
