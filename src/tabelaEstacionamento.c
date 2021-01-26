
#include <stdio.h>

#include "tabelaEstacionamento.h"
  
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
    
    TabelaDeEpcDeEstacionamento __attribute__((far)) listaDeVeiculosLiberados_test;
    
    void testTabelaDeEPC_should_IncludeSearchExclude(void){
        
        int encontrei;
    
        char mensagem[100];
        
        EPC_Estacionamento epc; 

        ////////////////////////////////////////////////////
        // Incluir 1000 registros
        ////////////////////////////////////////////////////

        int i;
               
        epc.tag = 0x3010;
        
        for( i = 0; i < NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO; i++){
                                    
            adicionarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados_test, epc);
            
            epc.tag ++;
            
        }
        
        if( listaDeVeiculosLiberados_test.ponteiroTabela >= NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_ESTACIONAMENTO){
            sprintf( mensagem, "Foram registrados: %d registros", (unsigned int)listaDeVeiculosLiberados_test.ponteiroTabela );      
            printf(mensagem);
        }
        
        ////////////////////////////////////////////////////
        // Incluir registro e verificar que a tabela esta cheia e nao foi possivel encontra-lo em uma busca
        ////////////////////////////////////////////////////

        epc.tag = 0x2010;
        
        adicionarRegistroNaTabelaDeEpcDeEstacionamento( &listaDeVeiculosLiberados_test, epc );

        encontrei = buscarRegistroNaTabelaDeEpcDeEstacionamento( &listaDeVeiculosLiberados_test, epc );

        if(!encontrei){
            sprintf( mensagem, "Tabela cheia, nao foi possivel registrar" );          
            printf(mensagem);
        }
        
        ////////////////////////////////////////////////////
        // Verificar que foi possivel encontrar um registro em uma busca
        ////////////////////////////////////////////////////
        
        epc.tag = 0x3010;
        
        encontrei = buscarRegistroNaTabelaDeEpcDeEstacionamento( &listaDeVeiculosLiberados_test, epc );

        if(encontrei){
            sprintf( mensagem, "Encontrei o registro: %x", (unsigned int) epc.tag ); 
            printf(mensagem);
        }

        ////////////////////////////////////////////////////
        // Excluir tabela e não encontrar registro em uma busca
        ////////////////////////////////////////////////////

        epc.tag = 0x3010;
        
        removerTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados_test);

        encontrei = buscarRegistroNaTabelaDeEpcDeEstacionamento(&listaDeVeiculosLiberados_test, epc );

        if(!encontrei){
            sprintf( mensagem, "Não encontrei o registro: %x", (unsigned int) epc.tag );
            printf(mensagem);
        }
    }