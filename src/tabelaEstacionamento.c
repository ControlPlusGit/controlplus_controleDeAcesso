
#include <stdio.h>
#include <stdint.h>
#include "FLASH/flash.h"

#include "tabelaEstacionamento.h"
#include "log.h"

#define SIM 1
#define NAO 0

extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados;
extern TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberadosTest;

static __prog__ uint8_t memoriaFlash_Page1[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));

static __prog__ uint8_t memoriaFlash_Page2[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));

  
    void adicionarRegistroNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc){
        if( tabela->ponteiroTabela >= 0 && tabela->ponteiroTabela < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO ){
            tabela->epc[tabela->ponteiroTabela].tag = _epc.tag;
            tabela->ponteiroTabela++;
        }
    }
    
    void zeraPointeiroDaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela){
        if(tabela != 0){
            tabela->ponteiroTabela = 0;
        }
    }
    
    void removerTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela){  
        /*int i=0;
        for(i=0;i<NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_EXCLUSAO;i++){
            tabela.epc[i].tag = 0;
        }*/
        if(tabela != 0){
            tabela->epc[0].tag = 0;
            zeraPointeiroDaTabelaDeEpcDeEstacionamento(tabela);
        }
    }
    
    int buscarRegistroNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc){
        
        if(tabela != 0 && _epc.tag != 0){
            if(binarySearchNaTabelaDeEpcDeEstacionamento(tabela,0,tabela->ponteiroTabela, _epc.tag)){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }   
    
    int buscarRegistroNaTabelaDeEpcDeEstacionamentoDesordenada(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc){
        int i=0;
        
        if(tabela != 0 && _epc.tag != 0){            
            for(i = 0; i < tabela->ponteiroTabela; i++){
                if(tabela->epc[i].tag == _epc.tag)
                {
                    return 1;
                }
            }                    
        }
        else{
            return 0;
        }
        return 0;
    }
    
    int removerRegistroNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *tabela, EPC_Estacionamento _epc){
        int i=0,j=0;
        
        if(tabela != 0 && _epc.tag != 0){            
            for(i = 0; i < tabela->ponteiroTabela; i++){
                if(tabela->epc[i].tag == _epc.tag)
                {
                    tabela->epc[i].tag = 0;
                    for(j = i; j < tabela->ponteiroTabela-1; j++){
                        tabela->epc[j].tag = tabela->epc[j+1].tag;
                    }
                    tabela->ponteiroTabela--;
                }
            }                    
        }
        else{
            return 0;
        }
        return 0;
    }
    
    int binarySearchNaTabelaDeEpcDeEstacionamento(TabelaDeEpcDeEstacionamento *arr, int l, int r, long _epc){ 
        /* BUSCA COM RECURSIVIDADE E REENTRANCIA
        if (r >= l) { 
            int mid = l + (r - l) / 2; 
            if (arr.epc[mid].tag == _epc) 
                return mid;             
            if (arr.epc[mid].tag > _epc) 
                return binarySearchNaTabelaDeEPC(arr, l, mid - 1, _epc); 
            return binarySearchNaTabelaDeEPC(arr, mid + 1, r, _epc); 
        } 
        return 0; 
        */
        
        // BUSCA SEM RECURSIVIDADE E REENTRANCIA
        int primeiro = 0;
        int aux = r-1;
        int meio=0;
        char encontrei = NAO;
        int ultimo = (aux> 0)?(aux):(0);        
        
        while(primeiro <= ultimo && !encontrei){
            meio = (primeiro + ultimo) / 2;
            if(arr->epc[meio].tag == _epc){
                encontrei = SIM;
            }
            else{
                if(_epc < arr->epc[meio].tag){
                    ultimo = meio - 1;
                }
                else{
                    primeiro = meio + 1;
                }
            }
        }
        return encontrei;
    }
    
    int8_t obtemListaDeVeiculosLiberados(void){
    
        uint32_t flash_storage_address_page1;
        uint32_t flash_storage_address_page2;

        uint16_t i=0;

        EPC_Estacionamento readEPC;

        // Get flash page aligned address of flash reserved above for this test.
        flash_storage_address_page1 = FLASH_GetErasePageAddress((uint32_t)&memoriaFlash_Page1[0]);
        flash_storage_address_page2 = FLASH_GetErasePageAddress((uint32_t)&memoriaFlash_Page2[0]);

        // read the data to verify the data
        for( i = 0; i < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; i++ ){

            if( i < 512 ){
                readEPC.tag = FLASH_ReadWord16( flash_storage_address_page1 + i * 2U );
                adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, readEPC);
            }
            else{
                readEPC.tag = FLASH_ReadWord16( flash_storage_address_page2 + (i-512) * 2U );
                adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, readEPC );
            }        
        }    

        return 0;
    }

    int8_t gravarListaDeVeiculosLiberados(void){
    
        uint32_t flash_storage_address_page1;
        uint32_t flash_storage_address_page2;

        bool result;

        uint16_t i=0;

        // Get flash page aligned address of flash reserved above for this test.
        flash_storage_address_page1 = FLASH_GetErasePageAddress((uint32_t)&memoriaFlash_Page1[0]);
        flash_storage_address_page2 = FLASH_GetErasePageAddress((uint32_t)&memoriaFlash_Page2[0]);

        // Program Valid Key for NVM Commands
        FLASH_Unlock(FLASH_UNLOCK_KEY);

        // Erase the page of flash at this address
        result = FLASH_ErasePage(flash_storage_address_page1);
        result = FLASH_ErasePage(flash_storage_address_page2);

        if (result == false)
        {
           //FlashError();
            return -1;
        }      

        EPC_Estacionamento epc;

        for(i=0; i < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; i++){
            epc.tag = 0x0001 + i;
            adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados, epc);
        }

        uint16_t element;

        for( i = 0; i < listaDeVeiculosLiberados.ponteiroTabela; i++ ){  

            element = (listaDeVeiculosLiberados.epc[i]).tag;

            if( i == 0 ){            
                result  = FLASH_WriteWord16( flash_storage_address_page1, element);
            }
            else{
                if( i < 512 ){
                    result &= FLASH_WriteWord16( flash_storage_address_page1 + i * 2U, element ); 
                }
                else{
                    if( i == 512 ){
                        result  = FLASH_WriteWord16( flash_storage_address_page2, element );
                    }
                    else{
                        result &= FLASH_WriteWord16( flash_storage_address_page2 + (i - 512) * 2U, element );
                    }
                }
            }
        }    

        if (result == false)
        {
            //FlashError();
            return -1;
        }

        // Clear Key for NVM Commands so accidental call to flash routines will not corrupt flash
        FLASH_Lock();

        EPC_Estacionamento readEPC;

        // read the data to verify the data
        for( i = 0; i < listaDeVeiculosLiberados.ponteiroTabela; i++ ){
            if( i < 512 ){
                readEPC.tag = FLASH_ReadWord16( flash_storage_address_page1 + i * 2U );
                adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberadosTest, readEPC);
            }
            else{
                readEPC.tag = FLASH_ReadWord16( flash_storage_address_page2 + (i-512) * 2U );
                adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberadosTest, readEPC);
            }        
        }    

        uint16_t var1,var2;
        // Stop if the read data does not match the write data;
        for( i = 0; i < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; i++ ){

            var1 = (listaDeVeiculosLiberados.epc[i]).tag;
            var2 = (listaDeVeiculosLiberadosTest.epc[i]).tag;

            if ( var1 != var2 ){
                  //MiscompareError();  
                return -2;
            }
        }      
        return 0;
    }

    
//    void testTabelaDeEPC_should_IncludeSearchExclude(void){
//        
//        TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados_test;
//        
//        int encontrei;
//    
//        char mensagem[100];
//        
//        EPC_Estacionamento epc; 
//        
//        logMsg("///////////////////////////////////////////////\n\rGREEN LIST\n\r///////////////////////////////////////////////\n\n\r");
//
//        ////////////////////////////////////////////////////
//        // Incluir 1000 registros
//        ////////////////////////////////////////////////////
//
//        int i;
//        
//        logMsg("///////////////////////////////////////////////\n\rTESTE - 1000 REGISTROS SERAO CADASTRADOS\n\r///////////////////////////////////////////////\n\n\r");
//        
//        epc.tag = 0x3010;
//        
//        for( i = 0; i < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; i++){
//                                    
//            adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados_test, epc);
//            
//            epc.tag ++;
//            
//        }
//        
//        if( listaDeVeiculosLiberados_test.ponteiroTabela >= NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO){
//            sprintf( ( char* )mensagem, "Foram registrados: %d registros\n\n\r", ( unsigned int )listaDeVeiculosLiberados_test.ponteiroTabela );      
//            logMsg( ( const char* ) mensagem );
//        }
//        
//        ////////////////////////////////////////////////////
//        // Incluir registro e verificar que a tabela esta cheia e nao foi possivel encontra-lo em uma busca
//        ////////////////////////////////////////////////////
//
//        logMsg("///////////////////////////////////////////////\n\rTESTE - REGISTRO COM TABELA CHEIA\n\r///////////////////////////////////////////////\n\n\r");
//        
//        epc.tag = 0x2010;
//        
//        adicionarRegistroNaTabelaDeEpcDeEstacionamento( &listaDeVeiculosLiberados_test, epc );
//
//        encontrei = buscarRegistroNaTabelaDeEpcDeEstacionamento( &listaDeVeiculosLiberados_test, epc );
//
//        if(!encontrei){
//            sprintf( mensagem, "Tabela cheia, nao foi possivel registrar\n\n\r" );          
//            logMsg( ( const char*) mensagem);
//        }
//        
//        ////////////////////////////////////////////////////
//        // Verificar que foi possivel encontrar um registro em uma busca
//        ////////////////////////////////////////////////////
//        
//        logMsg("///////////////////////////////////////////////\n\rTESTE - ENCONTRAR REGISTRO COM BUSCA\n\r///////////////////////////////////////////////\n\n\r");
//        
//        epc.tag = 0x3010;
//        
//        encontrei = buscarRegistroNaTabelaDeEpcDeEstacionamento( &listaDeVeiculosLiberados_test, epc );
//
//        if(encontrei){
//            sprintf( mensagem, "Encontrei o registro: %x\n\n\r", (unsigned int) epc.tag ); 
//            logMsg((const char*)mensagem);
//        }
//
//        ////////////////////////////////////////////////////
//        // Excluir tabela e não encontrar registro em uma busca
//        ////////////////////////////////////////////////////
//        
//        logMsg("\r///////////////////////////////////////////////\n\rTESTE - EXCLUIR TABELA E NAO ENCONTRAR REGISTRO\n\r///////////////////////////////////////////////\n\n\r");
//        
//        epc.tag = 0x3010;
//        
//        removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados_test);
//
//        encontrei = buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados_test, epc );
//
//        if(!encontrei){
//            sprintf( mensagem, "Não encontrei o registro: %x\n\n\r", (unsigned int) epc.tag );
//            logMsg((const char*)mensagem);
//        }
//    }