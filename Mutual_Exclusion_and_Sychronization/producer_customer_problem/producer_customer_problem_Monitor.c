/*
monitor monitor_PC;
char buffer[n];
int nextin, nextout;
int count;
condition notfull, notempty;

void put(char x)
{
    if (count == n)
    cwait(notfull);
    buffer[nextin] = x;
    count += 1;
    csignal(notempty);
}

void get(char x)
{
    if (count == 0)
    cwait(notempty);
    x = buffer[nextout];
    count -= 1;
    csignal(notfull);
}

{
/* 管程体
    next = 0;
    nextout = 0;
    count = 0;
    // initialization
}


void producer(){
    char x;
    while (true){
        produce an char in x;
        monitor_PC.put(x);
    }
}

void consumer(){
    char x;
    while (true){
        monitor_PC.get(x);
        consume an x;
    }
}



*/