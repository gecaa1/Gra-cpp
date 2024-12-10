#ifndef GRA_OSOBNIKI_H
#define GRA_OSOBNIKI_H
#include "organizm.h"
#include "mieszkaniec.h"
#include "ustawienia.h"
#include "generatorlosowy.h"
#include "sasiedztwo.h"

class Glon: protected Organizm, public Mieszkaniec {
public:
    Glon();
    virtual RodzajMieszkanca  kimJestes() final;
    virtual ZamiarMieszkanca
                    wybierzAkcje(Sasiedztwo sasiedztwo);
    virtual Mieszkaniec * dajPotomka();
    virtual void przyjmijZdobycz
                                (Mieszkaniec * mieszkaniec);
};
class Grzyb: protected Organizm, public Mieszkaniec {
public:
    Grzyb();
    virtual RodzajMieszkanca  kimJestes() final;
    virtual ZamiarMieszkanca
                    wybierzAkcje(Sasiedztwo sasiedztwo);
    virtual Mieszkaniec * dajPotomka();
    virtual void przyjmijZdobycz
                                (Mieszkaniec * mieszkaniec);
};

class Bakteria: protected Organizm, public Mieszkaniec {
public:
    Bakteria();
    virtual RodzajMieszkanca  kimJestes() final;
    virtual ZamiarMieszkanca
                    wybierzAkcje(Sasiedztwo sasiedztwo);
    virtual Mieszkaniec * dajPotomka();
    virtual void przyjmijZdobycz
                                (Mieszkaniec * mieszkaniec);
};


#endif //GRA_OSOBNIKI_H
