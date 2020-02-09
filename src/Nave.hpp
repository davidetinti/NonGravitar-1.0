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
    bool is_dead;
    bool at_planet;
    float life_left;
    float fuel_left;
    double top_speed;
	double current_speed;
    float acceleration;
    double planet_x, planet_y;
    double direction_x, direction_y;
    double time_btw_hit_S;
    double time_btw_pushes_MS;
    double angle_entering_planet;
    int points;
    int thrust_int;
    double ray_x, ray_y;
    Texture *spaceship_tx;
    Texture *ray_tx;
    Texture *thrust_tx;
    
public:
    
    bool in_boss;
    Clock last_hit;
    Clock push_clock;
    Sprite spaceship;
    Sprite thrust;
    Sprite ray;
    Bullets *SingleShot;
    Bullets *Laser;
    
    Nave();
    Nave(Resources *src);
    
    bool getIsDead();
    bool getAtPlanet();
    void setAtPlanet(bool atplanet);
    double getLifebar();
    double getFuelbar();
    void increaseFuel(double fuelbar);
    void setTopSpeed(double speed);
    void setSpaceshipAcceleration(float acceleration);
    double getX_planet();
    double getY_planet();
    int getPoints();
    void incrasePoints(int new_points);
	void setDxDy(double newDx, double newDy);
	void addToDxDy(double offsetDx, double offsetDy);
	double getAnglePlanet();
	void decayThrustInt();
    
    void armi(Terreno *terrain);
    bool raggioTraente();
	void getHit(int damage, int hit_type = 0);
	void push_back(int distance, int dir = 0);
    void gestisci();
    void handleThrust();
    void movements();
    void braceForEntry(Vector2f planetPos);
    void resetStats();
};
