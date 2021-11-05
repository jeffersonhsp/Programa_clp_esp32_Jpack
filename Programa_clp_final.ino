#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include <EEPROM.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include "html_page.h"

int currentmillis;                      //variavel para guardar o valor atual de millis

int currentmillis_foto;                 //variavel para guardar o valor atual de millis
int atraso_foto = 100;                  //atraso para fotocelula de 100ms para corrigir o ajuste mecanico da maquina
int atraso_rele = 0;                  //atraso para fotocelula de 100ms para corrigir o ajuste mecanico da maquina
const char *ssid = "JPACK";             //ssid do server AP
const char *password = "10203040";      //password do server AP


uint8_t i;                              //variavel auxiliar do laço de repetiçao

uint16_t counter = 0;  //variavel auxiliar para o ciclo na interrupçao correspondente a confecçao de um pacote de 1...1000
uint16_t vet[80];                       //vetor que armazena os e manipula os dados da maquina.

bool flag_estado = false;               //flag que guarda o estado de funcionamento da maquina ligada ou desligada no loop principal
bool flag_estado_ciclo = false;         //flag que guarda o estado de funcionamento da maquina ligada ou desligada no loop da interrupçao
bool flag_pedido = false;               //flag setada se a maquina pedir produto a balança
bool flag_espera_pdt = false;           //flag setada apos a pedida de produto para a balança para armazenar o estado de espera
bool pressed = false;                   //flag setada para guardar o estado atual do botao fisico LIGA_DESLIGA "flip flop"
bool flag_p_aquecimento = false;        //flag setada para guardar o estado de pre aquecimento da solda vertical
bool flag_foto_millis = false;          //flag setada para auxiliar no atraso da fotocelula sem precisar de "dalay"

bool flag_emergencia = false;           //flag da emergencia
bool flag_falha_datador = false;        //flag do erro do datador
bool flag_falha_bobinap = false;        //flag do erro de bobina presa
bool flag_falha_bobinaf = false;        //flag do erro de bobina frouxa
bool flag_falha_inversor = false;       //flag da falha dos inversores ligados em serie 
bool flag_falha_foto = false;           //flag de falha caso nao detecte a targeta da fotocelula no filme
bool foto_ciclo = false;


String alarme = "";                     //string auxiliar que armazena o nome do alarme para envio do Json para a IHM

WebServer server(80);                   //seta o webserver na porta padra0 :80

WebSocketsServer websockets(81);        //seta a conexao do websocket na porta :81 

TaskHandle_t Task1;                     //cria  3 tasks para envio do json para a ihm, para corrigir um erro
TaskHandle_t Task2;                     //que se mais de um usuario se conectasse a fechasse o navegador todos os usuarias conectador perdiam pacotes
TaskHandle_t Task3;

#define EEPROM_SIZE 100                 //define o tamanho da EEPROM simulada, para gardar os dados oparacionais da maquina


// do 0 ao 19 na eeprom valores dos tempos em uint16_t
#define velocidade            vet[0] 

#define tracionador_liga      vet[1]  
#define tracionador_tempo     vet[2]  
#define shorizontal_liga      vet[3]  
#define shorizontal_tempo     vet[4]
#define svertical_liga        vet[5]  
#define svertical_tempo       vet[6]
#define t_queda               vet[7]  
#define balanca_tempo         vet[8]
#define temperaturav_liga     vet[9]  
#define temperaturav_tempo    vet[10]
#define faca_liga             vet[11] 
#define faca_tempo            vet[12]
#define datador_liga          vet[13] 
#define datador_tempo         vet[14]
#define resfriamento_liga     vet[15] 
#define resfriamento_tempo    vet[16]
#define pre_aquecimento       vet[17]



// do 20 ao 39 flags de habilitacoes
#define hab_soldah            vet[20]
#define hab_soldav            vet[21]
#define hab_faca              vet[22]
#define hab_resfriamento      vet[23]
#define hab_datador           vet[24]   
#define hab_temperaturav      vet[25]
#define hab_temperaturah      vet[26]   
#define hab_tracionador       vet[27] 
#define hab_balanca           vet[28]   
#define hab_desbobinador      vet[29]
#define hab_calha             vet[30]  
#define hab_foto              vet[31] 


#define out_shorizontal     15  //1
#define out_svertical       2   //2
#define out_faca            4   //3
#define out_resfriamento    16  //4
#define out_datador         17  //5
#define out_temperaturav    5   //6
#define out_temperaturah    18  //7
#define out_tracionador     19  //8
#define out_balanca         23  //9
#define out_desbobinador    13  //10
#define out_calha           12  //11 correias

#define in_liga_desbobinador        14  //1
#define in_desliga_desbobinador     27  //2
#define in_fotocelula               26  //3
#define in_on_off                   25  //4
#define in_descarga                 33  //5
#define in_emergencia               32  //6
#define in_datador                  35  //7
#define in_bobinap                  34  //8
#define in_bobinaf                  39  //9
#define in_inversores               36  //10


uint16_t tracionador_off;
uint16_t shorizontal_off;
uint16_t svertical_off;
uint16_t balanca_off;
uint16_t temperaturav_off;
uint16_t faca_off;
uint16_t datador_off;
uint16_t resfriamento_off;
uint16_t balanca_liga;


//  Configura interrupçao e timer 0 
unsigned int timer_scaller = 0;
unsigned int tmr = 0;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Inicio da interrupçao
void cb_timer(){
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ - TRATAMENTO DO CICLO - @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       
     

     if(counter == tracionador_liga && hab_tracionador && !flag_espera_pdt){digitalWrite(out_tracionador,true); tracionador_off = (tracionador_tempo * velocidade / 60);}
     if(tracionador_off <= 0){digitalWrite(out_tracionador,false);} tracionador_off--;                                                                //decrementa o tempo e desliga a saida quando zerar o tempo
     if(tracionador_off == 1 && hab_foto && flag_estado_ciclo)flag_falha_foto = true;
     
     if(counter == shorizontal_liga && hab_soldah && !flag_espera_pdt){digitalWrite(out_shorizontal,true); shorizontal_off = (shorizontal_tempo * velocidade / 60);}
     if(shorizontal_off <= 0){digitalWrite(out_shorizontal,false);} shorizontal_off--;                                                                //decrementa o tempo e desliga a saida quando zerar o tempo
     
     if(counter == svertical_liga && hab_soldav && !flag_espera_pdt){digitalWrite(out_svertical,true); svertical_off = (svertical_tempo * velocidade / 60);}
     if(svertical_off <= 0){digitalWrite(out_svertical,false);} svertical_off--;                                                                      //decrementa o tempo e desliga a saida quando zerar o tempo




     if(counter == balanca_liga && hab_balanca){digitalWrite(out_balanca,true); balanca_off = (balanca_tempo * velocidade / 60);  }  //Aciona saida de pedido do produto e calcula tempo acionado
     if(balanca_off <= 0){digitalWrite(out_balanca,false);} balanca_off--;                                      //decrementa o tempo e desliga a saida quando zerar o tempo
     
     
     if(counter == (balanca_liga + atraso_rele) && hab_balanca )flag_espera_pdt = true;                                                    //se o "ciclo = tempo da balança" com o "atraso do rele" seta a flag para desabilitar outros acionamentos
     if(!digitalRead(in_descarga) && flag_espera_pdt){flag_espera_pdt = false;  counter = balanca_liga + atraso_rele;    atraso_rele = counter - balanca_liga; }        //se a balança respondeu seta flag e calcula o atraso do relé
     if(!hab_balanca && flag_espera_pdt){flag_espera_pdt = false; counter = (balanca_liga + atraso_rele); }                       //se foi desabilitado a balança pelo usuario retoma o funcionamento sem produto mesmo



     if(counter == faca_liga && hab_faca && !flag_espera_pdt){digitalWrite(out_faca,true); faca_off = (faca_tempo * velocidade / 60);}
     if(faca_off <= 0){digitalWrite(out_faca,false);} faca_off--;                                                                                          //decrementa o tempo e desliga a saida quando zerar o tempo
     
     if(counter == datador_liga && hab_datador && !flag_espera_pdt){digitalWrite(out_datador,true); datador_off = (datador_tempo * velocidade / 60);}
     if(datador_off <= 0){digitalWrite(out_datador,false);} datador_off--;                                                                                 //decrementa o tempo e desliga a saida quando zerar o tempo
     
     if(counter == resfriamento_liga && hab_resfriamento){
      digitalWrite(out_resfriamento,true); resfriamento_off = (resfriamento_tempo * velocidade / 60);
      if(flag_espera_pdt)resfriamento_off += 300;                                                                                                          // se a maquina esta aguardando a balança aumenta o tempo do resfriamento para nao queimar a fita vertical.                                                
     }
     if(resfriamento_off <= 0){digitalWrite(out_resfriamento,false);} resfriamento_off--;//decrementa o tempo e desliga a saida quando zerar o tempo

     if(counter == temperaturav_liga && hab_temperaturav){digitalWrite(out_temperaturav,true); temperaturav_off = (temperaturav_tempo * velocidade / 60);}
     if(temperaturav_off <= 0 && flag_p_aquecimento){digitalWrite(out_temperaturav,false);} temperaturav_off--;                                            //decrementa o tempo e desliga a saida quando zerar o tempo


        
     if(hab_desbobinador  && !digitalRead(in_liga_desbobinador))digitalWrite(out_desbobinador,true); 
     if(!hab_desbobinador  || !digitalRead(in_desliga_desbobinador))digitalWrite(out_desbobinador,false); 
          
     if(hab_calha && !flag_emergencia)digitalWrite(out_calha,true);
       else digitalWrite(out_calha,false);
     if(hab_temperaturah && !flag_emergencia)digitalWrite(out_temperaturah,true); 
       else digitalWrite(out_temperaturah,false);
          
     if(!digitalRead(in_fotocelula) && !flag_foto_millis && hab_foto)foto_ciclo = true; 
          
          
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@          
          
          if(counter == faca_liga && !flag_estado_ciclo)counter = 0;          //  Pausa os ciclos           
                    
          if(flag_estado_ciclo && counter == 0){counter = faca_liga; }        //  Retoma os ciclos
          
          if(counter >= 1 && counter <= 1000)counter++;                       //  Incrementa a variavel dos ciclos
          
          if(counter > 1000){counter = 1; }                                   //  Reinicializa o proximo ciclo 
          

} 
// FIM  da interrupçao
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void envia(int z){

// Define qual foi o alarme e adiciona no Json o alarme correspondente para IHM
alarme = "";
if(flag_emergencia)alarme += "Emergencia !!!<br>";
if(flag_falha_datador)alarme += "Erro no datador !<br>";
if(flag_falha_bobinap)alarme += "Bobina presa !<br>";
if(flag_falha_bobinaf)alarme += "Fim de filme !<br>";
if(flag_falha_inversor)alarme += "Inversores com falha !<br>";
if(flag_falha_foto)alarme += "Falha na Fotocélula !<br>";

// Monta a estrutura do Json para atualizar o status da ihm   
String JSON_Data = 
            + "{\"velocidade\":"+String(velocidade)
            + ",\"hab_balanca\":"+String(hab_balanca)
            + ",\"hab_tracionador\":"+String(hab_tracionador)
            + ",\"hab_soldah\":"+String(hab_soldah)
            + ",\"hab_soldav\":"+String(hab_soldav)
            + ",\"hab_temperaturav\":"+String(hab_temperaturav)
            + ",\"hab_resfriamento\":"+String(hab_resfriamento)
            + ",\"hab_faca\":"+String(hab_faca)
            + ",\"hab_datador\":"+String(hab_datador)
            + ",\"hab_desbobinador\":"+String(hab_desbobinador)
            + ",\"hab_calha\":"+String(hab_calha)
            + ",\"hab_temperaturah\":"+String(hab_temperaturah)
            + ",\"hab_foto\":"+String(hab_foto)
            + ",\"flag_estado\":"+String(flag_estado)
            + ",\"tracionador_liga\":"+String(tracionador_liga)
            + ",\"tracionador_tempo\":"+String(tracionador_tempo)
            + ",\"shorizontal_liga\":"+String(shorizontal_liga)
            + ",\"shorizontal_tempo\":"+String(shorizontal_tempo)
            + ",\"svertical_liga\":"+String(svertical_liga)
            + ",\"svertical_tempo\":"+String(svertical_tempo)
            + ",\"balanca_liga\":"+String(t_queda)
            + ",\"balanca_tempo\":"+String(balanca_tempo)
            + ",\"temperaturav_liga\":"+String(temperaturav_liga)
            + ",\"temperaturav_tempo\":"+String(temperaturav_tempo)
            + ",\"faca_liga\":"+String(faca_liga)
            + ",\"faca_tempo\":"+String(faca_tempo)
            + ",\"datador_liga\":"+String(datador_liga)
            + ",\"datador_tempo\":"+String(datador_tempo)
            + ",\"resfriamento_liga\":"+String(resfriamento_liga)
            + ",\"resfriamento_tempo\":"+String(resfriamento_tempo)
            + ",\"preaq_tempo\":"+String(pre_aquecimento)
            + ",\"atraso_rele\":"+String(atraso_rele)
            + ",\"counter\":"+ counter
            + ",\"alarme\":\""+ alarme
            + "\"}";
            //for(i=0;i<5;i++){websockets.sendTXT(i,JSON_Data);  delay(20);}
            //websockets.broadcastTXT(JSON_Data);
            
            websockets.sendTXT(z,JSON_Data);  //envia o Json via Websocket para o client "z"
            delay(50);
  }

// guarda o vetor na Eeprom
void write_eeprom_all() {
  for(i=0;i<20;i++){
    EEPROM.write(i*2,highByte(vet[i]));
    EEPROM.write(i*2+1,lowByte(vet[i]));
  }
  
  for(i=40;i<100;i++){
    EEPROM.write(i,vet[i-20]);
  }
  EEPROM.commit();
}

// Lê o vetor da Eeprom
void read_eeprom_all(){
  for(i=0;i<20;i++){
    vet[i] = word(EEPROM.read(i*2),EEPROM.read(i*2+1));
  }

  for(i=40;i<100;i++){
    vet[i-20] = EEPROM.read(i);
  }
}


//inicia o timer 0 e seta interrupçao por timer 
void startTimer(){
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &cb_timer, true);
    timerAlarmWrite(timer, timer_scaller, true); 
    timerAlarmEnable(timer);
}

// Para o timer 0
void stopTimer(){
    timerEnd(timer);
    timer = NULL; 
}


// para o funcionamento da maquina caso haja algum erro ou precise de uma parada brusca como a emergencia acionada
void parageral(){
  
    counter = 0; 
    flag_pedido = false; 
    flag_espera_pdt = false;
    flag_estado = false;
    
    tracionador_off = 0;
    shorizontal_off = 0;
    svertical_off = 0;
    balanca_off = 0;
    temperaturav_off = 0;
    faca_off = 0;
    datador_off = 0;
    resfriamento_off = 0;

    digitalWrite(out_desbobinador,false);  

}



// Funçao chamada quando é recebito um pacote do cliente Websocket.
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) 
  {
    case WStype_DISCONNECTED:{
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    } 
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: | %s | \n", num, ip[0], ip[1], ip[2], ip[3], payload);
        websockets.sendTXT(num, "Connected from server");
        break;break;
      }
      
      
    case WStype_TEXT: {
      DynamicJsonDocument doc(200);
      DeserializationError error = deserializeJson(doc, payload);
      if(error){
         Serial.print("deserializeJson() failed: ");
         Serial.println(error.c_str());
      return;}
         
      String aux ="";
      if(doc["velocidade"].as<long>() >= 20 && doc["velocidade"].as<long>() <= 150){  //confere se foi recebido a velocidade no Json
        velocidade = doc["velocidade"].as<long>();                                    //Atualiza a velocidade na variavel
        timer_scaller = 60000 / velocidade;                                           //atualiza a velocidade no timer
        timerAlarmWrite(timer, timer_scaller, true);                                  //reinicia o timer atualizado
      }

      aux = doc["flag_estado"].as<const char*>();
      //if(aux == "on" && !flag_emergencia && !flag_falha_datador && !flag_falha_bobinap && !flag_falha_bobinaf && !flag_falha_inversor){digitalWrite(out_temperaturav,true);currentmillis=millis();flag_p_aquecimento = false; } 
      //if(aux == "off")flag_estado = false;
      if(aux =="on" || aux == "off"){
          flag_estado = !flag_estado; 
          if(flag_estado){digitalWrite(out_temperaturav,true);currentmillis=millis();flag_p_aquecimento = false;}
       }

      aux = doc["hab_balanca"].as<const char*>();if(aux == "on") hab_balanca = 1; if(aux == "off")hab_balanca = 0;
      aux = doc["hab_foto"].as<const char*>();if(aux == "on") hab_foto = 1; if(aux == "off")hab_foto = 0;
      aux = doc["hab_tracionador"].as<const char*>();if(aux == "on") hab_tracionador = 1; if(aux == "off")hab_tracionador = 0;
      aux = doc["hab_soldah"].as<const char*>();if(aux == "on") hab_soldah = 1; if(aux == "off")hab_soldah = 0;
      aux = doc["hab_faca"].as<const char*>();if(aux == "on") hab_faca = 1; if(aux == "off")hab_faca = 0;
      aux = doc["hab_soldav"].as<const char*>();if(aux == "on") hab_soldav = 1; if(aux == "off")hab_soldav = 0;
      aux = doc["hab_datador"].as<const char*>();if(aux == "on") hab_datador = 1; if(aux == "off")hab_datador = 0;
      aux = doc["hab_temperaturav"].as<const char*>();if(aux == "on") hab_temperaturav = 1; if(aux == "off")hab_temperaturav = 0;
      aux = doc["hab_desbobinador"].as<const char*>();if(aux == "on") hab_desbobinador = 1; if(aux == "off")hab_desbobinador = 0;
      aux = doc["hab_resfriamento"].as<const char*>();if(aux == "on") hab_resfriamento = 1; if(aux == "off")hab_resfriamento = 0;
      aux = doc["hab_calha"].as<const char*>();if(aux == "on") hab_calha = 1; if(aux == "off")hab_calha = 0;
      aux = doc["hab_temperaturah"].as<const char*>();if(aux == "on") hab_temperaturah = 1; if(aux == "off")hab_temperaturah = 0;
      
      aux = doc["reset"].as<const char*>();if(aux == "on"){flag_emergencia=false;flag_falha_datador=false;flag_falha_bobinaf=false;flag_falha_bobinap=false;flag_falha_inversor=false; flag_falha_foto=false; alarme = "";}

      if(doc["tracionador_liga"].as<long>()){tracionador_liga = doc["tracionador_liga"].as<long>();}
      if(doc["tracionador_tempo"].as<long>()){tracionador_tempo = doc["tracionador_tempo"].as<long>();}
      if(doc["shorizontal_liga"].as<long>()){shorizontal_liga = doc["shorizontal_liga"].as<long>();} 
      if(doc["shorizontal_tempo"].as<long>()){shorizontal_tempo = doc["shorizontal_tempo"].as<long>();}
      if(doc["svertical_liga"].as<long>()){svertical_liga = doc["svertical_liga"].as<long>();}            
      if(doc["svertical_tempo"].as<long>()){svertical_tempo = doc["svertical_tempo"].as<long>();}
      if(doc["balanca_liga"].as<long>()){t_queda = doc["balanca_liga"].as<long>();}
      if(doc["balanca_tempo"].as<long>()){balanca_tempo = doc["balanca_tempo"].as<long>();}
      if(doc["temperaturav_liga"].as<long>()){temperaturav_liga = doc["temperaturav_liga"].as<long>();}
      if(doc["temperaturav_tempo"].as<long>()){temperaturav_tempo = doc["temperaturav_tempo"].as<long>();}
      if(doc["faca_liga"].as<long>()){faca_liga = doc["faca_liga"].as<long>();}
      if(doc["faca_tempo"].as<long>()){faca_tempo = doc["faca_tempo"].as<long>();}
      if(doc["datador_liga"].as<long>()){datador_liga = doc["datador_liga"].as<long>();}
      if(doc["datador_tempo"].as<long>()){datador_tempo = doc["datador_tempo"].as<long>();}
      if(doc["resfriamento_liga"].as<long>()){resfriamento_liga = doc["resfriamento_liga"].as<long>();}
      if(doc["resfriamento_tempo"].as<long>()){resfriamento_tempo = doc["resfriamento_tempo"].as<long>();}

      if(doc["preaq_tempo"].as<long>()){pre_aquecimento = doc["preaq_tempo"].as<long>();}
 
      stopTimer(); write_eeprom_all(); startTimer();        // salva tudo na eeprom parando o timer para nao haver conflito na gravaçao
      balanca_liga = 1000 - (t_queda * velocidade / 60);    // atualiza  o tempo de queda

    }
  }
}


void setup(void) {
  
  Serial.begin(9600);Serial.println("Serial iniciada");

  //configura as saidas
  pinMode(out_shorizontal,OUTPUT);pinMode(out_svertical,OUTPUT);pinMode(out_faca,OUTPUT);pinMode(out_resfriamento,OUTPUT);
  pinMode(out_datador,OUTPUT);pinMode(out_temperaturav,OUTPUT);pinMode(out_temperaturah,OUTPUT);pinMode(out_tracionador,OUTPUT);
  pinMode(out_balanca,OUTPUT);pinMode(out_desbobinador,OUTPUT);pinMode(out_calha,OUTPUT);
  //configura as entradas
  pinMode(in_liga_desbobinador,INPUT);pinMode(in_desliga_desbobinador,INPUT);pinMode(in_fotocelula,INPUT);pinMode(in_on_off,INPUT);
  pinMode(in_descarga,INPUT);pinMode(in_emergencia,INPUT);pinMode(in_datador,INPUT);pinMode(in_bobinap,INPUT);
  pinMode(in_bobinaf,INPUT);pinMode(in_inversores,INPUT);

  //desliga todas as saidas
  digitalWrite(out_shorizontal,false);digitalWrite(out_svertical,false);digitalWrite(out_faca,false);digitalWrite(out_resfriamento,false);
  digitalWrite(out_datador,false);digitalWrite(out_temperaturav,false);digitalWrite(out_temperaturah,false);digitalWrite(out_tracionador,false);
  digitalWrite(out_balanca,false);digitalWrite(out_desbobinador,false);digitalWrite(out_calha,false);

  EEPROM.begin(EEPROM_SIZE);                      // initialize EEPROM com o valor predefinido
  read_eeprom_all();                              //  CAPTURA TUDO NA EEPROM

  WiFi.mode(WIFI_AP);                             //  Configura Wifi no modo AP
  WiFi.softAP(ssid, password);                    //  Configura SSID e SENHA do modo AP.


  server.on("/", HTTP_GET, []() {                 //envia para o cliente a pagina completa caso solicitado na porta 80
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", html_page);
  });
  
  server.on("/ota", HTTP_GET, []() {              //envia para o cliente a pagina de atualizaçao caso solicitado /ota na porta 80
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", html_ota);
    stopTimer();
    parageral();
  });

  websockets.onEvent(webSocketEvent);             // funçao chamada quando receber um dado no websocket ("webSocketEvent()")

  /*handling uploading firmware file   OTA  */
  server.on("/update", HTTP_POST, []() {          //caso recebido um post com o arquivo.bin da inicio a atualizaçao do programa via OTA
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
         server.sendHeader("Connection", "close");
         server.send(200, "text/html", html_pos_ota);
         delay(500);
         ESP.restart();
      } else {
        Update.printError(Serial);
      }
    }
  });
  ////////////////////////////////////////////////////////////
  
  websockets.begin();                     // inicia o Websocket
  server.begin();                         // inicia o webserver


if(velocidade == 0 )velocidade = 1;                     //  Define a velocidade igual a 1 caso seja 0, para nao dar confito no timer da interrupçao
  balanca_liga = 1000 - (t_queda * velocidade / 60);    // atualiza  o tempo de queda
  timer_scaller = 60000 / velocidade;                   //  Atualiza o timer                           
  flag_estado = false;                                  //  INICIA MAQUINA DESLIGADA
  startTimer();                                         //  Inicia o timer
  shorizontal_liga = 1;                                 //  Define como padrao a solda orizontal igual a 1 "valor fixo nao pode ser alterado por pelo usuario"
  counter = 0;                                          //  inicia variavel zerada
  flag_emergencia = false;                              //  inicia variavel zerada
  atraso_rele = 30;
  alarme = "";                                          //  inicia variavel zerada
  

  //cria as 3 tasks para o envio dos dados para os clients Websockets no Core 0.
  xTaskCreatePinnedToCore(
                    Task1code,   
                    "Task1",     
                    10000,       
                    NULL,        
                    1,           
                    &Task1,      
                    0);                          
  delay(500); 
    xTaskCreatePinnedToCore(
                    Task2code,   
                    "Task2",     
                    10000,       
                    NULL,        
                    1,           
                    &Task2,      
                    0);             
  delay(500);
    xTaskCreatePinnedToCore(
                    Task3code,   
                    "Task3",     
                    10000,       
                    NULL,       
                    1,           
                    &Task3,      
                    0);                           
  delay(500);
}
  

void loop(void) {
  server.handleClient();
  websockets.loop();



  if(digitalRead(in_emergencia))flag_emergencia = true;
  if(!digitalRead(in_datador))flag_falha_datador = true;
  if(!digitalRead(in_bobinap))flag_falha_bobinap = true;
  if(!digitalRead(in_bobinaf))flag_falha_bobinaf = true;
  if(!digitalRead(in_inversores))flag_falha_inversor = true;

  
  if(flag_emergencia || flag_falha_datador || flag_falha_bobinap || flag_falha_bobinaf || flag_falha_inversor || flag_falha_foto)parageral();

  if(millis() % 50 == 0 && !flag_emergencia && !flag_falha_datador && !flag_falha_bobinap && !flag_falha_bobinaf && !flag_falha_inversor){
    if(digitalRead(in_on_off) && pressed)pressed = false;              //se botao for solto zera a flag do botao pressionado
    if(!digitalRead(in_on_off) && !pressed){
        pressed = true;
        flag_estado = !flag_estado; 
        if(flag_estado){digitalWrite(out_temperaturav,true);currentmillis=millis();flag_p_aquecimento = false;}
    }
  }
  if(flag_estado && millis() > (currentmillis + pre_aquecimento)){    // se ja acabou o tempo do pre aquecimento
    if(!flag_p_aquecimento)digitalWrite(out_temperaturav,false);      // desliga o aquecimento da vertical
    flag_estado_ciclo = true;                                         // inicia o ciclo de funcionamento
    flag_p_aquecimento = true;                                        // seta a flag de pre aquecimento concluido
  }
  if(!flag_estado){
    flag_estado_ciclo = false;
    flag_p_aquecimento = false;
    digitalWrite(out_temperaturav,false);
  }
  
     
  
  if(foto_ciclo){ currentmillis_foto = millis();  flag_foto_millis = true; foto_ciclo = false; }
  if(millis() >= (currentmillis_foto + atraso_foto) && flag_foto_millis){digitalWrite(out_tracionador,false); tracionador_off = 0; flag_foto_millis = false;}


}



void Task1code( void * parameter) {
  for(;;) {
    envia(0);
  }
}
void Task2code( void * parameter) {
  for(;;) {
    envia(1);
  }
}
void Task3code( void * parameter) {
  for(;;) {
    envia(2);
  }
}
