// master.ino

#include <Wire.h>
#include "comunicacion.h"

#define TURN_TIME 5000       //Tiempo de espera entre turnos

#define COST_CONS 3          //Coste de construir una casa
#define COST_CAMI 3          //Coste de construir un camion
#define COST_M1 2            //Coste de la mejora nivel 1
#define COST_M2 5            //Coste de la mejora nivel 2
#define COST_M3 8            //Coste de la mejora nivel 3

#define REC_LIM 8            //Limite de saturacion de recursos

#define AC_CAS 1             //Accion Construir una casa
#define AC_REC 2             //Codigo de accion de mejorar un recurso
#define AC_CAM 3             //Codigo de accion de constuir un Camion
#define AC_ATA 4             //Codigo de accion Atacar


struct cliente{              //Estructura cliente, status basico del cliente y 4 variables temporales para gestion de ataques.

        String nombre;
	int tomates;
	int aTomates;
	int lechugas;
	int aLechugas;
	int marmol;
	int aMarmol;
	int camiones;
	int casas;

        int cMovimiento;
        int tomRob;
        int lecRob;
        int marRob;
};

int turno = 0;              //Turno de la partida

    char status1[9];        //estado del jugador 1
    char status2[9];        //estado del jugador 2
    
    int jugada1=0;          //jugada que quiere realizar el jugador 1
    int jugada2=0;          //jugada que quiere realizar el jugador 2
    
    int jugador1;
    int jugador2;
    int accion1;
    int opcion1;
    int accion2;
    int opcion2;

struct cliente cliente1;
struct cliente cliente2;

struct cliente initCliente(struct cliente c,String nombre){
        c.nombre=nombre;
	c.tomates=2;
	c.lechugas=2;
	c.marmol=2;
	c.aTomates=1;
	c.aLechugas=1;
	c.aMarmol=1;
	c.camiones=0;
	c.casas=0;
        c.cMovimiento=0;
        c.tomRob=0;
        c.lecRob=0;
        c.marRob=0;
	return c;
}

// Inicia las comunicacioneslos y establece los valores por defecto de los clietes 
void setup() {
	
	cliente1 = initCliente(cliente1,"Cliente1");
	cliente2 = initCliente(cliente2,"Cliente2");
	Serial.begin(9600);
        Wire.begin();

}

// Rellena el array status con los datos del cliente
void crearstatus(struct cliente c1, char status[]) {
  
  status[0]=numeroAletra(c1.tomates);  
  status[1]=numeroAletra(c1.aTomates);  
  status[2]=numeroAletra(c1.lechugas);  
  status[3]=numeroAletra(c1.aLechugas);  
  status[4]=numeroAletra(c1.marmol);  
  status[5]=numeroAletra(c1.aMarmol);  
  status[6]=numeroAletra(c1.camiones);  
  status[7]=numeroAletra(c1.casas);
  status[8]='\0';

}

int initSincronizacion(){
   
// 2 jugadores

       enviarStatus(DIR_CLIENTE1,"START");
       delay(37); 
       enviarStatus(DIR_CLIENTE2,"START");
       delay(37);       
       enviarStatus(DIR_CLIENTE1,"START");
       delay(37); 
       enviarStatus(DIR_CLIENTE2,"START");
       delay(37);
         enviarStatus(DIR_CLIENTE1,"START");
       delay(37); 
       enviarStatus(DIR_CLIENTE2,"START");
       delay(37);
       
       
   while((jugada1!=166) && (jugada2!=266)) {
       enviarStatus(DIR_CLIENTE1,"START");
       delay(37); 
       enviarStatus(DIR_CLIENTE2,"START");
       delay(37);
       enviarStatus(DIR_CLIENTE1,"START");
       delay(37); 
       enviarStatus(DIR_CLIENTE2,"START");
       delay(37);
       enviarStatus(DIR_CLIENTE1,"START");
       delay(37); 
       enviarStatus(DIR_CLIENTE2,"START");
       delay(37);
           Serial.println(turno);
           Serial.println(" Enviado codigo: START y recibida señal: ");
           Serial.println(jugada1);
           Serial.println(jugada2);
       jugada1=recibeJugada(DIR_CLIENTE1);   
       delay(37);    
       jugada2=recibeJugada(DIR_CLIENTE2);
       delay(37); 
       if ((jugada1==100) && (jugada2==200))
       {
         return 0;
       }
   }
}

void loop() {
 
    if (turno==0){
      initSincronizacion();
    }
    
    turno++;     
    crearstatus(cliente1, status1);
    crearstatus(cliente2, status2);     
    enviarStatus(DIR_CLIENTE1, status1);
    enviarStatus(DIR_CLIENTE2, status2);
    Serial.println(status1);
    Serial.println(status2);    
   
    delay(TURN_TIME);  
    
    //Terminar Partida
        if((cliente1.casas==8) || (cliente2.casas==8)){
           if(cliente1.casas==8) {
             Serial.println(" Jugador 1 ha ganado"); 
           }
           if(cliente2.casas==8) {
             Serial.println(" Jugador 2 ha ganado"); 
           }
           exit(0);
        }     
    
    jugada1 = recibeJugada(DIR_CLIENTE1);
    jugada2 = recibeJugada(DIR_CLIENTE2); 
    decodificar(jugada1,&jugador1,&accion1,&opcion1);
    decodificar(jugada2,&jugador2,&accion2,&opcion2);
    Serial.println(jugada1);
    Serial.println(jugada2); 
    
    imprimirResumenTurno();        
    gestion_turno_2j(&cliente1,accion1,opcion1, &cliente2,accion2,opcion2);
          
}



void gestion_turno_2j(struct cliente *c1,int a1, int op1, struct cliente *c2,int a2,int op2){

  if (a1==AC_CAS) *c1 = construir(op1, *c1);
  if (a2==AC_CAS) *c2 = construir(op2, *c2);
  if (a1==AC_REC) *c1 = mejorar(op1, *c1);
  if (a2==AC_REC) *c2 = mejorar(op2, *c2);
  
  if (a1==AC_CAM) *c1 = construirCamion(op1, *c1);
  if (a2==AC_CAM) *c2 = construirCamion(op2, *c2);
  
  if (a1==AC_ATA && op1!=1) *c1=moverCamiones(*c1);
  if (a2==AC_ATA && op2!=2) *c2=moverCamiones(*c2);
   
  if (a1==AC_ATA) {
    if (op1!=1){
      if (op1==2){
        ataque(&*c1,&*c2);
      } 
    }
  }
  if (a2==AC_ATA) {
    if (op2!=2){
      if (op2==1){
        ataque(&*c2,&*c1);
      } 
    }
  }
  if (a1==AC_ATA && op1!=1)  *c1 = volverCamiones(*c1);
  if (a2==AC_ATA && op1!=2)  *c2 = volverCamiones(*c2); 
  
  *c1 = recursos(*c1);
  *c2 = recursos(*c2);  
  *c1 = liberarAlmacen(*c1);  
  *c2 = liberarAlmacen(*c2); 
  
}

///Cliente intenta construir un numero de casa
struct cliente construir(int ncasas, struct cliente c){
	
	if(c.tomates>=ncasas*COST_CONS && c.lechugas>=ncasas*COST_CONS){
		c.tomates = c.tomates-ncasas*COST_CONS;
		c.lechugas = c.lechugas-ncasas*COST_CONS;
		c.casas = c.casas + ncasas;
	}
        return c;
}

//Cliente intenta realizar una accion de mejora sobre las estructuras
struct cliente mejorar(int mejora,struct cliente c){

	if(mejora==1){
		switch (c.aTomates) {
		    case 1:
		    	if(c.tomates>=COST_M1 && c.lechugas>=COST_M1 && c.marmol>=COST_M1){
		    		c.aTomates++;
		    		c.tomates-=COST_M1;
		    		c.lechugas-=COST_M1;
		    		c.marmol-=COST_M1;
		    	}
		      break;
		    case 2:
		    	if(c.tomates>=COST_M2 && c.lechugas>=COST_M2 && c.marmol>=COST_M2){
		    		c.aTomates++;
		    		c.tomates-=COST_M2;
		    		c.lechugas-=COST_M2;
		    		c.marmol-=COST_M2;
		    	}
		      break;
		    case 3:
		    	if(c.tomates>=COST_M3 && c.lechugas>=COST_M3 && c.marmol>=COST_M3){
		    		c.aTomates++;
		    		c.tomates-=COST_M3;
		    		c.lechugas-=COST_M3;
		    		c.marmol-=COST_M3;
		    	}
		    	break;
		}
	}
	if(mejora==2){
		switch (c.aLechugas) {
		    case 1:
		    	if(c.tomates>=COST_M1 && c.lechugas>=COST_M1 && c.marmol>=COST_M1){
		    		c.aLechugas++;
		    		c.tomates-=COST_M1;
		    		c.lechugas-=COST_M1;
		    		c.marmol-=COST_M1;
		    	}
		      break;
		    case 2:
		    	if(c.tomates>=COST_M2 && c.lechugas>=COST_M2 && c.marmol>=COST_M2){
		    		c.aLechugas++;
		    		c.tomates-=COST_M2;
		    		c.lechugas-=COST_M2;
		    		c.marmol-=COST_M2;
		    	}
		      break;
		    case 3:
		    	if(c.tomates>=COST_M3 && c.lechugas>=COST_M3 && c.marmol>=COST_M3){
		    		c.aLechugas++;
		    		c.tomates-=COST_M3;
		    		c.lechugas-=COST_M3;
		    		c.marmol-=COST_M3;
		    	}
		    	break;
		}
	}
	if(mejora==3){
		switch (c.aMarmol) {
		    case 1:
		    	if(c.tomates>=COST_M1 && c.lechugas>=COST_M1 && c.marmol>=COST_M1){
		    		c.aMarmol++;
		    		c.tomates-=COST_M1;
		    		c.lechugas-=COST_M1;
		    		c.marmol-=COST_M1;
		    	}
		      break;
		    case 2:
		    	if(c.tomates>=5 && c.lechugas>=5 && c.marmol>=5){
		    		c.aMarmol++;
		    		c.tomates-=COST_M2;
		    		c.lechugas-=COST_M2;
		    		c.marmol-=COST_M2;
		    	}
		      break;
		    case 3:
		    	if(c.tomates>=COST_M3 && c.lechugas>=COST_M3 && c.marmol>=COST_M3){
		    		c.aMarmol++;
		    		c.tomates-=COST_M3;
		    		c.lechugas-=COST_M3;
		    		c.marmol-=COST_M3;
		    	}
		    	break;
		}
	}
  return c;
}

//Cliente intenta construir camiones
struct cliente construirCamion(int ncamiones, struct cliente c){
	if(c.marmol>=ncamiones*COST_CAMI){
		c.marmol = c.marmol-ncamiones*COST_CAMI;
		c.camiones = c.camiones + ncamiones;
	}
  return c;
}

//Aumento automatico de recursos segun el nivel de sus estructuras
struct cliente recursos(struct cliente c){
    c.tomates+=c.aTomates;
    c.lechugas+=c.aLechugas;
    c.marmol+=c.aMarmol;
return c;
}

//Eliminacion de los excedentes de recursos en almacenes
struct cliente liberarAlmacen(struct cliente c){
    if (c.tomates>REC_LIM){
          c.tomates=REC_LIM;
        }
    if (c.lechugas>REC_LIM){
          c.lechugas=REC_LIM;
        }
    if (c.marmol>REC_LIM){
          c.marmol=REC_LIM;
        }
    if (c.casas>REC_LIM){
          c.casas=REC_LIM;
        }
    if (c.camiones>REC_LIM){
          c.camiones=REC_LIM;
        }
    return c;
}




//Gestion pre-ataque de camiones
struct cliente moverCamiones(struct cliente c){
  c.cMovimiento=c.camiones;
  c.camiones=0;
  return c;

}

//Gestiona el post-ataque de camiones y recursos robados
struct cliente volverCamiones(struct cliente c){
  c.tomates+=c.tomRob;
  c.lechugas+=c.lecRob;
  c.marmol+=c.marRob;
  c.tomRob=0;
  c.lecRob=0;
  c.marRob=0;
  c.camiones=c.cMovimiento;
  c.cMovimiento=0;
  return c;
}

//Gestiona el ataque entre el Cliente Atacante ca y el cliente defenor cd. Y resuelve los robos si hubuese camiones restantes
void ataque(struct cliente *ca, struct cliente *cd){
    if (ca->cMovimiento >= cd->camiones){
      ca->cMovimiento-=cd->camiones;
      cd->camiones=0;
    }
    else{
    cd->camiones-=ca->cMovimiento;
    ca->cMovimiento=0;  
    }
    if (ca->cMovimiento>0){
      for (int i=ca->cMovimiento; i>0;){
        if(cd->tomates>0 && i>=1){
          cd->tomates--;
          ca->tomRob++;
          i--;
        }
        if(cd->lechugas>0 && i>=1){
          cd->lechugas--;
          ca->lecRob++;
          i--;
        }
        if(cd->marmol>0 && i>=1){
          cd->marmol--;
          ca->marRob++;
          i--;
        }
        if (cd->tomates==0 && cd->lechugas==0 && cd->marmol==0) {
        //  Serial.println("saliendo");
          break;
        }
      } 
    } 
}

void imprimirCliente(struct cliente c){  
        Serial.println("          T a L a M a C P   Cm Tr Lr Mr ");
        Serial.print(c.nombre);
        Serial.print(": ");
	Serial.print(c.tomates);
	Serial.print(" ");
	Serial.print(c.aTomates);
	Serial.print(" ");
	Serial.print(c.lechugas);
	Serial.print(" ");
	Serial.print(c.aLechugas);
	Serial.print(" ");
	Serial.print(c.marmol);
	Serial.print(" ");
	Serial.print(c.aMarmol);
	Serial.print(" ");
	Serial.print(c.camiones);
	Serial.print(" ");
	Serial.print(c.casas);
	Serial.print("   ");
	Serial.print(c.cMovimiento);
	Serial.print("  ");
	Serial.print(c.tomRob);
	Serial.print("  ");
	Serial.print(c.lecRob);
	Serial.print("  ");
	Serial.print(c.marRob);
	Serial.println(" ");
}

void imprimirResumenTurno(){
        Serial.println("");
        Serial.print("COMIENZA TURNO ");     
        Serial.println(turno);
        imprimirCliente(cliente1);
        imprimirCliente(cliente2);
        Serial.println(""); 

}


