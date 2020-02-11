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
    
    /**
     Costruttore base.
     */
    Nave();
    
    /**
     Costruttore avanzato.
     Imposta i valori di default nei campi della classe.
     
     @param src puntatore alla classe risorse di gioco
     */
    Nave(Resources *src);
    
    /**
     Ritorna il valore di is_dead
     
     @return true se is_dead è vero, false altrimenti
     */
    bool getIsDead();
    
    /**
     Ritorna il valore di at_planet
    
     @return true se at_planet è vero, false altrimenti
    */
    bool getAtPlanet();
    
    /**
     Imposta il valore di is_dead
    
     @param atplanet nuovo valore di at_planet
    */
    void setAtPlanet(bool atplanet);
    
    /**
     Ritorna il valore di life_left
    
     @return valore di life_left
    */
    double getLifebar();
    
    /**
     Ritorna il valore di fuel_left
    
     @return valore di fuel_left
    */
    double getFuelbar();
    
    /**
     Imposta il valore di is_red
     
     @param red nuovo valore di is_red
     */
    void setIsRed(bool red);

    /**
     Aumenta il valore di fuel_left della quantità fuelbal
    
     @param fuelbar incremento di carburante
    */
    void increaseFuel(double fuelbar);
    
    /**
     Imposta il valore della velocità massima
     
     @param speed nuova velocità massima
     */
    void setTopSpeed(double speed);
    
    /**
     Imposta il valore dell'accelerazione massima
     
     @param acceleration nuova accelerazione massima
     */
    void setSpaceshipAcceleration(float acceleration);
    
    /**
     Ritorna il valore di planet_x
     
     @return valore di planet_x
     */
    double getX_planet();
    
    /**
     Ritorna il valore di planet_y
    
     @return valore di planet_y
     */
    double getY_planet();
    
    /**
     Ritorna il valore di points
    
     @return valore di points
     */
    int getPoints();
    
    /**
     Aumenta il valore di points della quantità new_points
    
     @param new_points incremento di points
     */
    void incrasePoints(int new_points);
    
    /**
    Imposta il valore di direction_x e direction_y
    
    @param newDx nuovo valore di direction_x
    @param newDy nuovo valore di direction_y
    */
	void setDxDy(double newDx, double newDy);
    
    /**
    Incrementa il valore di direction_x e direction_y
    
    @param offsetDx valore di incremento di direction_x
    @param offsetDy valore di incremento di direction_y
    */
	void addToDxDy(double offsetDx, double offsetDy);
    
    /**
     Ritorna il valore di angle_entering_planet
    
     @return valore di angle_entering_planet
     */
	double getAnglePlanet();
    
    /**
     Diminuise in modo costante la spinta della navicella, fino ad azzerarla.
     */
	void decayThrustInt();
    
    /**
     Verifica la creazione di nuovi proiettili e ne gestisce il loro comportamento
     
     @param terrain terreno della schermata in cui si trova la navicella
     */
    void weapons(Terrain *terrain);
    
    /**
     Mostra il raggio traente premendo il pulsante associato.
     
     @return true se il raggio è attivato e visualizzato, false altrimenti
     */
    bool tractorRay();
    
    /**
     Verifica la possibilità della nave di subire danno.
     In caso di esito positivo diminuisce la salute e rende il giocatore temporaneamente immune.
     */
	void getHit(int damage, int hit_type = 0);
    
    /**
     Respinge il giocatore nel verso opposto alla sua direzione.
     
     @param distance distanza di spinta
     @param dir se 0 si muove nella direzione opposta, se 1 si dirige verso il centro della schermata (boss)
     */
	void push_back(int distance, int dir = 0);
    
    /**
     Gestisce i movimenti della nave e verifica lo stato del carburante e salute rimasta, ponendo is_dead a true se necessario.
     */
    void handle();
    
    /**
     Gestisce la visualizzazione della propulsione della nave
     */
    void handleThrust();
    
    /**
     Regola i movimenti della nave.
     Ruota la nave, diminuisce il carburante durante l'accelerazione e modifica la velocità attuale.
     */
    void movements();
    
    /**
     Memorizza le statistiche di posizione della nave prima dell'entrata dentro un pianeta e ne imposta i corretti valori per il movimento al suo interno.
     
     @param planetPos coordinate del pianeta d'entrata
     */
    void braceForEntry(Vector2f planetPos);
    
    /**
     Riporta i valori di carburante e salute al massimo
     */
    void resetStats();
};
