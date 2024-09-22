//****************************************************************************************\\
// KEYPAD THAT PERFORMS ADD(A), SUB(B), PROD(C), DIV(D), MOD(*).

// THIS SYSTEM CAN PERFORM OPERATIONS, IS  SUITABLE TO PRODUCE THE OUTPUT 
// WITHIN THE RANGE OF -999 - 9999. IF THE LIMITS OF OUTPUT IS CROSSED, IT'LL DISPLAY "EEEE".

// AFTER GIVING REQUIRED INPUT, PRESS (#) TO GET THE RESULT.
//****************************************************************************************\\

#include "ECEN.h"

#define k_rows 4

void setup() {
  // put your setup code here, to run once:
  initializePort();
}

void loop() {
  // put your main code here, to run repeatedly:
  volatile char *outf,*ink,*outa,*outd;
  outf=0x31;
  ink=0x106;
  outa=0x22;
  outd=0x2b;
  volatile char readInput,flag1=0,flag2=0,firstnumber=0,secondnumber=0,sumflag=0,subflag=0,prodflag=0,divflag=0,modflag=0,eflag=0,negflag=0;
  volatile long number1=0,number2=0,no1=0,no2=0,sum=0,sub=0,prod=0,div=0,mod=0,first,second,third,fourth,count;
  while(1){
    readInput=0;
    for(volatile long i=0;i<k_rows;i++){
      *outf=1<<i;
      readInput=*ink;
      if(readInput){
        for(volatile long j=0;j<160000;j++);
        if(flag1==0 && flag2==0){
          *outd=0x0f;
          firstnumber=digits(*outf,readInput);
          no1=numbers(firstnumber);
          number1=(number1*10)+no1;
          *outa=firstnumber;
          *outd=0x0e;
          if(*outf==0x01 && readInput==0x08){
            for(volatile long j=0;j<3000;j++);
            flag1=1;
            number1/=10;
          }
          if(*outf==0x02 && readInput==0x08){
            for(volatile long j=0;j<3000;j++);
            flag1=2;
            number1/=10;
          }
          if(*outf==0x04 && readInput==0x08){
            for(volatile long j=0;j<3000;j++);
            flag1=3;
            number1/=10;
          }
          if(*outf==0x08 && readInput==0x08){
            for(volatile long j=0;j<3000;j++);
            flag1=4;
            number1/=10;
          }
          if(*outf==0x08 && readInput==0x01){
            for(volatile long j=0;j<3000;j++);
            flag1=5;
            number1/=10;
          }
        }
        else if(flag1 && flag2==0){
          *outd=0x0f;
          secondnumber=digits(*outf,readInput);
          no2=numbers(secondnumber);
          number2=(number2*10)+no2;
          *outa=secondnumber;
          *outd=0x0d;
          if(*outf==0x08 && readInput==0x04){
            for(volatile long j=0;j<3000;j++);
            flag2=1;
            number2/=10;
            break;
          }
        }
      }
    }
    if(flag2){
      if(flag1==1){
        sum=number1+number2;
        count=countNumbers(sum);
        if(sum<10000){
          first=sum/1000;
          second=(sum%1000)/100;
          third=(sum%100)/10;
          fourth=sum%10;
          eflag=0;
          sumflag=1;
          break;
        }
        else{
          sumflag=1;
          eflag=1;
          break;
        }
      }
      else if(flag1==2){
        sub=number1-number2;
        count=countNumbers(sub);
        if(sub<10000 && sub>=0){
          first=sub/1000;
          second=(sub%1000)/100;
          third=(sub%100)/10;
          fourth=sub%10;
          eflag=0;
          subflag=1;
          break;
        }
        else if(sub<0){
          sub=-sub;
          count=countNumbers(sub);
          first=sub/1000;
          second=(sub%1000)/100;
          third=(sub%100)/10;
          fourth=sub%10;
          eflag=0;
          negflag=1;
          subflag=1;
          break;
        }
        else{
          subflag=1;
          eflag=1;
          break;
        }
      }
      else if(flag1==3){
        prod=(number1)*(number2);
        count=countNumbers(prod);
        if(prod<10000){
          first=prod/1000;
          second=(prod%1000)/100;
          third=(prod%100)/10;
          fourth=prod%10;
          eflag=0;
          prodflag=1;
          break;
        }
        else{
          prodflag=1;
          eflag=1;
          break;
        }
      }
      else if(flag1==4){
        div=(number1)/(number2);
        count=countNumbers(div);
        if(div<10000){
          first=div/1000;
          second=(div%1000)/100;
          third=(div%100)/10;
          fourth=div%10;
          divflag=1;
          break;
        }
      }
      else if(flag1==5){
        mod=(number1)%(number2);
        count=countNumbers(mod);
        if(mod<10000){
          first=mod/1000;
          second=(mod%1000)/100;
          third=(mod%100)/10;
          fourth=mod%10;
          modflag=1;
          break;
        }
      }
    }
  }
  if(sumflag){
    if(eflag==0){
      outputs(count,first,second,third,fourth);
    }
    else if(eflag) printE();
  }
  else if(subflag){
    if(eflag==0){
      if(negflag==0) outputs(count,first,second,third,fourth);
      else if(negflag==1){
        outputNeg(count,first,second,third,fourth);
      }
    }
    else if(eflag) printE();
  }
  else if(prodflag){
    if(eflag==0){
      outputs(count,first,second,third,fourth);
    }
    else if(eflag) printE();
  }
  else if(divflag){
    outputs(count,first,second,third,fourth);
  }
  else if(modflag){
    outputs(count,first,second,third,fourth);
  }
}