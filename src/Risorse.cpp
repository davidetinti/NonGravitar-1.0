#include "pch.h"
#include "Risorse.hpp"

using namespace std;
using namespace sf;

Risorse::Risorse(){
    if (!sound[0].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/player_bullet.ogg")) {
        if (!sound[0].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/player_bullet.ogg")) {
            if (!sound[0].loadFromFile("./../resources/player_bullet.ogg")) {
                cout << "Errore nel caricamento del suono player_bullet.ogg";
            }
        }
    }
    if (!texture[0].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/player_bullet_tx.png")) {
        if (!texture[0].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/player_bullet_tx.png")) {
            if (!texture[0].loadFromFile("./../resources/player_bullet_tx.png")) {
                cout << "Errore nel caricamento dell'immagine player_bullet_tx.png";
            }
        }
    }
    if (!texture[1].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/player_laser_tx.png")) {
        if (!texture[1].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/player_laser_tx.png")) {
            if (!texture[1].loadFromFile("./../resources/player_laser_tx.png")) {
                cout << "Errore nel caricamento dell'immagine player_laser_tx.png";
            }
        }
    }
    if (!texture[2].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/nongravitar.png")) {
        if (!texture[2].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/nongravitar.png")) {
            if (!texture[2].loadFromFile("./../resources/nongravitar.png")) {
                cout << "Errore nel caricamento dell'immagine nongravitar.png";
            }
        }
    }
    if (!texture[3].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/bunker_tx.png")) {
        if (!texture[3].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/bunker_tx.png")) {
            if (!texture[3].loadFromFile("./../resources/bunker_tx.png")) {
                cout << "Errore nel caricamento dell'immagine bunker_tx.png";
            }
        }
    }
    if (!texture[4].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/nave_tx.png")) {
        if (!texture[4].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/nave_tx.png")) {
            if (!texture[4].loadFromFile("./../resources/nave_tx.png")) {
                cout << "Errore nel caricamento dell'immagine nave_tx.png";
            }
        }
    }
    if (!texture[5].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet3.png")) {
        if (!texture[5].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet3.png")) {
            if (!texture[5].loadFromFile("./../resources/planet3.png")) {
                cout << "Errore nel caricamento dell'immagine planet3.png";
            }
        }
    }
    if (!texture[6].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet4.png")) {
        if (!texture[6].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet4.png")) {
            if (!texture[6].loadFromFile("./../resources/planet4.png")) {
                cout << "Errore nel caricamento dell'immagine planet4.png";
            }
        }
    }
    if (!texture[7].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet5.png")) {
        if (!texture[7].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet5.png")) {
            if (!texture[7].loadFromFile("./../resources/planet5.png")) {
                cout << "Errore nel caricamento dell'immagine planet5.png";
            }
        }
    }
    if (!texture[8].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet6.png")) {
        if (!texture[8].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet6.png")) {
            if (!texture[8].loadFromFile("./../resources/planet6.png")) {
                cout << "Errore nel caricamento dell'immagine planet6.png";
            }
        }
    }
    if (!texture[9].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet7.png")) {
        if (!texture[9].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet7.png")) {
            if (!texture[9].loadFromFile("./../resources/planet7.png")) {
                cout << "Errore nel caricamento dell'immagine planet7.png";
            }
        }
    }
    if (!texture[10].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet8.png")) {
        if (!texture[10].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet8.png")) {
            if (!texture[10].loadFromFile("./../resources/planet8.png")) {
                cout << "Errore nel caricamento dell'immagine planet8.png";
            }
        }
    }
    if (!texture[11].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet9.png")) {
        if (!texture[11].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet9.png")) {
            if (!texture[11].loadFromFile("./../resources/planet9.png")) {
                cout << "Errore nel caricamento dell'immagine planet9.png";
            }
        }
    }
    if (!texture[12].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/planet10.png")) {
        if (!texture[12].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/planet10.png")) {
            if (!texture[12].loadFromFile("./../resources/planet10.png")) {
                cout << "Errore nel caricamento dell'immagine planet10.png";
            }
        }
    }
    if (!texture[13].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/inside.png")) {
        if (!texture[13].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/inside.png")) {
            if (!texture[13].loadFromFile("./../resources/inside.png")) {
                cout << "Errore nel caricamento dell'immagine inside.png";
            }
        }
    }
    if (!texture[14].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/bullet1_tx.png")) {
        if (!texture[14].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/bullet1_tx.png")) {
            if (!texture[14].loadFromFile("./../resources/bullet1_tx.png")) {
                cout << "Errore nel caricamento dell'immagine bullet1_tx.png";
            }
        }
    }
    if (!texture[15].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/bullet2_tx.png")) {
        if (!texture[15].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/bullet2_tx.png")) {
            if (!texture[15].loadFromFile("./../resources/bullet2_tx.png")) {
                cout << "Errore nel caricamento dell'immagine bullet2_tx.png";
            }
        }
    }
    if (!texture[16].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/bar.png")) {
        if (!texture[16].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/bar.png")) {
            if (!texture[16].loadFromFile("./../resources/bar.png")) {
                cout << "Errore nel caricamento dell'immagine bar.png";
            }
        }
    }
    if (!texture[17].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/raggio.png")) {
        if (!texture[17].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/raggio.png")) {
            if (!texture[17].loadFromFile("./../resources/raggio.png")) {
                cout << "Errore nel caricamento dell'immagine raggio.png";
            }
        }
    }
    if (!texture[18].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/fueltank.png")) {
        if (!texture[18].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/fueltank.png")) {
            if (!texture[18].loadFromFile("./../resources/fueltank.png")) {
                cout << "Errore nel caricamento dell'immagine fueltank.png";
            }
        }
    }
    if (!texture[19].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/explosion1.png")) {
        if (!texture[19].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/explosion1.png")) {
            if (!texture[19].loadFromFile("./../resources/explosion1.png")) {
                cout << "Errore nel caricamento dell'immagine explosion1.png";
            }
        }
    }
    if (!texture[20].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/explosion2.png")) {
        if (!texture[20].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/explosion2.png")) {
            if (!texture[20].loadFromFile("./../resources/explosion2.png")) {
                cout << "Errore nel caricamento dell'immagine explosion2.png";
            }
        }
    }
    if (!texture[21].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/credits.png")) {
        if (!texture[21].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/credits.png")) {
            if (!texture[21].loadFromFile("./../resources/credits.png")) {
                cout << "Errore nel caricamento dell'immagine credits.png";
            }
        }
    }
    if (!texture[22].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/esci.png")) {
        if (!texture[22].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/esci.png")) {
            if (!texture[22].loadFromFile("./../resources/esci.png")) {
                cout << "Errore nel caricamento dell'immagine esci.png";
            }
        }
    }
    if (!texture[23].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/gioca.png")) {
        if (!texture[23].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/gioca.png")) {
            if (!texture[23].loadFromFile("./../resources/gioca.png")) {
                cout << "Errore nel caricamento dell'immagine gioca.png";
            }
        }
    }
    if (!texture[24].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/indietro.png")) {
        if (!texture[24].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/indietro.png")) {
            if (!texture[24].loadFromFile("./../resources/indietro.png")) {
                cout << "Errore nel caricamento dell'immagine indietro.png";
            }
        }
    }
    if (!texture[25].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/1.png")) {
        if (!texture[25].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/1.png")) {
            if (!texture[25].loadFromFile("./../resources/1.png")) {
                cout << "Errore nel caricamento dell'immagine 1.png";
            }
        }
    }
    if (!texture[26].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/2.png")) {
        if (!texture[26].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/2.png")) {
            if (!texture[26].loadFromFile("./../resources/2.png")) {
                cout << "Errore nel caricamento dell'immagine 2.png";
            }
        }
    }
    if (!texture[27].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/3.png")) {
        if (!texture[27].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/3.png")) {
            if (!texture[27].loadFromFile("./../resources/3.png")) {
                cout << "Errore nel caricamento dell'immagine 3.png";
            }
        }
    }
    if (!texture[28].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/nongravitar.png")) {
        if (!texture[28].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/nongravitar.png")) {
            if (!texture[28].loadFromFile("./../resources/nongravitar.png")) {
                cout << "Errore nel caricamento dell'immagine nongravitar.png";
            }
        }
    }
    if (!texture[29].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/terra.png")) {
        if (!texture[29].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/terra.png")) {
            if (!texture[29].loadFromFile("./../resources/terra.png")) {
                cout << "Errore nel caricamento dell'immagine terra.png";
            }
        }
    }
	if (!texture[30].loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/thrust.png")) {
		if (!texture[30].loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/thrust.png")) {
			if (!texture[30].loadFromFile("./../resources/thrust.png")) {
				cout << "Errore nel caricamento dell'immagine thrust.png";
			}
		}
	}
}

SoundBuffer Risorse::caricaSuono(int n){
    return sound[n];
}

ptr_Texture Risorse::caricaTexture(int n){
    return &texture[n];
}
