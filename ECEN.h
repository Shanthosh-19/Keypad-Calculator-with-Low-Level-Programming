long numbers(char,char);
char digits(char);
char display(long);
void outputs(long,long,long,long,long);
void printE(void);
void initializePort(void);
long countNumbers(long);
void outputNeg(long,long,long,long,long);

void initializePort(){
  volatile char *dirf,*dirk,*dira,*dird;
  dira=0x21;
  dird=0x2a;
  dirf=0x30;
  dirk=0x107;
  *dira=0xff;
  *dird=0x0f;
  *dirf=0x0f;
  *dirk=0x00;
}

char digits(char a,char b){
  volatile char save;
  if(a==0x01){
    if(b==0x01) save=0x06;
    else if(b==0x02) save=0x5b;
    else if(b==0x04) save=0x4f;
  }
  else if(a==0x02){
    if(b==0x01) save=0x66;
    else if(b==0x02) save=0x6d;
    else if(b==0x04) save=0x7d;
  }
  else if(a==0x04){
    if(b==0x01) save=0x07;
    else if(b==0x02) save=0x7f;
    else if(b==0x04) save=0x6f;
  }
  else if(a==0x08){
    if(b==0x02) save=0x3f;
  }
  return save;
}

long numbers(char a){
  volatile long save;
  if(a==0x06) save=1;
  else if(a==0x5b) save=2;
  else if(a==0x4f) save=3;
  else if(a==0x66) save=4;
  else if(a==0x6d) save=5;
  else if(a==0x7d) save=6;
  else if(a==0x07) save=7;
  else if(a==0x7f) save=8;
  else if(a==0x6f) save=9;
  else if(a==0x3f) save=0;

  return save;
}

char display(long a){
  volatile char save;
  if(a==1) save=0x06;
  else if(a==2) save=0x5b;
  else if(a==3) save=0x4f;
  else if(a==4) save=0x66;
  else if(a==5) save=0x6d;
  else if(a==6) save=0x7d;
  else if(a==7) save=0x07;
  else if(a==8) save=0x7f;
  else if(a==9) save=0x6f;
  else if(a==0) save=0x3f;
  else if(a==11) save=0x00;
  else if(a==13) save=0x40;

  return save;
}

void outputs(long count,long first,long second,long third,long fourth){
  volatile char *outa,*outd;
  outa=0x22;
  outd=0x2b;
  if(count==3){
    first=11;
  }
  else if(count==2){
    first=11;
    second=11;
  }
  else if(count==1){
    first=11;
    second=11;
    third=11;
  }
  else if(count==0){
    first=11;
    second=11;
    third=11;
  }
  while(1){
    *outd=0x0f;
    *outa=display(first);
    *outd=0x0e;
    for(volatile long j=0;j<3000;j++);
    *outd=0x0f;
    *outa=display(second);
    *outd=0x0d;
    for(volatile long j=0;j<3000;j++);
    *outd=0x0f;
    *outa=display(third);
    *outd=0x0b;
    for(volatile long j=0;j<3000;j++);
    *outd=0x0f;
    *outa=display(fourth);
    *outd=0x07;
    for(volatile long j=0;j<3000;j++);
  }
}

void printE(){
  volatile char *outa,*outd;
  outa=0x22;
  outd=0x2b;
  while(1){
    *outd=0x0f;
    *outa=0x79;
    *outd=0x00;
    for(volatile long j=0;j<3000;j++);
  }
}

long countNumbers(long a){ 
  volatile long count=0;
  while(a!=0){
    count++;
    a/=10;
  }
  return count;
}

void outputNeg(long count,long first,long second,long third,long fourth){
  volatile char *outa,*outd;
  outa=0x22;
  outd=0x2b;
  if(count==3){
    first=13;
  }
  else if(count==2){
    first=11;
    second=13;
  }
  else if(count==1){
    first=11;
    second=11;
    third=13;
  }
  while(1){
    *outd=0x0f;
    *outa=display(first);
    *outd=0x0e;
    for(volatile long j=0;j<3000;j++);
    *outd=0x0f;
    *outa=display(second);
    *outd=0x0d;
    for(volatile long j=0;j<3000;j++);
    *outd=0x0f;
    *outa=display(third);
    *outd=0x0b;
    for(volatile long j=0;j<3000;j++);
    *outd=0x0f;
    *outa=display(fourth);
    *outd=0x07;
    for(volatile long j=0;j<3000;j++);
  }
}