// master.ino

#include <Wire.h>

#define COST_CONS 3
#define COST_CAMI 3
#define COST_M1 2
#define COST_M2 5
#define COST_M3 8

#define REC_LIM 8

#define AC_CAS 1
#define AC_REC 2
#define AC_CAM 3
#define AC_ATA 4


struct cliente{

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

int turno = 1;
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


void setup() {
	
	cliente1 = initCliente(cliente1,"Cliente1");
	cliente2 = initCliente(cliente2,"Cliente2");
	Serial.begin(9600);
        Wire.begin();

}

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

void decodificar(

void loop() {
        
    //comunicacion
    const int address1 = 1;
    const int address2 = 2;
    char status1[9];
    char status2[9];  
    
    
    int jugada1 = recibeJugada(address1);
    int jugada2 = recibeJugada(address2);

    imprimirResumenTurno();      
    //Serial.println(receivedValue);
  

    gestion_turno_2j(&cliente1,1,1, &cliente2,2,3);
    crearstatus(cliente1, status1);
    crearstatus(cliente2, status2);
 
    Serial.println(status1);
    Serial.println(status2);
    
    enviarStatus(address1, status1);
    enviarStatus(address2, status2);  
  
  
  
/*  
        Serial.println("Inicio del Juego, situacion Inicial");   
        imprimirResumenTurno();         

        Serial.println("Cliente 1 Accion:1-1 construye casa // Cliente 2 Accion:2-3  mejora marmol");         
        gestion_turno_2j(&cliente1,1,1, &cliente2,2,3);
        imprimirResumenTurno();        
        turno++;              
                     

        Serial.println("Cliente 1 Accion:1-1 construye casa // Cliente 2 Accion:3-1 entrena camion");                    
        gestion_turno_2j(&cliente1,1,1, &cliente2,3,1);
        imprimirResumenTurno();        
        turno++; 
        

        Serial.println("Cliente 1 Accion:1-1 construye casa // Cliente 2 Accion:3-1 entrena camion");             
        gestion_turno_2j(&cliente1,1,1, &cliente2,3,1);
        imprimirResumenTurno();        
        turno++;  
        

        Serial.println("Cliente 1 Accion:1-1 construye casa // Cliente 2 Accion:3-1 entrena camion");          
        gestion_turno_2j(&cliente1,1,1, &cliente2,3,1);
        imprimirResumenTurno();        
        turno++;   
        

        Serial.println("Cliente 1 Accion:1-1 construye casa  // Cliente 2 Accion:4-1 ataca a 1");            
        gestion_turno_2j(&cliente1,1,1, &cliente2,4,1);
        imprimirResumenTurno();        
        turno++;   
  
*/        
        delay(20000);
        
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
struct cliente construir(int ncasas, struct cliente c){
	
	if(c.tomates>=ncasas*COST_CONS && c.lechugas>=ncasas*COST_CONS){
		c.tomates = c.tomates-ncasas*COST_CONS;
		c.lechugas = c.lechugas-ncasas*COST_CONS;
		c.casas = c.casas + ncasas;
	}
        return c;
}

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

struct cliente construirCamion(int ncamiones, struct cliente c){
	if(c.marmol>=ncamiones*COST_CAMI){
		c.marmol = c.marmol-ncamiones*COST_CAMI;
		c.camiones = c.camiones + ncamiones;
	}
  return c;
}

struct cliente recursos(struct cliente c){
    c.tomates+=c.aTomates;
    c.lechugas+=c.aLechugas;
    c.marmol+=c.aMarmol;
return c;
}

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
    return c;
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

struct cliente moverCamiones(struct cliente c){
  c.cMovimiento=c.camiones;
  c.camiones=0;
  return c;

}

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
        Serial.println("saliendo");
            break;
      }
    } 
    } 
}



void enviarStatus(int address, char status[])
/* Envia el status del jugador de direccion address a ese jugador 
  El estatus sera un codigo de 8 digitos
  El primero sera el numero de tomates 
  El segundo el nivel de los tomates
  El tercero el numero de lechugas
  El cuarto el nivel de lechugas
  el quito el numero de marmol
  el sexto el nivel de marmol
  el septimo el numero de camiones
  y el octavo el numero de casas*/
{
  Wire.beginTransmission(address); 
  Wire.write('i');
  delay(10);
  Wire.write(status[0]);
  delay(10);
  Wire.write(status[1]);
  delay(10);
  Wire.write(status[2]);
  delay(10);
  Wire.write(status[3]);
  delay(10);
  Wire.write(status[4]);
  delay(10);
  Wire.write(status[5]);
  delay(10);
  Wire.write(status[6]);
  delay(10);
  Wire.write(status[7]);
  delay(10);
  Wire.endTransmission();
 
}


int recibeJugada(int direccion)
/* El Master manda al esclavo con direccion "direccion"  la peticion de la 
  jugada que va a realizar y retorna el codigo de jugada enviada 
  los codigos de jugada son numeros de tres digitos, 
  el primero es la direccion del jugador
  el segundo es la accion a realizar
  y el tercero es el destinatario */
{
  int receivedValue;
  // Request data from slave.
  Wire.beginTransmission(direccion);
  
  // Envia al cliente de direccion 4 la peticion y se queda a la espera de 
  // recibir un byte
  int available = Wire.requestFrom(direccion, 4); 
 
   if(available == 4)
    {
      receivedValue = Wire.read() << 8 | Wire.read();
    }
    else
    {
      Serial.print("Unexpected number of bytes received: ");
      Serial.println(available);
    }
    Wire.endTransmission();
    return receivedValue;
   
}

char numeroAletra(int num){
  char b[2];
  String str;
  str=String(num);
  str.toCharArray(b,2);  
  return str.charAt(0);
}

int letraAnumero(char letra){
   return letra - '0'; 
}



