/*
 *****************************************************************************
 * Copyright by ams AG                                                       *
 * All rights are reserved.                                                  *
 *                                                                           *
 * IMPORTANT - PLEASE READ CAREFULLY BEFORE COPYING, INSTALLING OR USING     *
 * THE SOFTWARE.                                                             *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS         *
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT          *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.      *
 *****************************************************************************
 */
/** @file
  * @brief Implementation of tuner functionality.
  *
  * This file includes the whole functionality to adjust the PI tuner network 
  * on tuner enabled boards.
  * The communication pins for the tuner network are defined in platform.h.
  * The tuner network consists of 3 variable capacitors: Cin, Clen and Cout
  * and looks like this:
  \code
                         .--- L ---.
                         |         |
  in ----.----.----- L --.--C_len--.--.-----.-----.----- out
         |    |                       |     |     |
        C_in  L                     C_out   L     R
         |    |                       |     |     |
        ___  ___                     ___   ___   ___
         -    -                       -     -     -
         '    '                       '     '     '
  \endcode
  *
  * @author Ulrich Herrmann
  * @author Bernhard Breinbauer
  */
#include "as3993_config.h"
#include "global.h"
#include "delay.h"
#include <uart.h>
#include "tuner.h"
#include "as3993_public.h"
#include "platform.h"
#include "logger.h"
#include "timer.h"

#include "tuner.h"
#include <math.h>
#include "appl_commands.h"
#include "as3993.h"
#include "setup_usb.h"
#include "i2c.h"

#include "spi1.h"

extern Freq Frequencies;
void calcula_dbm(int);

void tunerDebug();

u8 tunerCheckConfig(const TunerConfiguration * config, u8 component);

void tunerInit(const TunerConfiguration *config){  
    tunerSetTuning(config,0,21,12);  // FWEMP_POC_V01R00.hex    
}

void sintonizaCapacitores(const TunerConfiguration *config, u8 Cin, u8 Cen, u8 Cout){
     tunerSetTuning(config, Cin, Cin, Cout); //antena 1
}

void tunerInit_A1(const TunerConfiguration *config)
{    
    tunerSetTuning(config,capAntena1[0],capAntena1[1],capAntena1[2]);
}

void tunerInit_A2(const TunerConfiguration *config)
{
    //tunerSetTuning(config, 1,16,10);//antena 2 - 15 metros   
    tunerSetTuning(config,capAntena2[0],capAntena2[1],capAntena2[2]);  
}

void tunerInit_A3(const TunerConfiguration *config)
{
    //tunerSetTuning(config,0,11,4); // antena 3 - 15 metros   
    tunerSetTuning(config,capAntena3[0],capAntena3[1],capAntena3[2]);
}

void tunerInit_A4(const TunerConfiguration *config)
{
    tunerSetTuning(config, 0, 23, 11);//antena 3,4,5
}

void tunerInit_A5(const TunerConfiguration *config)
{
    tunerSetTuning(config, 0, 23, 11);//antena 3,4,5
}

void mainSenCIN(int select)
{
    if (select) 
        SEN_TUNER_CIN(1);
    else
        SEN_TUNER_CIN(0);

}
void mainSenCLEN(int select)
{
    if (select) 
        SEN_TUNER_CLEN(1);
    else
        SEN_TUNER_CLEN(0);

}
void mainSenCOUT(int select)
{
    if (select) 
        SEN_TUNER_COUT(1);
    else
        SEN_TUNER_COUT(0);

}

TunerConfiguration mainTuner = 
{
    mainSenCIN,
    mainSenCLEN,
    mainSenCOUT
};


void realizaAutoSintoniaDosCapacitores(int Metodo){
    //extern  TunerParameters tunerParams;
    static TunerParameters tunerParams = {2, 12, 12};
    extern TunerConfiguration mainTuner;
    TunerConfiguration *tuner = NULL;
    TunerParameters *params = NULL;
//    int Resultados[3];
    
    int endereco = 0;
    char enderecoRefl_MSB = 0;
    char enderecoRefl_LSB = 0;
    unsigned char aux1,aux2;
    
    char Mensagem[100];
    int Contador;
    
    tuner = &mainTuner;
    params = &tunerParams;
    
    int _AntenaASerLida;
    _AntenaASerLida = 1;
    sel_led(0,0);
    for(_AntenaASerLida=1;_AntenaASerLida<=4;_AntenaASerLida++){
        sel_led(_AntenaASerLida, 1);
        sel_antena(_AntenaASerLida);
        delay_ms(300);
        switch(Metodo){
            case (0):
                as3993AntennaPower(1);
                tunerOneHillClimb(tuner, params, 100);
                as3993AntennaPower(0);
                break;
            case (1): /* advanced: hill climb from more points */
                as3993AntennaPower(1);
                tunerMultiHillClimb(tuner, params);
                as3993AntennaPower(0);
                break;
            case (2):
                as3993AntennaPower(1);
                tunerTraversal(tuner, params);
                as3993AntennaPower(0);
        }

        sprintf(Mensagem, "Antena %d -> Cin: %d, Clen: %d, Cout: %d, Reflexao: %d\n", _AntenaASerLida,params->cin, params->clen, params->cout,params->reflectedPower);
        
        switch(_AntenaASerLida){
            case 1:
                endereco = END_AJUSTE_CAP0_ANTENA_1;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_1_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_1_LSB;
                break;
            case 2:
                endereco = END_AJUSTE_CAP0_ANTENA_2;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_2_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_2_LSB;
                break;
            case 3:
                endereco = END_AJUSTE_CAP0_ANTENA_3;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_3_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_3_LSB;
                break;
            case 4: 
                endereco = END_AJUSTE_CAP0_ANTENA_4;
                enderecoRefl_MSB = END_INTENSIDADE_REFLEXAO_ANTENA_4_MSB;
                enderecoRefl_LSB = END_INTENSIDADE_REFLEXAO_ANTENA_4_LSB;                       
                break;
        }
        
        EscreverNaEEprom(endereco, params->cin);
        EscreverNaEEprom(endereco+1, params->clen);
        EscreverNaEEprom(endereco+2, params->cout);
        
        aux1 = (unsigned char)(params->reflectedPower>>8);
        aux2 = (unsigned char)(params->reflectedPower & 0X00FF);
        EscreverNaEEprom(enderecoRefl_MSB,aux1);
        EscreverNaEEprom(enderecoRefl_LSB,aux2);
        
        Contador = 0;
//        while(Mensagem[Contador]){
//            uart3Tx(Mensagem[Contador]);
//            Contador = Contador + 1;
//        }
        sel_led(_AntenaASerLida, 0);
    }
}

/*------------------------------------------------------------------------- */
/**
 * Checks if component is available in current tuner configuration. If it is
 * available the return value is 0 if there is no such component the return
 * value is 1.
 * @param component tuner cap component (TUNER_Cin, TUNER_Clen, TUNER_Cout)
 * @return 0 If configuration matches, 1 if component is invalid.
 */
u8 tunerCheckConfig(const TunerConfiguration *config, u8 component){
    u8 ret = 0;
    switch (component)
    {
        case TUNER_CIN:
            if (config->cinSenFn == 0)
                ret = 1;
            break;
        case TUNER_CLEN:
            if (config->clenSenFn == 0)
                ret = 1;
            break;
        case TUNER_COUT:
            if (config->coutSenFn == 0)
                ret = 1;
            break;
        default:
            ret = 1;
    }
    if (ret == 1)
    {
        //TLOG("Tuner: invalid component: %hhx\n", component);
    }
    return ret;
}

void tunerSetCap(const TunerConfiguration *config,  u8 component, u8 val ){
    
    if (tunerCheckConfig(config, component))
        return;     //we have an invalid component.

    switch (component)
    {
        case TUNER_CIN:
            config->cinSenFn(1);
            sel_cap_cin(1);
            break;
        case TUNER_CLEN:
            config->clenSenFn(1);
            sel_cap_clen(1);
            break;
        case TUNER_COUT:
            config->coutSenFn(1);
            sel_cap_cout(1);
            break;
    }

    SPI1_Exchange8bitBuffer(&val, 1, 0);

    switch (component)
    {
        case TUNER_CIN:
            config->cinSenFn(0);
            sel_cap_cin(0);
            break;
        case TUNER_CLEN:
            config->clenSenFn(0);
            sel_cap_clen(0);
            break;
        case TUNER_COUT:
            config->coutSenFn(0);
            sel_cap_cout(0);
            break;
    }
}

u16 tunerGetReflected(void){
    u16 r; u32 refl;
    s8 i, q;

    delay_us(300);
    r = as3993GetReflectedPower();
    i = r & 0xff;
    q = r >> 8;
    refl = (i * i) + (q * q);

    r = refl;
    if (refl > 0xffff) r= 0xffff;

    return r;
}

u8 tunerClimbOneParam(const TunerConfiguration *config,  u8 el, u8 *elval, u16 *reflectedPower, u16 *maxSteps){
    u16 refl, start = *reflectedPower;
    s8 dir = 0;
    s8 add = 0;
    u8 improvement = 3;
    u8 bestelval;

    if (tunerCheckConfig(config, el))
        return 0;     //we have an invalid component.

    if (*maxSteps == 0)
    {
        return 0;
    }

    //TLOG("start: el %hhx val %hhx r %hx\n",el,*elval,*reflectedPower);
    if ( *elval != 0 )
    {
        tunerSetCap(config, el, *elval - 1 ); 
        refl = tunerGetReflected();
        //TLOG("-1:  r %hx\n",refl);
        if ( refl <= *reflectedPower )
        {
            *reflectedPower = refl;
            dir = -1;
        }
    }

    if ( *elval < 31 )
    {
        tunerSetCap(config, el, *elval + 1 ); 
        refl = tunerGetReflected();
        //TLOG("+1:  r %hx\n",refl);
        if ( refl <= *reflectedPower )
        {
            *reflectedPower = refl;
            dir = 1;
        }
    }

    /* if it's possible we try to change the value by 2 and check what direction is better.
     * This improves tuning in the case of a local minima. */
    if ( *elval > 1 )
    {
        tunerSetCap(config, el, *elval - 2 );
        refl = tunerGetReflected();
        //TLOG("-2:  r %hx\n",refl);
        if ( refl <= *reflectedPower )
        {
            *reflectedPower = refl;
            dir = -1;
            add = -1;
        }
    }

    if ( *elval < 30 )
    {
        tunerSetCap(config, el, *elval + 2 );
        refl = tunerGetReflected();
        //TLOG("+2:  r %hx\n",refl);
        if ( refl <= *reflectedPower )
        {
            *reflectedPower = refl;
            dir = 1;
            add = 1;
        }
    }

    *elval += add;
    *elval += dir;
    bestelval = *elval;
    //TLOG("decision:  dir %hhx add %hhx\n",dir, add);

    if (dir!=0)
    {
        (*maxSteps)--;
        while ( improvement && *maxSteps )
        {
            if ( *elval == 0 ) break;
            if ( *elval == 31 ) break;
            tunerSetCap(config, el, *elval + dir ); 
            refl = tunerGetReflected();
            //TLOG("t %hhx:  r %hx\n",*elval + dir, refl);
            if ( refl <= *reflectedPower )
            {
                (*maxSteps)--;
                *reflectedPower = refl;
                *elval += dir;
                bestelval = *elval;
                improvement = 3; /* we don't want to stop when a local minima is hit, so we
                continue tuning for 3 more steps, even if they are worse than the one before.
                If it does not improve in this 3 steps, we will go back to the best value. */
            }else{
                improvement--;
            }
        }
    }
    *elval = bestelval;
    tunerSetCap(config, el, *elval);
    //TLOG("result val %hhx: r %hx\n",*elval, *reflectedPower);
    return start > (*reflectedPower);
}

void tunerOneHillClimb(const TunerConfiguration *config,  TunerParameters *p, u16 maxSteps){
    u8 improvement = 1;

    tunerSetTuning(config, p->cin, p->clen, p->cout);

    p->reflectedPower = tunerGetReflected();

    while (maxSteps && improvement)
    {
        improvement = 0;
        if (config->cinSenFn)
            improvement |= tunerClimbOneParam(config, TUNER_CIN, &p->cin, &p->reflectedPower, &maxSteps);
        if (config->clenSenFn)
            improvement |= tunerClimbOneParam(config, TUNER_CLEN, &p->clen, &p->reflectedPower, &maxSteps);
        if (config->coutSenFn)
            improvement |= tunerClimbOneParam(config, TUNER_COUT, &p->cout, &p->reflectedPower, &maxSteps);
    }

    //tunerSetTuning(config, p->cin, p->clen, p->cout);
}

static const u8 tunePoints[3] = {5,16,26};

void tunerMultiHillClimb(const TunerConfiguration *config,  TunerParameters *res ){
    TunerParameters p;
    u8 i,j;

    tunerSetTuning(config, res->cin, res->clen, res->cout);

    res->reflectedPower = tunerGetReflected();

    for( i = 0; i < 27; i++ )
    {
        j=i;
        if (config->cinSenFn)
            p.cin  = tunePoints[j%3]; j/=3;
        if (config->clenSenFn)
            p.clen = tunePoints[j%3]; j/=3;
        if (config->coutSenFn)
            p.cout = tunePoints[j%3]; j/=3;
        tunerOneHillClimb(config, &p, 30);
        //TLOG("new refl: %hx, prev refl: %hx, cin: %hhx, count: %hhx\n", p.reflectedPower, res->reflectedPower, p.cin, p.cout );
        if ( p.reflectedPower < res->reflectedPower )
        {
            *res = p;
        }
    }

    tunerSetTuning(config, res->cin, res->clen, res->cout);
}

void tunerTraversal(const TunerConfiguration *config,  TunerParameters *res ){
    u8 l=0,o=0,i=0;
    u16 refl;
    res->reflectedPower = 32767;
    if (config->clenSenFn)
    for (l = 0; l < 32; l++)
    {
        tunerSetCap(config, TUNER_CLEN,l);
        //TLOG("%hhx\n",l);
        if (config->coutSenFn)
        for (o = 0; o < 32; o++)
        {
            tunerSetCap(config, TUNER_COUT,o);
            if (config->cinSenFn)
            for (i = 0; i < 32; i++)
            {
                tunerSetCap(config, TUNER_CIN,i);
                refl = tunerGetReflected();

                if ( refl < res->reflectedPower )
                {
                    res->cin  = i;
                    res->cout = o;
                    res->clen = l;
                    res->reflectedPower = refl;
                    //TLOG("cin=%hhx,cout=%hhx,clen=%hhx r=%hx\n",res->cin,res->cout,res->clen,res->reflectedPower);
                }
            }
        }
    }
    tunerSetTuning(config, res->cin, res->clen, res->cout);
    //TLOG("cin=%hhx,cout=%hhx,clen=%hhx r=%hx\n",res->cin,res->cout,res->clen,res->reflectedPower);
}

void tunerSetTuning(const TunerConfiguration *config, u8 cin, u8 clen, u8 cout ){
    //TLOG("setTuning %hhx %hhx %hhx\n", cin, clen, cout);
    if (config->cinSenFn)
        tunerSetCap(config, TUNER_CIN, cin);
    if (config->clenSenFn)
        tunerSetCap(config, TUNER_CLEN, clen);
    if (config->coutSenFn)
        tunerSetCap(config, TUNER_COUT, cout);
}




