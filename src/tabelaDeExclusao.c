
#include "tabelaDeExclusao.h"
    
    TabelaDeExclusao tabelaDeExclusao;    
    int ponteiroTabelaDeExclusao = 0;
        
    void adicionarRegistroNaTabelaDeExclusao(EPC _epc){
        tabelaDeExclusao.epc[ponteiroTabelaDeExclusao].tag = _epc.tag;
        ponteiroTabelaDeExclusao++;
    }
    
    void zeraPointeiroDaTabelaDeExclusao(void){
        ponteiroTabelaDeExclusao = 0;
    }
    
    void removerTabelaDeExclusao(){  
        /*int i=0;
        for(i=0;i<NUMERO_MAXIMO_DE_REGISTROS_DA_TABELA_DE_EXCLUSAO;i++){
            tabelaDeExclusao.epc[i].tag = 0;
        }*/
        tabelaDeExclusao.epc[0].tag = 0;
        zeraPointeiroDaTabelaDeExclusao();
    }
    
    int buscarRegistroNaTabelaDeExclusao(EPC _epc){
        if(binarySearch(tabelaDeExclusao,0,ponteiroTabelaDeExclusao,_epc.tag)){
            return 1;
        }
        else{
            return 0;
        }
    }
    
    
    
    int binarySearch(TabelaDeExclusao arr, int l, int r, long _epc){ 
        /* BUSCA COM RECURSIVIDADE E REENTRANCIA
        if (r >= l) { 
            int mid = l + (r - l) / 2; 
            if (arr.epc[mid].tag == _epc) 
                return mid;             
            if (arr.epc[mid].tag > _epc) 
                return binarySearch(arr, l, mid - 1, _epc); 
            return binarySearch(arr, mid + 1, r, _epc); 
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
            if(arr.epc[meio].tag == _epc){
                encontrei = SIM;
            }
            else{
                if(_epc < arr.epc[meio].tag){
                    ultimo = meio - 1;
                }
                else{
                    primeiro = meio + 1;
                }
            }
        }
        return encontrei;
    }  

    /*
    first = 0
    last = len(alist)-1
    found = False

    while first<=last and not found:
        midpoint = (first + last)//2
        if alist[midpoint] == item:
            found = True
        else:
            if item < alist[midpoint]:
                last = midpoint-1
            else:
                first = midpoint+1

    return found
    */