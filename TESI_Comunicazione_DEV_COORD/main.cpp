#include "mbed.h"
//#define DEVICE
#define COORDINATOR


Serial pc(USBTX, USBRX);
RawSerial uart(PB_6,PB_7,9600);


/*void onMsgReceived()
{
   rcv_msg = uart.getc();
}*/

int main()
{
    //uart.attach(&onMsgRecived);
    #ifdef DEVICE
    int auth_response = 0x0F;
    int auth_challenge;
    int coordinator_reply;
    int number_of_node;
    int auth_request_msg = 0;
    int selfID = 8;
    
    pc.printf("SONO IL DEVICE!!!\n\r");
    
    //requesting authentication & sending self ID
    uart.putc(auth_request_msg);
    uart.putc(selfID);
    
    
    
    
        pc.printf("Inviati authorization request e selfID al coordinator...\n\r");
        wait(0.1);
        auth_challenge = uart.getc();
        pc.printf("Ho ricevuto la challenge %d\n\r",auth_challenge);
        //TODO: generare la risposta sulla base di auth_challenge
        uart.putc(auth_response);
        pc.printf("Ho inviato la risposta al coordinator...\n\r");
        coordinator_reply = uart.getc();
        if(coordinator_reply == 1){
            pc.printf("Authorization granted...\n\r");
            number_of_node = uart.getc();
            int i;
            int node_address[number_of_node];
            for(i = 0; i < number_of_node; i++)
                node_address[i] = uart.getc();
            pc.printf("Ho ricevuto i seguenti dati:\n\r");
            pc.printf("Numero di nodi connessi: %d\n\r",number_of_node);    
            for(i = 0; i < number_of_node; i++)
                pc.printf("Indirizzo nodo %d: %d",i+1,node_address[i]);
        }
        else
            pc.printf("Authorization denied...\n\r");
        
    
    
    #endif
    
    #ifdef COORDINATOR
    int deviceID;
    int stored_response = 0x0F;
    int auth_rcv;
    int challenge_response,reply;
    int challenge = 5;
    int node_number = 3;
    int addresses[node_number];
    int j;
    for(j = 0; j < node_number; j++)
        addresses[j] = j+1; 
    
    
    //uart.attach(&onMsgReceived);    
    //while(1) {
        
    pc.printf("SONO IL COORDINATOR!!!\n\r");    
        auth_rcv = uart.getc();
        deviceID = uart.getc();
        pc.printf("Richiesta di autorizzazione da parte del node %d...\n\r",deviceID);
        //TODO: Cerca in un database le info sulla challenge
        uart.putc(challenge);
        pc.printf("Inviata la challenge %d\n\r",challenge);
        challenge_response = uart.getc();
        pc.printf("Ho ricevuto la risposta alla challenge\n\rInvio reply\n\r");
        reply = (challenge_response == stored_response) ? 1 : -1;
        uart.putc(reply);
        if(reply==1){
            pc.printf("Invio dati nodi in corso...\n\r");
            uart.putc(node_number);
            int i;
            for(i = 0; i < node_number; i++)
                uart.putc(addresses[i]);
        }
            
        
                            
    //}
    
    #endif
   
   
}
